/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
 */
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Iphlpapi.lib")
#endif
#include "../common/config.h"
#include "GoProController.h"
#include "hv/EventLoop.h"
#include "hv/UdpClient.h"
#include "hv/UdpServer.h"
#include "hv/WebSocketServer.h"
#include "hv/hsocket.h"
#include <iostream>
#include <vector>

///
/// UDP packet header
///
struct SenderStruct {
  bool vaild;
  std::array<char, 24> host_ip;
  std::array<char, 24> websocket_ip;
  int32_t sock_fd;
  struct sockaddr_in bcsa;
};

///
/// The application data block
///
struct AppData {
  ///
  /// Main worker, HERO is here
  ///
  GoProController controller;
  ///
  /// This will prevent server download multiple media at the same time
  /// Imagine if there are 30+ cameras connected, that will be insane and crash
  /// easily.
  ///
  std::mutex download_mtx;
  ///
  /// UDP broadcasting thread blocker
  ///
  std::mutex broadcast_mtx;
  std::array<SenderStruct, 10> broadcast_addrs = std::array<SenderStruct, 10>();
};

///
/// For preview feature, listening port
///
constexpr int32_t listen_port = 8556;
///
/// For preview feature, broadcasting port
///
constexpr int32_t broadcast_port = 8554;

///
/// Packing the data into a string, to send back to master
///
/// Args:
/// - key: Header key, for first order filtering
/// - data: The actually json data
///
std::string getPacket(std::string key, json data) {
  json response = json::object();
  response["key"] = key;
  response["value"] = data;
  return response.dump();
}

void ExecuteCommand(const WebSocketChannelPtr &channel, json j) {
  std::string resultText = "";
  std::string name = "";
  std::string target = "";
  std::string value = "";
  int32_t ivalue = 0;
  json r = json::object();

  if (j["name"].is_string()) {
    name = j["name"].get<std::string>();
  }
  if (j["target"].is_string()) {
    target = j["target"].get<std::string>();
  }
  if (j["value"].is_string()) {
    value = j["value"].get<std::string>();
  }
  if (j["value"].is_number_integer()) {
    ivalue = j["value"].get<int32_t>();
  }

  if (name == "reboot") {
    controller.reboot(target);
    channel->send(getPacket("command:reboot", r));
  } else if (name == "shutdown") {
    controller.shutdown(target);
    channel->send(getPacket("command:shutdown", r));
  } else if (name == "keep_alive") {
    controller.keep_alive(target);
    channel->send(getPacket("command:keep_alive", r));
  } else if (name == "usb_on") {
    controller.usb(target, true);
    channel->send(getPacket("command:usb_on", r));
  } else if (name == "usb_off") {
    controller.usb(target, false);
    channel->send(getPacket("command:usb_off", r));
  } else if (name == "datetime") {
    controller.datetime(target);
    channel->send(getPacket("command:datetime", r));
  } else if (name == "zoom") {
    controller.zoom(target, ivalue);
    channel->send(getPacket("command:zoom", r));
  } else if (name == "shutter_on") {
    controller.shutter(target, true);
    channel->send(getPacket("command:shutter", r));
  } else if (name == "shutter_off") {
    controller.shutter(target, false);
    channel->send(getPacket("command:shutter_off", r));
  } else if (name == "ip") {
    resultText = controller.getAllIP();
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      std::cerr << "[ERROR] ExecuteCommand ip before response: " << resultText
                << std::endl;
      r["data"] = json::array();
    }
    channel->send(getPacket("command:ip", r));
  } else if (name == "locate_on") {
    controller.locate(target, true);
    r["data"] = json::object();
    channel->send(getPacket("command:locate_on", r));
  } else if (name == "locate_off") {
    controller.locate(target, false);
    r["data"] = json::object();
    channel->send(getPacket("command:locate_off", r));
  } else if (name == "res_clean") {
    if (fs::exists("res")) {
      fs::remove_all("res");
    }
    fs::create_directory("res");
    channel->send(getPacket("command:res_clean", r));
  } else if (name == "scan") {
    controller.scanCameras();
    channel->send(getPacket("command:scan", r));
  } else if (name == "clean") {
    controller.cleanCameras();
    channel->send(getPacket("command:clean", r));
  } else if (name == "add" && target.size() >= 3) {
    controller.addCameras(target);
    channel->send(getPacket("command:add", r));
  } else if (name == "delete" && target.size() >= 3) {
    controller.deleteCameras(target);
    channel->send(getPacket("command:delete", r));
  } else if (name == "rename" && target.size() >= 3) {
    controller.renameCameras(target, value);
    channel->send(getPacket("command:rename", r));
  } else {
    channel->send(getPacket("command:unknown", r));
  }
}

