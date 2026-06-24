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
#include "data.h"
#include "analysis.h"
#include "../common/config.h"

#include "hv/EventLoop.h"
#include "hv/UdpClient.h"
#include "hv/UdpServer.h"
#include "hv/WebSocketServer.h"
#include "hv/hsocket.h"
#include <iostream>
#include <vector>

void websocket_server(AppData &data) noexcept {
  std::cout << "Starting GoPro Server (RPi)..." << std::endl;
  hv::WebSocketService ws;
  ws.onopen = [&](const WebSocketChannelPtr &channel, const HttpRequestPtr &req) {
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
      printf("Received: %s\n", msg.c_str());
      try {
        json j = json::parse(msg.c_str());
        // Simple command parsing
        if (j["key"].get<std::string>() == "command") {
          execute_command(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "query") {
          query_action(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "webcam") {
          webcam_action(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "media") {
          media_action(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "preview") {
          preview_action(&data.controller, channel, j["value"]);
        } else if (j["key"].get<std::string>() == "preset") {
          mode_action(&data.controller, channel, j["value"]);
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

void http_server() noexcept {
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

void upd_proxy_server() noexcept {
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

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  std::thread t1 = std::thread([&data]() {
    std::cout << "Create websocket server" << std::endl;
    websocket_server(data);
  });

  std::thread t2 = std::thread([&data]() {
    std::cout << "Create http server" << std::endl;
    http_server(data);
  });

  std::thread t3 = std::thread([&data]() {
    std::cout << "Create udp server" << std::endl;
    upd_proxy_server(data);
  });

  data.controller.update();

  t3.join();
  t2.join();
  t1.join();
  return 0;
}
