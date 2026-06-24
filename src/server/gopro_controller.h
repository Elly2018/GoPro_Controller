/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
 */
#pragma once
#ifndef GOPRO_CONTROLLER_H
#define GOPRO_CONTROLLER_H

#include "../common/camera_code.h"
#include "../common/iphelper.h"
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

using json = nlohmann::json;
std::string getPacket(std::string key, json data);

typedef std::pair<std::string, std::string> SingleResponse;

struct gopro_element {
  static constexpr uint64_t ip_str_length = 24UL;
  static constexpr uint64_t name_str_length = 256UL;

  bool exist;
  bool alive;
  char ip[ip_str_length];
  char name[name_str_length];
};

struct gopro_controller {
  static constexpr uint64_t client_limit = 128UL;

  bool applying_cancel = false;
  mdns_cpp::mDNS mdns;
  bool mdns_scaned = false;
  std::array<std::thread, client_limit> scan_workers;
  std::array<gopro_element, client_limit> camera_ips;
  std::mutex ips_mutex;
  std::mutex ips_alive_mutex;
  std::unordered_map<std::string, json> camera_hw;
  bool scanning;
};

void gopro_controller_init(gopro_controller& controller) noexcept;
void gopro_controller_dispose(gopro_controller& controller) noexcept;
void gopro_controller_update(gopro_controller& controller) noexcept;

void gopro_controller_scanCameras(gopro_controller& controller) noexcept;
void gopro_controller_cleanCameras(gopro_controller& controller) noexcept;
void gopro_controller_renameCameras(gopro_controller& controller, std::string ip, std::string name) noexcept;
void gopro_controller_addCameras(gopro_controller& controller, std::string serial) noexcept;
void gopro_controller_deleteCameras(gopro_controller& controller, std::string ip) noexcept;

void gopro_controller_setPreset(gopro_controller& controller, std::string target, int32_t mode) noexcept;
void gopro_controller_reboot(gopro_controller& controller, std::string target) noexcept;
void gopro_controller_shutdown(gopro_controller& controller, std::string target) noexcept;
void gopro_controller_keep_alive(gopro_controller& controller, std::string target) noexcept;
void gopro_controller_usb(gopro_controller& controller, std::string target, bool ison) noexcept;
void gopro_controller_datetime(gopro_controller& controller, std::string target) noexcept;
void gopro_controller_zoom(gopro_controller& controller, std::string target, int32_t value) noexcept;
void gopro_controller_shutter(gopro_controller& controller, std::string target, bool isstart) noexcept;
void gopro_controller_locate(gopro_controller& controller, std::string target, bool ison) noexcept;
std::string gopro_controller_getAllIP(gopro_controller& controller) noexcept;
  
std::string gopro_controller_queryStatus(gopro_controller& controller, std::string target) noexcept;
std::string gopro_controller_setSetting(gopro_controller& controller, std::string target, int32_t ID, std::string value) noexcept;
std::string gopro_controller_setSettingAll(gopro_controller& controller, const std::string source, const std::string target, int32_t preset, json value) noexcept;
void gopro_controller_setSettingCancelAll(gopro_controller& controller) noexcept;

void gopro_controller_webcamMode(gopro_controller& controller, std::string target) noexcept;
void gopro_controller_webcamUnMode(gopro_controller& controller, std::string target) noexcept;
void gopro_controller_webcamOn(gopro_controller& controller, std::string target, int32_t startPort, int32_t res, int32_t fov, bool TS) noexcept;
void gopro_controller_webcamOff(gopro_controller& controller, std::string target) noexcept;
std::string gopro_controller_webcamStatus(gopro_controller& controller, std::string target) noexcept;
std::string gopro_controller_webcamVersion(gopro_controller& controller, std::string target) noexcept;

void gopro_controller_previewOn(gopro_controller& controller, std::string target, int32_t port) noexcept;
void gopro_controller_previewOff(gopro_controller& controller, std::string target) noexcept;

std::string gopro_controller_getMediaList(gopro_controller& controller, std::string target) noexcept;
std::string gopro_controller_getLastMedia(gopro_controller& controller, std::string target) noexcept;
std::string gopro_controller_getFetchURL(gopro_controller& controller, std::string target_ip, bool is_local) noexcept;
std::string gopro_controller_getSingleFetchURL(gopro_controller& controller, std::string target_ip, const std::string filename, bool is_local) noexcept;
std::vector<SingleResponse> gopro_controller_getAllFetchURL(gopro_controller& controller, std::string target_ip, std::vector<std::string> filenames, bool is_local) noexcept;
std::string gopro_controller_getThumbnailData(gopro_controller& controller, std::string target_ip, std::string path, bool is_local) noexcept;
std::string gopro_controller_getMediaInfoData(gopro_controller& controller, std::string target_ip, std::string path, bool is_local) noexcept;

#endif