void QueryAction(const WebSocketChannelPtr &channel, json j) {
  std::string resultText = "";
  std::string name = "";
  std::string source = "";
  std::string target = "";
  int id = 0;
  int preset = 0;
  std::string value = "";
  json jvalue = json::object();
  json r = json::object();

  if (j["name"].is_string()) {
    name = j["name"].get<std::string>();
  }
  if (j["source"].is_string()) {
    source = j["source"].get<std::string>();
  }
  if (j["target"].is_string()) {
    target = j["target"].get<std::string>();
  }
  if (j["id"].is_number()) {
    id = j["id"].get<int32_t>();
  }
  if (j["value"].is_string()) {
    value = j["value"].get<std::string>();
  } else if (j["value"].is_object()) {
    jvalue = j["value"];
    if (j["value"]["preset"].is_number()) {
      preset = j["value"]["preset"].get<int32_t>();
    }
  }

  // The reason we need to seperate the set and setall
  // It's because we needs to know which one is called by master update loop
  // And which one is called by UI event
  //
  // We don't want to flip the update flag when it's actually the UI event...
  if (name == "get") {
    resultText = controller.queryStatus(target);
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      std::cerr << "[ERROR] QueryAction get before response: " << resultText
                << std::endl;
      r["data"] = json::array();
    }
    channel->send(getPacket("query:get", r));
  } else if (name == "getall") {
    resultText = controller.queryStatus("");
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      std::cerr << "[ERROR] QueryAction getall before response: " << resultText
                << std::endl;
      r["data"] = json::array();
    }
    channel->send(getPacket("query:getall", r));
  } else if (name == "set") {
    resultText = controller.setSetting(target, id, value);
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      std::cerr << "[ERROR] QueryAction set before response: " << resultText
                << std::endl;
      r["data"] = json::array();
    }
    channel->send(getPacket("query:set", r));
  } else if (name == "setall_cancel") {
    controller.setSettingCancelAll();
    channel->send(getPacket("query:setall_cancel", r));
  } else if (name == "setall") {
    resultText = controller.setSettingAll(source, target, preset, jvalue);
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      std::cerr << "[ERROR] QueryAction setall before response: " << resultText
                << std::endl;
      r["data"] = json::array();
    }
    channel->send(getPacket("query:setall", r));
  } else {
    channel->send(getPacket("query:unknown", r));
  }
}

void WebcamAction(const WebSocketChannelPtr &channel, json j) {
  std::string name = "";
  std::string target = "";
  int port = 8554;
  int res = 4;
  int fov = 0;
  bool ts = true;
  json r = json::object();

  if (j["name"].is_string()) {
    name = j["name"].get<std::string>();
  }
  if (j["target"].is_string()) {
    target = j["target"].get<std::string>();
  }
  if (j["port"].is_number_integer()) {
    port = j["port"].get<int>();
  }
  if (j["res"].is_number_integer()) {
    res = j["res"].get<int>();
  }
  if (j["fov"].is_number_integer()) {
    fov = j["fov"].get<int>();
  }
  if (j["ts"].is_boolean()) {
    ts = j["ts"].get<bool>();
  }

  if (name == "preview") {
    controller.webcamMode(target);
    channel->send(getPacket("webcam:reboot", r));
  } else if (name == "exit") {
    controller.webcamUnMode(target);
    channel->send(getPacket("webcam:exit", r));
  } else if (name == "start") {
    controller.webcamOn(target, port, res, fov, ts);
    channel->send(getPacket("webcam:start", r));
  } else if (name == "stop") {
    controller.webcamOff(target);
    channel->send(getPacket("webcam:stop", r));
  } else if (name == "status") {
    r["data"] = json::parse(controller.webcamStatus(target));
    channel->send(getPacket("webcam:status", r));
  } else if (name == "version") {
    r["data"] = json::parse(controller.webcamVersion(target));
    channel->send(getPacket("webcam:version", r));
  } else {
    channel->send(getPacket("webcam:unknown", r));
  }
}

void ModeAction(const WebSocketChannelPtr &channel, json j) {
  std::string name = "";
  std::string target = "";
  int mode = 0;
  json r = json::object();

  if (j["name"].is_string()) {
    name = j["name"].get<std::string>();
  }
  if (j["target"].is_string()) {
    target = j["target"].get<std::string>();
  }
  if (j["mode"].is_number()) {
    mode = j["mode"].get<int32_t>();
  }

  if (name == "load") {
    controller.setPreset(target, mode);
    channel->send(getPacket("preset:set", r));
  } else {
    channel->send(getPacket("webcam:unknown", r));
  }
}

