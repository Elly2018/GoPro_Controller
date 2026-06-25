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

typedef void (*camera_media_list_feedback)(std::vector<MediaInfo> media_list);
typedef void (*camera_setting_feedback)(std::string ip, json setting);
typedef void (*camera_status_feedback)(std::string ip, json status);
typedef void (*camera_hw_feedback)(std::string ip, json hw);
typedef void (*camera_log_feedback)(std::string key, std::string value);
typedef void (*camera_preset_save)();
typedef void (*camera_apply_all_feedback)();

struct DownloadMediaParameters {
    std::string dir;
    bool put_finish;
    int32_t type;
    int32_t c_count;
};

///
/// GoPro Master Worker
/// Use this hub stuff to control multiple websocket server or camera
/// And handles the message sender and process
/// It also use multithread to decode the message from the websocket instancess
///
class Gopro_master {
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
    /**
     * Reconnect all the exists websocket server record
     */
    void reconnectAll();
    /**
     * Disconnect all the exists websocket server record
     */
    void disconnectAll();
    /**
     * Remove all the disconnected websocket server record
     */
    void cleanAll();
    /**
     * Reconnect server by ip, If not found: do nothing
     */
    void reconnect(const std::string& ip);
    /**
     * Disconnect server by ip, If not found: do nothing
     */
    void disconnect(const std::string& ip);
    /**
     * Remove server by ip, If not found: do nothing
     */
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

    void registerCameraMediaListFeedback(camera_media_list_feedback v);
    ///
    /// Register the feedback event
    /// Called when fetch inspector setting data
    ///
    void registerCameraSettingFeedback(camera_setting_feedback v);
    ///
    /// Register the feedback event
    /// Called when fetch Monitor data
    ///
    void registerCameraStatusFeedback(camera_status_feedback v);
    void registerCameraHWFeedback(camera_hw_feedback v);
    void registerCameraLogFeedback(camera_log_feedback v);
    void registerApplyAllFeedback(camera_apply_all_feedback v);
    void registerSavePreset(camera_preset_save v);
    void set_preset_data(std::shared_ptr<json> _preset);

    int32_t add_preset(const std::string name, json data);
    bool get_preset(const std::string name, json& data);
    bool remove_preset(const std::string name);
    std::vector<std::string> get_preset_names();
    /**
     * Camera list multithread lock guard
     * This will prevent race condition
     */
    std::mutex camera_mtx;
    std::mutex locate_mtx;
    std::mutex server_mtx;

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
     * All cameras record for master
    */
    std::vector<std::shared_ptr<CameraInfo>> cameras;
    /** 
     * All websocket servers record for master
    */
    std::vector<std::shared_ptr<ServerConnection>> servers;
    /**
     * All the locate records
     */
    std::vector<std::pair<std::string, std::string>> locates;
    /**
     * Basically a update thread, THere is a while true loop in it,
     * And when done is true, it automatically escape the loop
     */
    std::thread t1;
    /**
     * Tells thread, if this websocket finish the ip query
     * This prevent command stacking, when last ip fetch is not finish yet
     */
    std::unordered_map<std::string, bool> ipQueryFinish = std::unordered_map<std::string, bool>();
    /**
     * Tells thread, if this websocket finish the state query
     * This prevent command stacking, when last state fetch is not finish yet
     */
    std::unordered_map<std::string, bool> stateQueryFinish = std::unordered_map<std::string, bool>();
    std::unordered_map<std::string, bool> mediaQueryFinish = std::unordered_map<std::string, bool>();
    camera_media_list_feedback _camera_media_list_feedback = NULL;
    camera_setting_feedback _camera_setting_feedback = NULL;
    camera_status_feedback _camera_status_feedback = NULL;
    camera_hw_feedback _camera_hw_feedback = NULL;
    camera_log_feedback _camera_log_feedback = NULL;
    camera_preset_save _camera_preset_save = NULL;
    camera_apply_all_feedback _camera_apply_all_feedback = NULL;
    std::shared_ptr<json> preset_ptr = NULL;
    /**
     * Is app exit or not flag
     */
    bool done = false;
    /**
     * 0: Off
     * 1: On (no finish txt)
     * 2: On (with finish txt)
     */
    std::atomic_char32_t downloading_media_flag = 0;
    std::atomic_char32_t downloading_media_total;
    std::atomic_char32_t downloading_media_done;

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
