/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"

void gopro_master_preset_switch(AppData& data, const std::string server, const std::string target, int32_t mode) {

}

void gopro_master_locate(AppData& data, const std::string server, const std::string target) {

}

int32_t gopro_master_has_locate(const std::string server, const std::string target) {

}

void gopro_master_apply(const std::string& ip, const std::string& target, const int32_t id, const int32_t value) {

}

void gopro_master_apply(const std::string& ip, const json& res) {

}

void gopro_master_quick_apply(const CameraInfo& target) {

}

void gopro_master_stop_apply(const CameraInfo& target) {

}

bool gopro_master_directory_exists(const std::string& path) {

}

void gopro_master_set_preset_data(json _preset) {

}

int32_t gopro_master_add_preset(const std::string name, json data) {

}

bool gopro_master_get_preset(const std::string name, json& data) {

}

bool gopro_master_remove_preset(const std::string name) {

}

std::vector<std::string> gopro_master_get_preset_names() {

}
