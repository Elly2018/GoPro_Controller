/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <mutex>
#include <thread>
#include <functional>
#include "../common/iphelper.h"
#include "../common/camera_code.h"
#include "../common/thread_safe_queue.h"
#include "data/state.h"
#include "data/camera_info.h"
#include "data/server_connection.h"
#include "data/app.h"

typedef struct AppData;

typedef void (*camera_media_list_feedback)(AppData& data, const std::vector<Media_info> media_list);
typedef void (*camera_setting_feedback)(AppData& data, const std::string ip, const json setting);
typedef void (*camera_status_feedback)(AppData& data, const std::string ip, const json status);
typedef void (*camera_hw_feedback)(AppData& data, const std::string ip, const json hw);
typedef void (*camera_log_feedback)(AppData& data, const std::string key, const std::string value);
typedef void (*camera_preset_save)(AppData& data);
typedef void (*camera_apply_all_feedback)(AppData& data);

struct Locate_data {
    char server[32];
    char ip[32];
    bool vaild;
}

struct Download_media_parameters {
    bool put_finish;
    int32_t type;
    int32_t c_count;
    char dir[512];
};

struct Gopro_master {
    std::mutex camera_mtx;
    std::mutex locate_mtx;
    std::mutex server_mtx;

    Locate_data locates;
    
    std::vector<Camera_info> cameras = std::vector<Camera_info>(1024);
    std::vector<Server_connection> servers = std::vector<Server_connection>(32);
    thread_safe_queue<std::pair<std::string, std::string>> msg_queue;
    
    std::unordered_map<std::string, bool> ip_query_finish = std::unordered_map<std::string, bool>();
    std::unordered_map<std::string, bool> state_query_finish = std::unordered_map<std::string, bool>();
    std::unordered_map<std::string, bool> media_query_finish = std::unordered_map<std::string, bool>();

    camera_media_list_feedback feedback_camera_media_list = NULL;
    camera_setting_feedback feedback_camera_setting = NULL;
    camera_status_feedback feedback_camera_status = NULL;
    camera_hw_feedback feedback_camera_hw = NULL;
    camera_log_feedback feedback_camera_log = NULL;
    camera_preset_save feedback_camera_preset_save = NULL;
    camera_apply_all_feedback feedback_camera_apply_all = NULL;
    json preset_ptr;

    std::thread downloading_thread;
    std::atomic_char32_t downloading_media_flag = 0;
    std::atomic_char32_t downloading_media_total;
    std::atomic_char32_t downloading_media_done;
};

void gopro_master_release(AppData& data);
void gopro_master_update(AppData& data);

bool gopro_master_add_server(AppData& data, const std::string& ip);
void gopro_master_reconnect(AppData& data);
void gopro_master_reconnect(AppData& data, const std::string& ip);
void gopro_master_disconnect(AppData& data);
void gopro_master_disconnect(AppData& data, const std::string& ip);
void gopro_master_clean(AppData& data);
void gopro_master_clean(AppData& data, const std::string& ip);

void gopro_master_clean_cameras_from_server(AppData& data, const std::string server);
void gopro_master_replace_camera_from_server(AppData& data, const std::string server, const std::vector<std::string> ips);

void gopro_master_packet_sender(AppData& data, const std::string key, const std::string server, const std::string command, const std::string target, const std::string value = "");
void gopro_master_command_only(AppData& data, const std::string command, const std::string target = "");
void gopro_master_command_only(AppData& data, const std::string server, const std::string command, const std::string target = "");
void gopro_master_command_with_value(AppData& data, const std::string command, std::string target, const std::string value);
void gopro_master_query_only(AppData& data, const std::string command, const std::string target = "");
void gopro_master_query_only(AppData& data, const std::string server, const std::string command, const std::string target = "");
void gopro_master_webcam_only(AppData& data, const std::string command, const std::string target = "");
void gopro_master_webcam_only(AppData& data, const std::string server, const std::string command, const std::string target = "");
void gopro_master_webcam_start(AppData& data, const std::string server);
void gopro_master_preview_start(AppData& data, const std::string server, const std::string target);
void gopro_master_preview_end(AppData& data, const std::string server, const std::string target);
void gopro_master_media_only(AppData& data, const std::string command, std::string target = "");
void gopro_master_download_last_media(AppData& data, const std::string ip, const Download_media_parameters params);
void gopro_master_download_all_media(AppData& data, const std::string server, const std::string ip, const std::string filepath, const std::vector<Media_info> media_list);
void gopro_master_download_single_media(AppData& data, const std::string server, const std::string ip, const std::string filepath, const Media_info media);
void gopro_master_get_media_info(AppData& data, const std::string server, const std::string ip, const std::string path);
void gopro_master_get_media_list(AppData& data, const std::string server, const std::string ip);

void gopro_master_process_message(AppData& data, const std::string& ip, const std::string& msg);
void gopro_master_send_2_all(AppData& data, const std::string& msg);

void gopro_master_preset_switch(AppData& data, const std::string server, const std::string target, int32_t mode);
void gopro_master_locate(AppData& data, const std::string server, const std::string target);
void gopro_master_apply(AppData& data, const std::string& ip, const std::string& target, const int32_t id, const int32_t value);
void gopro_master_apply(AppData& data, const std::string& ip, const json& res);
void gopro_master_quick_apply(AppData& data, const CameraInfo& target);
void gopro_master_stop_apply(AppData& data, const CameraInfo& target);
bool gopro_master_directory_exists(const std::string& path);
int32_t gopro_master_add_preset(AppData& data, const std::string name, json data);
bool gopro_master_get_preset(AppData& data, const std::string name, json& data);
bool gopro_master_remove_preset(AppData& data, const std::string name);
std::vector<std::string> gopro_master_get_preset_names(AppData& data);

bool gopro_master_get_settings_from_camera(AppData& data, const Camera_info& target, json& res);
bool gopro_master_get_status_from_camera(AppData& data, const Camera_info& target, json& res);
std::string gopro_master_get_bar_info(AppData& data, const Camera_info &c);
uint32_t gopro_master_get_server_count(AppData& data);
int32_t gopro_master_find_server(AppData& data, const std::string ip);
int32_t gopro_master_find_camera(AppData& data, const std::string server, const std::string ip);
std::vector<u_char> gopro_master_decode_base64(const std::string& input);
