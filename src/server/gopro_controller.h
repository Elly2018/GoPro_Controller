/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
 */
#pragma once
#ifndef GOPRO_CONTROLLER_H
#define GOPRO_CONTROLLER_H
#include "hv/requests.h"
#include "mdns_cpp/logger.hpp"
#include "mdns_cpp/mdns.hpp"
#include <atomic>
#include <iostream>
#include <list>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <array>
#include "../common/camera_code.h"
#include "../common/iphelper.h"
#include "../common/utility.h"

using json = nlohmann::json;

typedef std::pair<std::string, json> SingleResponse;

enum class Thread_state {
  NONE = 0,
  PROCESSING = 1,
  FINISHED = 2,
};

struct gopro_element {
  static constexpr uint64_t ip_str_length = 24UL;
  static constexpr uint64_t name_str_length = 256UL;
  static constexpr uint64_t hw_str_length = 1024UL;

  bool exist;
  bool alive;
  char ip[ip_str_length];
  char name[name_str_length];
  char hw[hw_str_length];
};

struct gopro_controller {
  static constexpr uint64_t client_limit = 128UL;

  bool shutdown;
  bool applying_cancel;
  mdns_cpp::mDNS mdns;
  bool mdns_event_registered;
  std::thread scan_thread;
  Thread_state scan_thread_state;
  std::thread ping_thread;
  Thread_state ping_thread_state;
  std::thread command_thread;
  Thread_state command_thread_state;
  std::thread apply_thread;
  Thread_state apply_thread_state;
  std::array<gopro_element, client_limit> camera_elements;
  std::mutex ips_mutex;
  std::mutex ips_alive_mutex;
  std::unordered_map<std::string, json> camera_hw;
  bool scanning;
};

void gopro_controller_init(gopro_controller& controller);
void gopro_controller_dispose(gopro_controller& controller);
void gopro_controller_update(gopro_controller& controller);
void gopro_controller_ping(gopro_controller& controller);

void gopro_controller_scan_cameras(gopro_controller& controller);
void gopro_controller_clean_cameras(gopro_controller& controller);
void gopro_controller_rename_cameras(gopro_controller& controller, const std::string ip, const std::string name);
void gopro_controller_add_cameras(gopro_controller& controller, const std::string serial);
void gopro_controller_delete_cameras(gopro_controller& controller, const std::string ip);

void gopro_controller_set_preset(gopro_controller& controller, const std::string target, const int32_t mode);
void gopro_controller_reboot(gopro_controller& controller, const std::string target);
void gopro_controller_shutdown(gopro_controller& controller, const std::string target);
void gopro_controller_keep_alive(gopro_controller& controller, const std::string target);
void gopro_controller_usb(gopro_controller& controller, const std::string target, const bool is_on);
void gopro_controller_datetime(gopro_controller& controller, const std::string target);
void gopro_controller_zoom(gopro_controller& controller, const std::string target, const int32_t value);
void gopro_controller_shutter(gopro_controller& controller, const std::string target, const bool is_start);
void gopro_controller_locate(gopro_controller& controller, const std::string target, const bool is_on);
json gopro_controller_get_IPs(gopro_controller& controller);
  
json gopro_controller_query_status(gopro_controller& controller, const std::string target);
json gopro_controller_set_setting(gopro_controller& controller, const std::string target, const int32_t ID, const std::string value);
json gopro_controller_set_setting_preset(gopro_controller& controller, const std::string source, const std::string target, const int32_t preset, const json value);
void gopro_controller_set_setting_cancel(gopro_controller& controller);

void gopro_controller_webcam_mode(gopro_controller& controller, const std::string target);
void gopro_controller_webcam_mode_off(gopro_controller& controller, const std::string target);
void gopro_controller_webcam_on(gopro_controller& controller, const std::string target, const int32_t start_port, const int32_t res, const int32_t fov, const bool ts);
void gopro_controller_webcam_off(gopro_controller& controller, const std::string target);
json gopro_controller_webcam_status(gopro_controller& controller, const std::string target);
json gopro_controller_webcam_version(gopro_controller& controller, const std::string target);

void gopro_controller_preview_on(gopro_controller& controller, const std::string target, const int32_t port);
void gopro_controller_preview_off(gopro_controller& controller, const std::string target);

json gopro_controller_get_media_list(gopro_controller& controller, const std::string target);
json gopro_controller_get_last_media(gopro_controller& controller, const std::string target);
std::string gopro_controller_get_fetch_URL(gopro_controller& controller, const std::string target_ip, const bool is_local);
std::string gopro_controller_get_filename_fetch_URL(gopro_controller& controller, const std::string target_ip, const std::string filename, const bool is_local);
std::vector<SingleResponse> gopro_controller_get_filename_fetch_IRL(gopro_controller& controller, const std::string target_ip, const std::vector<std::string> filenames, const bool is_local);
std::string gopro_controller_get_thumbnail_data(gopro_controller& controller, const std::string target_ip, const std::string path, const bool is_local);
std::string gopro_controller_get_media_info_data(gopro_controller& controller, const std::string target_ip, const std::string path, const bool is_local);

#endif