void MediaAction(const WebSocketChannelPtr &channel, json j) {
  std::string resultText = "";
  std::string target = "";
  std::string name = "";
  std::string item = "";
  std::string path = "";
  std::string ip = "";
  std::string dir = "";
  std::string filename = "";
  std::vector<std::string> filenames = std::vector<std::string>();
  bool local = true;
  json r = json::object();

  if (j["target"].is_string()) {
    target = j["target"].get<std::string>();
  }
  if (j["name"].is_string()) {
    name = j["name"].get<std::string>();
  }
  if (j["item"].is_string()) {
    item = j["item"].get<std::string>();
  }
  if (j["path"].is_string()) {
    path = j["path"].get<std::string>();
  }
  if (j["ip"].is_string()) {
    ip = j["ip"].get<std::string>();
  }
  if (j["dir"].is_string()) {
    dir = j["dir"].get<std::string>();
  }
  if (j["filename"].is_string()) {
    filename = j["filename"].get<std::string>();
  }
  if (j["filenames"].is_array()) {
    for (size_t i = 0; i < j["filenames"].size(); i++) {
      if (j["filenames"][i].is_string()) {
        filenames.push_back(j["filenames"][i].get<std::string>());
      }
    }
  }
  if (j["local"].is_boolean()) {
    local = j["local"].get<bool>();
  }

  if (name == "lastmedia") {
    controller.keep_alive("");
    resultText = controller.getLastMedia(target);
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      r["data"] = json::array();
    }
    channel->send(getPacket("media:lastmedia", r));
  } else if (name == "url") {
    // Download the media one at the time... thanks
    std::lock_guard<std::mutex> lock(download_mtx);
    r["local"] = local;
    r["item"] = item;
    r["dir"] = dir;
    r["filename"] = filename;
    r["path"] = controller.getFetchURL(ip, local);
    channel->send(getPacket("media:url", r));
  } else if (name == "list") {
    resultText = controller.getMediaList(target);
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      r["data"] = json::array();
    }
    channel->send(getPacket("media:list", r));
  } else if (name == "thumbnail") {
    r["local"] = local;
    r["data"] = controller.getThumbnailData(ip, path, local);
    channel->send(getPacket("media:thumbnail", r));
  } else if (name == "info") {
    r["local"] = local;
    r["data"] = controller.getMediaInfoData(ip, path, local);
    channel->send(getPacket("media:info", r));
  } else if (name == "d_single") {
    std::lock_guard<std::mutex> lock(download_mtx);
    r["local"] = local;
    r["item"] = item;
    r["dir"] = dir;
    r["filename"] = filename;
    r["path"] = controller.getSingleFetchURL(ip, filename, local);
    channel->send(getPacket("media:d_single", r));
  } else if (name == "d_all") {
    std::lock_guard<std::mutex> lock(download_mtx);
    std::vector<std::pair<std::string, std::string>> results =
        controller.getAllFetchURL(ip, filenames, local);
    r["local"] = local;
    r["item"] = item;
    r["dir"] = dir;
    r["filenames"] = filenames;
    r["paths"] = json::array();
    for (size_t i = 0; i < results.size(); i++) {
      json buffer = json::object();
      buffer["filename"] = results.at(i).first;
      buffer["path"] = results.at(i).second;
      r["paths"].push_back(buffer);
    }
    channel->send(getPacket("media:d_all", r));
  } else {
    channel->send(getPacket("media:unknown", r));
  }
}

void PreviewAction(const WebSocketChannelPtr &channel, json j) {
  std::string target = "";
  std::string name = "";
  int32_t port = 8556;
  json r = json::object();

  if (j["target"].is_string()) {
    target = j["target"].get<std::string>();
  }
  if (j["name"].is_string()) {
    name = j["name"].get<std::string>();
  }
  if (j["port"].is_number_integer()) {
    port = j["port"].get<int32_t>();
  }

  if (name == "start") {
    controller.previewOn(target, port);
    channel->send(getPacket("preview:start", r));
  } else if (name == "stop") {
    controller.previewOff(target);
    channel->send(getPacket("preview:stop", r));
  } else {
    channel->send(getPacket("preview:unknown", r));
  }
}

