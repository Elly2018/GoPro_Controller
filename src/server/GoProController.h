/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
 */
/*
 * In order to follow the memory safety standard. the vector part should have
 * Hard limit.
 */
#pragma once

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

using json = nlohmann::json;
std::string getPacket(std::string key, json data);

typedef std::pair<std::string, std::string> SingleResponse;

///
/// The middleware server worker, the hero
/// The cpp files break into two folder, and base on implementation detail to
/// seperate cpp files
/// - controller (public methods)
/// - private (private methods)
///
class GoProController {
public:
#pragma region public methods
  GoProController();
  GoProController(const GoProController &) = delete;
  GoProController &operator=(const GoProController &) = delete;
  virtual ~GoProController();
  ///
  /// Spawn a background worker for
  /// - Check camera alive or not
  /// - - Base on the state, put it in the "camera_alive_ips" variable
  ///
  void update();

#pragma region Camera part of calls
  ///
  /// Using mdns feature to catch all gopro services and store the ip addresses
  ///
  void scanCameras();
  ///
  /// Clear the array of IP address
  ///
  void cleanCameras();
  ///
  /// Rename the camera by ip input
  /// It will change the variable "camera_name", and store to the record and
  /// keep it in the disk
  ///
  void renameCameras(std::string ip, std::string name);
  ///
  /// Adding camera base on serial number
  /// The serial string must satisfied rules below
  /// - Must be number charachers
  /// - Must at least 3 length long (This will took last 3 charachers anyway)
  ///
  void addCameras(std::string serial);
  ///
  /// Delete camera by IP address
  ///
  void deleteCameras(std::string ip);
#pragma endregion

#pragma region Control part of calls
  ///
  /// Set the camera preset (example: 0:video, 65536:photo_single)
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  /// - mode: Mode ID (check src/common/camera_other.h for more details)
  ///
  void setPreset(std::string target, int32_t mode);
  ///
  /// Send reboot command for target camera
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  void reboot(std::string target);
  ///
  /// Send shutdown command for target camera
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  void shutdown(std::string target);
  ///
  /// Send keep alive command for target camera
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  void keep_alive(std::string target);
  ///
  /// Send the usb control command to the camera
  /// The most obvious command when send off
  /// If ison is off the camera will go to black screen
  /// If ison is on the camera will go to normal camera control screen
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  /// - ison: usb control turn on or off
  ///
  void usb(std::string target, bool ison);
  ///
  /// Send the datetime command to the camera
  /// The datetime value will base on the machine where it run
  /// Better sync it with network before doing yeah ?
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  void datetime(std::string target);
  ///
  /// Send the zoom command to the camera
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  /// - value: The zoom value, should be in the range [0...100]
  ///
  void zoom(std::string target, int32_t value);
  ///
  /// Send the shutter command to the camera
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  /// - isstart: shutter turn on or off
  ///
  void shutter(std::string target, bool isstart);
  ///
  /// Send the locate function to the camera
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  /// - ison: locate turn on or off
  ///
  void locate(std::string target, bool ison);
  ///
  /// Get the current ip list record, It looks up variable "camera_ips"
  ///
  /// Return:
  /// serialized json
  /// ["IP1", "IP2", "IP3"]
  ///
  std::string getAllIP();
#pragma endregion

#pragma region Status part of calls
  ///
  /// Get the status from the target camera
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  /// Return:
  /// serialized json
  /// [{
  ///    ip: "IP string",
  ///    status: { /** settings and status */ },
  ///    hw: { /** Hardware info */ }
  /// }]
  ///
  std::string queryStatus(std::string target);
  ///
  /// Change setting to a camera
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  /// - ID: the setting id
  /// - value: the setting option id
  ///
  /// Return:
  /// serialized json
  /// [{
  ///    ip: "IP string",
  ///    status: { /** settings and status */ }
  /// }]
  ///
  std::string setSetting(std::string target, int32_t ID, std::string value);
  ///
  /// Trying to apply a json object of setting value map to a camera
  ///
  /// Args:
  /// - source: The source of the json value (Camera ip, can be empty)
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  /// - preset: The preset registered
  /// - - This means camera mode (0 or 65536 or etc... check
  /// src/common/camera_other.h)
  /// - - Affect the filter which only apply base on this setting
  /// - - For example if preset=0 (video), then it will apply video setting, but
  /// photo setting will not apply here
  /// - value: the setting json object
  /// - - Should be a json with 3 keys (model (int32_t), preset (int32_t),
  /// setting (json))
  ///
  /// Return:
  /// serialized json
  /// [{
  ///    ip: "IP string",
  ///    status: { /** settings and status */ }
  /// }]
  ///
  std::string setSettingAll(const std::string source, const std::string target,
                            int32_t preset, json value);
  void setSettingCancelAll();
#pragma endregion

#pragma region Webcam part of calls
  ///
  /// Open webcam mode
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  void webcamMode(std::string target);
  ///
  /// Close webcam mode
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  void webcamUnMode(std::string target);
  ///
  /// Start webcam
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  /// - startPort: using port
  /// - res: resolution
  /// - fov: field of view
  /// - TS: using ts or rtmp
  ///
  void webcamOn(std::string target, int32_t startPort, int32_t res, int32_t fov,
                bool TS);
  ///
  /// Stop webcam
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  void webcamOff(std::string target);
  ///
  /// Get current webcam status
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  std::string webcamStatus(std::string target);
  ///
  /// Get current webcam version
  ///
  /// Args:
  /// - target: Camera IP address
  /// - - if this is empty, This mean it will send to all camera
  ///
  std::string webcamVersion(std::string target);
#pragma endregion

#pragma region Preview part of calls
  ///
  /// Open preview on the camera
  ///
  /// Args:
  /// - target: The Camera IP
  /// - port: The open port
  ///
  void previewOn(std::string target, int32_t port);
  ///
  /// Close preview on the camera
  ///
  /// Args:
  /// - target: The Camera IP
  ///
  void previewOff(std::string target);
#pragma endregion

#pragma region Media part of calls
  ///
  /// Received target camera media list, basically the whole list
  ///
  /// Args:
  /// - target: Camera ip
  ///
  std::string getMediaList(std::string target);
  ///
  /// Received target camera last store media
  ///
  /// Args:
  /// - target: Camera ip
  ///
  std::string getLastMedia(std::string target);
  ///
  /// Get the download link for the last media resource
  ///
  /// Notice:
  /// ! If master is not at the same machine as where this server hosting,
  /// ! It will trying to download to the /res folder as temp, and using HTTP
  /// static router as a download link ! This might be slower than you think,
  /// since you have to wait it to finish ? But if they are the same machine,
  /// the download link will go straight to the GoPro camera provide http URL ?
  /// Which means no buffer waiting time.
  ///
  /// TODO:
  /// - Make pipe download possible. Reduce time to download the media
  ///
  /// Args:
  /// - target
  ///
  std::string getFetchURL(std::string target_ip, bool is_local);
  std::string getSingleFetchURL(std::string target_ip,
                                const std::string filename, bool is_local);
  std::vector<std::pair<std::string, std::string>>
  getAllFetchURL(std::string target_ip, std::vector<std::string> filenames,
                 bool is_local);
  std::string getThumbnailData(std::string target_ip, std::string path,
                               bool is_local);
  std::string getMediaInfoData(std::string target_ip, std::string path,
                               bool is_local);
#pragma endregion
#pragma endregion

protected:
#pragma region protected
#pragma region IO
  ///
  /// Loading record from disk
  ///
  void _loadRecord();
  ///
  /// Store record to disk
  ///
  void _updateRecord();
#pragma endregion

#pragma region Control part of calls
  void _setAllPreset(std::vector<std::string> targets, int32_t mode);
  void _setPreset(std::string target, int32_t mode);
  void _rebootAll(std::vector<std::string> targets);
  void _reboot(std::string target);
  void _shutdownAll(std::vector<std::string> targets);
  void _shutdown(std::string target);
  void _keepAliveAll(std::vector<std::string> targets);
  void _keepAlive(std::string target);
  void _usbAll(std::vector<std::string> targets, bool ison);
  void _usb(std::string target, bool ison);
  void _datetimeAll(std::vector<std::string> targets);
  void _datetime(std::string target);
  void _zoomAll(std::vector<std::string> targets, int32_t value);
  void _zoom(std::string target, int32_t value);
  void _shutterAll(std::vector<std::string> targets, bool isstart);
  void _shutter(std::string target, bool isstart);
  void _locate(std::string target, bool ison);
#pragma endregion

#pragma region Status part of calls
  std::vector<SingleResponse> _queryAllStatus(std::vector<std::string> targets);
  SingleResponse _queryStatus(std::string target);
  std::vector<SingleResponse> _queryAllHW(std::vector<std::string> targets);
  SingleResponse _queryHW(std::string target);
  std::vector<SingleResponse> _setAllSetting(std::vector<std::string> targets,
                                             int32_t ID, std::string value);
  SingleResponse _setSetting(std::string target, int32_t ID, std::string value);
  std::vector<SingleResponse> _setAllSetting(std::vector<std::string> targets,
                                             int32_t preset, json res);
  std::vector<SingleResponse> _setSetting(std::string target, int32_t preset,
                                          json res);
  std::vector<SingleResponse>
  _setSetting_utility(std::string target, json res,
                      std::vector<int32_t> setting_ids);
#pragma endregion

#pragma region Webcam part of calls
  void _webcamAllMode(std::vector<std::string> targets);
  void _webcamMode(std::string target);
  void _webcamAllUnMode(std::vector<std::string> targets);
  void _webcamUnMode(std::string target);
  void _webcamAllOn(std::vector<std::string> targets, int32_t startPort,
                    int32_t res, int32_t fov, bool TS);
  void _webcamOn(std::string target, int32_t startPort, int32_t res,
                 int32_t fov, bool TS);
  void _webcamAllOff(std::vector<std::string> targets);
  void _webcamOff(std::string target);
  SingleResponse _webcamStatus(std::string target);
  SingleResponse _webcamVersion(std::string target);
#pragma endregion

#pragma region Preview part of calls
  void _previewAllOn(std::vector<std::string> targets, int32_t port);
  void _previewOn(std::string target, int32_t port);
  void _previewAllOff(std::vector<std::string> targets);
  void _previewOff(std::string target);
#pragma endregion
  // Media part of calls
  std::vector<SingleResponse>
  _getAllMediaList(std::vector<std::string> targets);
  SingleResponse _getMediaList(std::string target);
  std::vector<SingleResponse>
  _getAllLastMedia(std::vector<std::string> targets);
  SingleResponse _getLastMedia(std::string target);
  // Utility calls
  SingleResponse _getSingleResponse(std::string target, std::string suffix);
  std::vector<SingleResponse> _getAllResponse(std::vector<std::string> targets,
                                              std::string suffix);
  std::string base64_encode(const std::vector<u_char> &data);

  int32_t _get_current_model(json hwinfo);
#pragma endregion

private:
#pragma region private variable
  ///
  /// State of current server
  /// Is applying something
  ///
  std::atomic<bool> applying_cancel = false;
  ///
  /// The handle for mdns service manager
  ///
  mdns_cpp::mDNS mdns;
  ///
  /// Is it scanning right now or not
  ///
  bool mdns_scaned = false;
  ///
  /// mDNS scanning worker
  ///
  std::vector<std::thread> scan_workers;
  ///
  /// IP address record
  ///
  std::vector<std::string> camera_ips;
  ///
  /// IP address record (Alive)
  ///
  std::vector<std::string> camera_alive_ips;
  ///
  /// IP address record (Thread Guard)
  ///
  std::mutex ips_mutex;
  ///
  /// IP address record (Alive) (Thread Guard)
  ///
  std::mutex ips_alive_mutex;
  ///
  /// IP : Hardware info json data
  ///
  std::unordered_map<std::string, json> camera_hw;
  ///
  /// IP : Name
  ///
  std::unordered_map<std::string, std::string> camera_name;
  ///
  /// To track scanning state if needed
  ///
  std::atomic<bool> scanning{false};
#pragma endregion
};
