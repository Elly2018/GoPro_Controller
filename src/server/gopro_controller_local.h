/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
 */
#pragma once
#ifndef GOPRO_CONTROLLER_LOCAL_H
#define GOPRO_CONTROLLER_LOCAL_H
#include "gopro_controller.h"

void gopro_controller_local_loadRecord(gopro_controller& controller) noexcept;
void gopro_controller_local_updateRecord(gopro_controller& controller) noexcept;
void gopro_controller_local_setAllPreset(gopro_controller& controller, std::vector<std::string> targets, const int32_t mode) noexcept;
void gopro_controller_local_set_preset(gopro_controller& controller, const std::string target, const int32_t mode) noexcept;
void gopro_controller_local_set_preset(gopro_controller& controller, const std::vector<std::string> target, const int32_t mode) noexcept;
void gopro_controller_local_reboot(gopro_controller& controller, const std::vector<std::string> targets) noexcept;
void gopro_controller_local_reboot(gopro_controller& controller, const std::string target) noexcept;
void gopro_controller_local_shutdown(gopro_controller& controller, const std::vector<std::string> targets) noexcept;
void gopro_controller_local_shutdown(gopro_controller& controller, const std::string target) noexcept;
void gopro_controller_local_keep_alive(gopro_controller& controller, const std::vector<std::string> targets) noexcept;
void gopro_controller_local_keep_alive(gopro_controller& controller, const std::string target) noexcept;
void gopro_controller_local_usb(gopro_controller& controller, const std::vector<std::string> targets, const bool ison) noexcept;
void gopro_controller_local_usb(gopro_controller& controller, const std::string target, const bool ison) noexcept;
void gopro_controller_local_datetime(gopro_controller& controller, const std::vector<std::string> targets) noexcept;
void gopro_controller_local_datetime(gopro_controller& controller, const std::string target) noexcept;
void gopro_controller_local_zoom(gopro_controller& controller, const std::vector<std::string> targets, const int32_t value) noexcept;
void gopro_controller_local_zoom(gopro_controller& controller, const std::string target, int32_t value) noexcept;
void gopro_controller_local_shutter(gopro_controller& controller, const std::vector<std::string> targets, const bool isstart) noexcept;
void gopro_controller_local_shutter(gopro_controller& controller, const std::string target, const bool isstart) noexcept;
void gopro_controller_local_locate(gopro_controller& controller, std::string target, bool ison) noexcept;

std::vector<SingleResponse> gopro_controller_local_query_status(gopro_controller& controller, const std::vector<std::string> targets) noexcept;
SingleResponse gopro_controller_local_query_status(gopro_controller& controller, const std::string target) noexcept;
std::vector<SingleResponse> gopro_controller_local_queryAllHW(gopro_controller& controller, std::vector<std::string> targets) noexcept;
SingleResponse gopro_controller_local_queryHW(gopro_controller& controller, std::string target) noexcept;
std::vector<SingleResponse> gopro_controller_local_setAllSetting(gopro_controller& controller, std::vector<std::string> targets, int32_t ID, std::string value) noexcept;
SingleResponse gopro_controller_local_setSetting(gopro_controller& controller, std::string target, int32_t ID, std::string value) noexcept;
std::vector<SingleResponse> gopro_controller_local_setAllSetting(gopro_controller& controller, std::vector<std::string> targets, int32_t preset, json res) noexcept;
std::vector<SingleResponse> gopro_controller_local_setSetting(gopro_controller& controller, std::string target, int32_t preset, json res) noexcept;
std::vector<SingleResponse> gopro_controller_local_setSetting_utility(gopro_controller& controller, std::string target, json res, std::vector<int32_t> setting_ids) noexcept;

void gopro_controller_local_webcamAllMode(gopro_controller& controller, std::vector<std::string> targets) noexcept;
void gopro_controller_local_webcamMode(gopro_controller& controller, std::string target) noexcept;
void gopro_controller_local_webcamAllUnMode(gopro_controller& controller, std::vector<std::string> targets) noexcept;
void gopro_controller_local_webcamUnMode(gopro_controller& controller, std::string target) noexcept;
void gopro_controller_local_webcamAllOn(gopro_controller& controller, std::vector<std::string> targets, int32_t startPort, int32_t res, int32_t fov, bool TS) noexcept;
void gopro_controller_local_webcamOn(gopro_controller& controller, std::string target, int32_t startPort, int32_t res, int32_t fov, bool TS) noexcept;
void gopro_controller_local_webcamAllOff(gopro_controller& controller, std::vector<std::string> targets) noexcept;
void gopro_controller_local_webcamOff(gopro_controller& controller, std::string target) noexcept;
SingleResponse gopro_controller_local_webcamStatus(gopro_controller& controller, std::string target) noexcept;
SingleResponse gopro_controller_local_webcamVersion(gopro_controller& controller, std::string target) noexcept;

void gopro_controller_local_previewAllOn(gopro_controller& controller, std::vector<std::string> targets, int32_t port) noexcept;
void gopro_controller_local_previewOn(gopro_controller& controller, std::string target, int32_t port) noexcept;
void gopro_controller_local_previewAllOff(gopro_controller& controller, std::vector<std::string> targets) noexcept;
void gopro_controller_local_previewOff(gopro_controller& controller, std::string target) noexcept;

std::vector<SingleResponse> gopro_controller_local_getAllMediaList(gopro_controller& controller, std::vector<std::string> targets) noexcept;
SingleResponse gopro_controller_local_getMediaList(gopro_controller& controller, std::string target) noexcept;
std::vector<SingleResponse> gopro_controller_local_getAllLastMedia(gopro_controller& controller, std::vector<std::string> targets) noexcept;
SingleResponse gopro_controller_local_getLastMedia(gopro_controller& controller, std::string target) noexcept;

SingleResponse gopro_controller_local_getSingleResponse(gopro_controller& controller, std::string target, std::string suffix) noexcept;
std::vector<SingleResponse> gopro_controller_local_getAllResponse(gopro_controller& controller, std::vector<std::string> targets, std::string suffix) noexcept;
std::string gopro_controller_local_base64_encode(gopro_controller& controller, const std::vector<u_char> &data) noexcept;
int32_t gopro_controller_local_get_current_model(gopro_controller& controller, json hwinfo) noexcept;

bool gopro_controller_local_element_exist(gopro_controller& controller, const std::string ip, bool should_be_alive = false) noexcept;
int32_t gopro_controller_local_element_add(gopro_controller& controller, const std::string ip) noexcept;
bool gopro_controller_local_element_remove(gopro_controller& controller, const std::string ip) noexcept;
bool gopro_controller_local_element_clean(gopro_controller& controller) noexcept;
int32_t gopro_controller_local_element_have_slot(gopro_controller& controller) noexcept;
int32_t gopro_controller_local_element_find(gopro_controller& controller, const std::string ip) noexcept;
std::vector<std::string> gopro_controller_local_element_alives(gopro_controller& controller) noexcept;
void gopro_controller_local_element_set_hw(gopro_controller& controller, const std::string ip, json value) noexcept;
json gopro_controller_local_element_get_hw(gopro_controller& controller, const std::string ip) noexcept;

#endif