void WebsocketServer(AppData &data) {
  std::cout << "Starting GoPro Server (RPi)..." << std::endl;
  hv::WebSocketService ws;
  ws.onopen = [&](const WebSocketChannelPtr &channel,
                  const HttpRequestPtr &req) {
    std::lock_guard<std::mutex> lock(data.broadcast_mtx);
    printf("Client connected: %s\n", channel->peeraddr().c_str());

    int32_t f = -1;
    for (int32_t i = 0; i < data.broadcast_addrs.size(); i++) {
      if (data.broadcast_addrs.at(i).websocket_ip ==
          channel->peeraddr().c_str()) {
        f = i;
        break;
      }
    }

    if (f == -1) {
      SenderStruct sss = SenderStruct();
      std::string addd = channel->peeraddr().c_str();
      while (addd.at(addd.size() - 1) != ':') {
        addd.pop_back();
      }
      addd.pop_back();

      sss.websocket_ip = channel->peeraddr().c_str();
      sss.host_ip = addd.c_str();

      sss.sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
      memset(&sss.bcsa, 0, sizeof(sss.bcsa));
      sss.bcsa.sin_family = AF_INET;
      sss.bcsa.sin_port = htons(data.broadcast_port);
      sss.bcsa.sin_addr.s_addr = inet_addr(addd.c_str());

      data.broadcast_addrs.push_back((sss));
    }
  };
  ws.onmessage = [&](const WebSocketChannelPtr &channel,
                     const std::string &msg) {
    if (!json::accept(msg.c_str()))
      return;
    std::thread([=]() {
#ifdef SERVER_QUERY_LOG
      printf("Received: %s\n", msg.c_str());
#endif
      try {
        json j = json::parse(msg.c_str());
        // Simple command parsing
        if (j["key"].get<std::string>() == "command") {
          ExecuteCommand(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "query") {
          QueryAction(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "webcam") {
          WebcamAction(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "media") {
          MediaAction(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "preview") {
          PreviewAction(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "preset") {
          ModeAction(&data.controller, channel, j["value"]);
        }
      } catch (const std::exception &e) {
        std::cerr << "JSON Parse error: " << e.what() << std::endl;
      }
    }).detach();
  };
  ws.onclose = [&](const WebSocketChannelPtr &channel) {
    std::lock_guard<std::mutex> lock(broadcast_mtx);
    printf("Client disconnected: %s\n", channel->peeraddr().c_str());

    int32_t f = -1;
    for (int32_t i = 0; i < broadcast_addrs.size(); i++) {
      if (broadcast_addrs.at(i).websocket_ip == channel->peeraddr().c_str()) {
        f = i;
        break;
      }
    }
    if (f >= 0) {
      SenderStruct &sss = broadcast_addrs.at(f);
      closesocket(sss.sock_fd);
      broadcast_addrs.erase(broadcast_addrs.begin() + f);
    }
  };

  hv::WebSocketServer server;
  server.registerWebSocketService(&ws);
  server.setPort(9090);

  std::cout << "WebSocket Server listening on port 9090..." << std::endl;
  server.run();
}

void HttpServer() {
  hv::HttpService router;
  ///
  /// Clean the res temp folder
  ///
  if (fs::exists("res")) {
    fs::remove_all("res");
  }
  fs::create_directory("res");
  router.Static("/res", "./res");

  hv::HttpServer http_server;
  http_server.registerHttpService(&router);
  http_server.setPort(8080);
  http_server.setThreadNum(4);

  std::cout << "Http Server listening on port 8080..." << std::endl;

  http_server.run();
}

void UDPProxyServer() {
  std::cout << "Starting GoPro UDP Proxy Server (RPi)..." << std::endl;
  static hv::UdpServer us;
  int32_t bindfd = us.createsocket(listen_port);
  if (bindfd == -1) {
    std::cerr << "Failed to create socket for recevier: " << std::endl;
    return;
  }
  std::cout << "UDP bind on port: " << listen_port << std::endl;
  std::cout << "UDP Broadcast Relay started:" << std::endl;
  std::cout << "  Listening on: 0.0.0.0:" << listen_port << " (from GoPro)"
            << std::endl;
  std::cout << "  Broadcasting to: " << broadcast_port << " (to all Masters)"
            << std::endl;

  us.onMessage = [&](const hv::SocketChannelPtr &channel, hv::Buffer *buf) {
    std::lock_guard<std::mutex> lock(broadcast_mtx);
    for (auto &sss : broadcast_addrs) {
#ifdef _WIN32
      sendto(sss.sock_fd, (const char *)buf->data(), buf->size(), 0,
             (struct sockaddr *)&sss.bcsa, sizeof(sss.bcsa));
#else
      sendto(sss.sock_fd, buf->data(), buf->size(), 0,
             (struct sockaddr *)&sss.bcsa, sizeof(sss.bcsa));
#endif
    }
  };
  us.start();
}

int main() {
  AppData data = AppData();

  // I forgot why this is here, probably console printf related stuff...
  // Just don't touch it
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // For communication, so master can know shit
  std::thread t1 = std::thread([&data]() {
    std::cout << "Create websocket server" << std::endl;
    WebsocketServer(&data);
  });

  // For static file service, so master can download shit
  std::thread t2 = std::thread([&data]() {
    std::cout << "Create http server" << std::endl;
    HttpServer(&data);
  });

  // For preview feature, so master can see shit
  std::thread t3 = std::thread([&data]() {
    std::cout << "Create udp server" << std::endl;
    UDPProxyServer(&data);
  });

  data.controller.update();

  t3.join();
  t2.join();
  t1.join();
  return 0;
}
