/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "analysis.h"
#include <cinttypes>
#include "gopro_controller.h"
#include "../common/utility.h"

void Execute_command(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) {
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
    gopro_controller_reboot(controller, target);
    channel->send(Get_packet("command:reboot", r));
  } else if (name == "shutdown") {
    gopro_controller_shutdown(controller, target);
    channel->send(Get_packet("command:shutdown", r));
  } else if (name == "keep_alive") {
    gopro_controller_keep_alive(controller, target);
    channel->send(Get_packet("command:keep_alive", r));
  } else if (name == "usb_on") {
    gopro_controller_usb(controller, target, true);
    channel->send(Get_packet("command:usb_on", r));
  } else if (name == "usb_off") {
    gopro_controller_usb(controller, target, false);
    channel->send(Get_packet("command:usb_off", r));
  } else if (name == "datetime") {
    gopro_controller_datetime(controller, target);
    channel->send(Get_packet("command:datetime", r));
  } else if (name == "zoom") {
    gopro_controller_zoom(controller, target, ivalue);
    channel->send(Get_packet("command:zoom", r));
  } else if (name == "shutter_on") {
    gopro_controller_shutter(controller, target, true);
    channel->send(Get_packet("command:shutter", r));
  } else if (name == "shutter_off") {
    gopro_controller_shutter(controller, target, false);
    channel->send(Get_packet("command:shutter_off", r));
  } else if (name == "ip") {
    r["data"] = gopro_controller_get_IPs(controller);
    channel->send(Get_packet("command:ip", r));
  } else if (name == "locate_on") {
    gopro_controller_locate(controller, target, true);
    r["data"] = json::object();
    channel->send(Get_packet("command:locate_on", r));
  } else if (name == "locate_off") {
    controller.locate(target, false);
    r["data"] = json::object();
    channel->send(Get_packet("command:locate_off", r));
  } else if (name == "res_clean") {
    if (fs::exists("res")) {
      fs::remove_all("res");
    }
    fs::create_directory("res");
    channel->send(Get_packet("command:res_clean", r));
  } else if (name == "scan") {
    gopro_controller_scan_cameras(controller);
    channel->send(Get_packet("command:scan", r));
  } else if (name == "clean") {
    gopro_controller_clean_cameras(controller);
    channel->send(Get_packet("command:clean", r));
  } else if (name == "add" && target.size() >= 3) {
    gopro_controller_add_cameras(controller, target);
    channel->send(Get_packet("command:add", r));
  } else if (name == "delete" && target.size() >= 3) {
    gopro_controller_delete_cameras(controller, target);
    channel->send(Get_packet("command:delete", r));
  } else if (name == "rename" && target.size() >= 3) {
    gopro_controller_rename_cameras(controller, target, value);
    channel->send(Get_packet("command:rename", r));
  } else {
    channel->send(Get_packet("command:unknown", r));
  }
}
void Query_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) {
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
    channel->send(Get_packet("query:get", r));
  } else if (name == "getall") {
    resultText = controller.queryStatus("");
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      std::cerr << "[ERROR] QueryAction getall before response: " << resultText
                << std::endl;
      r["data"] = json::array();
    }
    channel->send(Get_packet("query:getall", r));
  } else if (name == "set") {
    resultText = controller.setSetting(target, id, value);
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      std::cerr << "[ERROR] QueryAction set before response: " << resultText
                << std::endl;
      r["data"] = json::array();
    }
    channel->send(Get_packet("query:set", r));
  } else if (name == "setall_cancel") {
    controller.setSettingCancelAll();
    channel->send(Get_packet("query:setall_cancel", r));
  } else if (name == "setall") {
    resultText = controller.setSettingAll(source, target, preset, jvalue);
    if (json::accept(resultText)) {
      r["data"] = json::parse(resultText);
    } else {
      std::cerr << "[ERROR] QueryAction setall before response: " << resultText
                << std::endl;
      r["data"] = json::array();
    }
    channel->send(Get_packet("query:setall", r));
  } else {
    channel->send(Get_packet("query:unknown", r));
  }
}
void Webcam_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) {
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
    gopro_controller_webcam_mode(controller, target);
    channel->send(Get_packet("webcam:reboot", r));
  } else if (name == "exit") {
    gopro_controller_webcam_mode_off(controller, target);
    channel->send(Get_packet("webcam:exit", r));
  } else if (name == "start") {
    gopro_controller_webcam_on(controller, target, port, res, fov, ts);
    channel->send(Get_packet("webcam:start", r));
  } else if (name == "stop") {
    gopro_controller_webcam_off(controller, target);
    channel->send(Get_packet("webcam:stop", r));
  } else if (name == "status") {
    r["data"] = controller.gopro_controller_webcam_status(controller, target);
    channel->send(Get_packet("webcam:status", r));
  } else if (name == "version") {
    r["data"] = controller.gopro_controller_webcam_version(controller, target);
    channel->send(Get_packet("webcam:version", r));
  } else {
    channel->send(Get_packet("webcam:unknown", r));
  }
}
void Mode_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) {
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
    channel->send(Get_packet("preset:set", r));
  } else {
    channel->send(Get_packet("webcam:unknown", r));
  }
}
void Media_action(gopro_controller& controller, AppData& data, const WebSocketChannelPtr &channel, json j) {
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
    channel->send(Get_packet("media:lastmedia", r));
  } else if (name == "url") {
    // Download the media one at the time... thanks
    std::lock_guard<std::mutex> lock(data.download_mtx);
    r["local"] = local;
    r["item"] = item;
    r["dir"] = dir;
    r["filename"] = filename;
    r["path"] = gopro_controller_get_fetch_URL(controller, ip, local);
    channel->send(Get_packet("media:url", r));
  } else if (name == "list") {
    r["data"] = gopro_controller_get_media_list(controller, target);
    channel->send(Get_packet("media:list", r));
  } else if (name == "thumbnail") {
    r["local"] = local;
    r["data"] = controller.getThumbnailData(ip, path, local);
    channel->send(Get_packet("media:thumbnail", r));
  } else if (name == "info") {
    r["local"] = local;
    r["data"] = controller.getMediaInfoData(ip, path, local);
    channel->send(Get_packet("media:info", r));
  } else if (name == "d_single") {
    std::lock_guard<std::mutex> lock(download_mtx);
    r["local"] = local;
    r["item"] = item;
    r["dir"] = dir;
    r["filename"] = filename;
    r["path"] = controller.getSingleFetchURL(ip, filename, local);
    channel->send(Get_packet("media:d_single", r));
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
    channel->send(Get_packet("media:d_all", r));
  } else {
    channel->send(Get_packet("media:unknown", r));
  }
}
void Preview_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) {
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
    gopro_controller_preview_on(controller, target, port);
    channel->send(Get_packet("preview:start", r));
  } else if (name == "stop") {
    gopro_controller_preview_off(controller, target);
    channel->send(Get_packet("preview:stop", r));
  } else {
    channel->send(Get_packet("preview:unknown", r));
  }
}
