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

void gopro_controller_local_load_record(gopro_controller& controller);
void gopro_controller_local_update_record(gopro_controller& controller);
void gopro_controller_local_setAllPreset(gopro_controller& controller, std::vector<std::string> targets, const int32_t mode);
void gopro_controller_local_set_preset(gopro_controller& controller, const std::string target, const int32_t mode);
void gopro_controller_local_set_preset(gopro_controller& controller, const std::vector<std::string> target, const int32_t mode);
void gopro_controller_local_reboot(gopro_controller& controller, const std::vector<std::string> targets);
void gopro_controller_local_reboot(gopro_controller& controller, const std::string target);
void gopro_controller_local_shutdown(gopro_controller& controller, const std::vector<std::string> targets);
void gopro_controller_local_shutdown(gopro_controller& controller, const std::string target);
void gopro_controller_local_keep_alive(gopro_controller& controller, const std::vector<std::string> targets);
void gopro_controller_local_keep_alive(gopro_controller& controller, const std::string target);
void gopro_controller_local_usb(gopro_controller& controller, const std::vector<std::string> targets, const bool ison);
void gopro_controller_local_usb(gopro_controller& controller, const std::string target, const bool ison);
void gopro_controller_local_datetime(gopro_controller& controller, const std::vector<std::string> targets);
void gopro_controller_local_datetime(gopro_controller& controller, const std::string target);
void gopro_controller_local_zoom(gopro_controller& controller, const std::vector<std::string> targets, const int32_t value);
void gopro_controller_local_zoom(gopro_controller& controller, const std::string target, int32_t value);
void gopro_controller_local_shutter(gopro_controller& controller, const std::vector<std::string> targets, const bool isstart);
void gopro_controller_local_shutter(gopro_controller& controller, const std::string target, const bool isstart);
void gopro_controller_local_locate(gopro_controller& controller, std::string target, bool ison);

std::vector<SingleResponse> gopro_controller_local_query_status(gopro_controller& controller, const std::vector<std::string> targets);
SingleResponse gopro_controller_local_query_status(gopro_controller& controller, const std::string target);
std::vector<SingleResponse> gopro_controller_local_query_HW(gopro_controller& controller, std::vector<std::string> targets);
SingleResponse gopro_controller_local_query_HW(gopro_controller& controller, std::string target);
std::vector<SingleResponse> gopro_controller_local_set_setting(gopro_controller& controller, const std::vector<std::string> targets, const int32_t ID, const std::string value);
SingleResponse gopro_controller_local_set_setting(gopro_controller& controller, const std::string target, const int32_t ID, const std::string value);
std::vector<SingleResponse> gopro_controller_local_set_setting_preset(gopro_controller& controller, const std::vector<std::string> targets, const int32_t preset, json res);
std::vector<SingleResponse> gopro_controller_local_set_setting_preset(gopro_controller& controller, const std::string target, const int32_t preset, json res);
std::vector<SingleResponse> gopro_controller_local_set_setting_utility(gopro_controller& controller, const std::string target, json res, const std::vector<int32_t> setting_ids);

void gopro_controller_local_webcam_mode(gopro_controller& controller, std::vector<std::string> targets);
void gopro_controller_local_webcam_mode(gopro_controller& controller, std::string target);
void gopro_controller_local_webcam_mode_off(gopro_controller& controller, std::vector<std::string> targets);
void gopro_controller_local_webcam_mode_off(gopro_controller& controller, std::string target);
void gopro_controller_local_webcam_on(gopro_controller& controller, std::vector<std::string> targets, int32_t startPort, int32_t res, int32_t fov, bool TS);
void gopro_controller_local_webcam_on(gopro_controller& controller, std::string target, int32_t startPort, int32_t res, int32_t fov, bool TS);
void gopro_controller_local_webcam_off(gopro_controller& controller, std::vector<std::string> targets);
void gopro_controller_local_webcam_off(gopro_controller& controller, std::string target);
SingleResponse gopro_controller_local_webcamStatus(gopro_controller& controller, std::string target);
SingleResponse gopro_controller_local_webcamVersion(gopro_controller& controller, std::string target);

void gopro_controller_local_preview_on(gopro_controller& controller, const std::vector<std::string> targets, const int32_t port);
void gopro_controller_local_preview_on(gopro_controller& controller, const std::string target, const int32_t port);
void gopro_controller_local_preview_off(gopro_controller& controller, const std::vector<std::string> targets);
void gopro_controller_local_preview_off(gopro_controller& controller, const std::string target);

std::vector<SingleResponse> gopro_controller_local_get_media_list(gopro_controller& controller, const std::vector<std::string> targets);
SingleResponse gopro_controller_local_get_media_list(gopro_controller& controller, const std::string target);
std::vector<SingleResponse> gopro_controller_local_get_last_media(gopro_controller& controller, const std::vector<std::string> targets);
SingleResponse gopro_controller_local_get_last_media(gopro_controller& controller, const std::string target);

SingleResponse gopro_controller_local_get_response(gopro_controller& controller, const std::string target, const std::string suffix);
std::vector<SingleResponse> gopro_controller_local_get_responses(gopro_controller& controller, const std::vector<std::string> targets, const std::string suffix);
std::string gopro_controller_local_base64_encode(gopro_controller& controller, const std::vector<u_char> &data);
int32_t gopro_controller_local_get_current_model(gopro_controller& controller, json hwinfo);

bool gopro_controller_local_element_exist(gopro_controller& controller, const std::string ip, bool should_be_alive = false);
int32_t gopro_controller_local_element_add(gopro_controller& controller, const std::string ip);
bool gopro_controller_local_element_remove(gopro_controller& controller, const std::string ip);
bool gopro_controller_local_element_clean(gopro_controller& controller);
int32_t gopro_controller_local_element_have_slot(gopro_controller& controller);
int32_t gopro_controller_local_element_find(gopro_controller& controller, const std::string ip);
std::vector<std::string> gopro_controller_local_element_alives(gopro_controller& controller);
void gopro_controller_local_element_set_hw(gopro_controller& controller, const std::string ip, json value);
json gopro_controller_local_element_get_hw(gopro_controller& controller, const std::string ip);

#endif