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
#include "data/state.h"
#include "data/camera_info.h"
#include "data/server_connection.h"
#include "data/app.h"

typedef struct AppData;

typedef void (*camera_media_list_feedback)(AppData& data, const std::vector<MediaInfo> media_list);
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
    
    std::unordered_map<std::string, bool> ipQueryFinish = std::unordered_map<std::string, bool>();
    std::unordered_map<std::string, bool> stateQueryFinish = std::unordered_map<std::string, bool>();
    std::unordered_map<std::string, bool> mediaQueryFinish = std::unordered_map<std::string, bool>();

    camera_media_list_feedback feedback_camera_media_list = NULL;
    camera_setting_feedback feedback_camera_setting = NULL;
    camera_status_feedback feedback_camera_status = NULL;
    camera_hw_feedback feedback_camera_hw = NULL;
    camera_log_feedback feedback_camera_log = NULL;
    camera_preset_save feedback_camera_preset_save = NULL;
    camera_apply_all_feedback feedback_camera_apply_all = NULL;
    std::shared_ptr<json> preset_ptr = NULL;

    std::atomic_char32_t downloading_media_flag = 0;
    std::atomic_char32_t downloading_media_total;
    std::atomic_char32_t downloading_media_done;
};

void gopro_master_update(AppData& data);

void gopro_master_add_server(AppData& data, const std::string& ip);
void gopro_master_reconnect(AppData& data);
void gopro_master_reconnect(AppData& data, const std::string& ip);
void gopro_master_disconnect(AppData& data);
void gopro_master_disconnect(AppData& data, const std::string& ip);
void gopro_master_clean(AppData& data);
void gopro_master_clean(AppData& data, const std::string& ip);

void gopro_master_process_message(AppData& data, const std::string& ip, const std::string& msg);
void gopro_master_send_2_all(AppData& data, const std::string& msg);

///
/// GoPro Master Worker
/// Use this hub stuff to control multiple websocket server or camera
/// And handles the message sender and process
/// It also use multithread to decode the message from the websocket instancess
///
class Gopro_master_Old {
public:
    GoProMaster();
    /// 
    /// Destroy the threadings and release the resource under.
    /// 
    ~GoProMaster();

    // ----------------------------------------------------------
    //
    //       Websocket Server Action
    //
    // ----------------------------------------------------------
    /**
     * Menually add websocket server and connect to it
     */
    std::string addServer(const std::string& ip);
    void reconnectAll();
    void disconnectAll();
    void cleanAll();
    void reconnect(const std::string& ip);
    void disconnect(const std::string& ip);
    void clean(const std::string& ip);

    // ----------------------------------------------------------
    //
    //       Websocket Server Sending Signal
    //
    // ----------------------------------------------------------
    void command_only(const std::string command, std::string target = "");
    void command_only(const std::string server, const std::string command, std::string target = "");
    void command_with_value(const std::string command, std::string target, std::string value);
    void query_only(const std::string command, std::string target = "");
    void query_only(const std::string server, const std::string command, std::string target = "");
    void webcam_only(const std::string command, std::string target = "");
    void webcam_only(const std::string server, const std::string command, std::string target = "");
    void webcam_start(const std::string server);
    void preview_start(std::string server, std::string target);
    void preview_end(std::string server, std::string target);
    void media_only(const std::string command, std::string target = "");
    void download_last_media(const std::string ip, const DownloadMediaParameters params);
    void download_all_media(const std::string server, const std::string ip, const std::string folder, std::vector<MediaInfo> media_list);
    void download_single_media(const std::string server, const std::string ip, const std::string filepath, MediaInfo media);
    void get_media_info(const std::string server, const std::string ip, const std::string path);
    void get_media_list(const std::string server, const std::string ip);

    void presetSwitch(const std::string server, const std::string target, int32_t mode);
    void locate(const std::string server, const std::string target);
    int32_t haslocate(const std::string server, const std::string target);
    void apply(const std::string& ip, const std::string& target, const int32_t id, const int32_t value);
    void applyAll(const std::string& ip, const json& res);
    void quickApplyAll(const CameraInfo& target);
    void stopApplyAll(const CameraInfo& target);

    bool directoryExists(const std::string& path);

    void set_preset_data(std::shared_ptr<json> _preset);

    int32_t add_preset(const std::string name, json data);
    bool get_preset(const std::string name, json& data);
    bool remove_preset(const std::string name);
    std::vector<std::string> get_preset_names();
    

    // ----------------------------------------------------------
    //
    //       Cache Data Getter
    //
    // ----------------------------------------------------------
    /**
     * Get current camera record
     */
    const std::vector<std::shared_ptr<CameraInfo>>& getCameras() const;
    /**
     * Get current camera record (Clone, For thread optimization)
     */
    const std::vector<CameraInfo> getCameras_Clone();
    const CameraInfo getCamera_Clone(int32_t index);
    /**
     * Get current websocket server record
     */
    const std::vector<std::shared_ptr<ServerConnection>>& getServers() const;
    const std::vector<ServerConnection> getServers_Clone();
    const ServerConnection getServer_Clone(int32_t index);
private:
    

    /**
     * The background thread for fetch update from all websocket server and update etc...
     */
    void update();
    void processMessage(const std::string& ip, const std::string& msg);
    void sendToAll(const std::string& msg);
    /**
     * Clean all cameras by server ip
     */
    void cleanCameraFromServer(const std::string server);
    /**
     * Base on the new ip list
     * Appending new ip that dont appear old ips
     * Remove ip that does not exists in the new ip list
     */
    void replaceCameraFromServer(const std::string server, const std::vector<std::string> ips);

public:
    void setdone();
    /**
     * We will need to convert the Value ID to index here
     * It's easier for me to display stuff on the gui this way
     */
    bool getSettingsFromCamera(CameraInfo target, json& res);
    bool getStatusFromCamera(CameraInfo target, json& res);
    std::string getBarInfo(const std::shared_ptr<CameraInfo> &c);
    std::string getBarInfo(const CameraInfo &c);

    size_t getServerCount();
    int32_t findServer(const std::string ip);
    int32_t findCamera(const std::string server, const std::string ip);
    std::vector<u_char> decodeBase64(const std::string& input);
};
