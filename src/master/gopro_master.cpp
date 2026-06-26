/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "gopro_master.h"
#include <iostream>
#include <filesystem>
#include "hv/requests.h"
#include "windows/inspector.h"
#include "src/imgui_notify.h"

namespace fs = std::filesystem;

extern std::shared_ptr<GlobalState> global_state;

GoProMaster::GoProMaster() {
    t1 = std::thread(&GoProMaster::update, this);
    std::cout << "GoProMaster created" << std::endl;
}

GoProMaster::~GoProMaster() {
    std::cout << "GoProMaster destroy" << std::endl;
    setdone();
    if(t1.joinable()){
        t1.join();
    }
    for (auto& s : servers) {
        s->client->close();
        std::lock_guard<std::mutex> lock(camera_mtx);
        cleanCameraFromServer(s->ip);
    }
}

std::string GoProMaster::addServer(const std::string& ip) {
    for(auto & s : servers){
        if(s->ip == ip){
            std::cout << "Server " << ip << " already exists." << std::endl;
            return s->ip;
        }
    }

    auto conn = std::make_shared<ServerConnection>();
    conn->client = std::make_shared<hv::WebSocketClient>();
    conn->ip = ip;
    
    conn->client->onopen = [conn, this]() {
        std::cout << "Connected to server: " << conn->ip << std::endl;
        conn->connected = true;
        {
            ImGuiToast toast(ImGuiToastType_Success, 3000);
            toast.set_title("Server Connected");
            toast.set_content("Server ip: %s", conn->ip.c_str());
            ImGui::InsertNotification(toast);
        }
    };
    conn->client->onmessage = [conn, this](const std::string& msg) {
        std::thread([=]() {
            processMessage(conn->ip, msg);
        }).detach();
    };
    conn->client->onclose = [conn, this]() {
        if(conn->connected){
            std::cout << "Disconnected from server: " << conn->ip << std::endl;
            conn->connected = false;
            std::lock_guard<std::mutex> lock(camera_mtx);
            cleanCameraFromServer(conn->ip);
            stateQueryFinish.insert_or_assign(conn->ip, false);
            ipQueryFinish.insert_or_assign(conn->ip, false);
            mediaQueryFinish.insert_or_assign(conn->ip, false);
            {
                ImGuiToast toast(ImGuiToastType_Warning, 3000);
                toast.set_title("Server Disconnected");
                toast.set_content("Server ip: %s", conn->ip.c_str());
                ImGui::InsertNotification(toast);
            }
        }
    };

    servers.push_back(conn);
    return conn->ip;
}

void GoProMaster::reconnectAll() {
    for (auto& s : servers) {
        if (!s->connected) {
            std::cout << "Connecting to " << s->ip << "..." << std::endl;
            // Assuming ws://ip:9090 based on server implementation
            std::string url = "ws://" + s->ip + ":9090";
            s->client->open(url.c_str());
        }
    }
}

void GoProMaster::disconnectAll(){
    for (auto& s : servers) {
        if (s->connected) {
            std::cout << "Disconnect to " << s->ip << "..." << std::endl;
            s->client->close();
        }
    }
}

void GoProMaster::cleanAll(){
    for(int i = servers.size() - 1; i >=0; --i){
        auto& s = servers[i];
        if(!s->connected){
            std::cout << "Cleaning " << s->ip << "..." << std::endl;
            servers.erase(servers.begin() + i);
        }
    }
}

void GoProMaster::reconnect(const std::string& ip){
    for(auto& s : servers){
        if(s->ip == ip && !s->connected){
            std::cout << "Connecting to " << s->ip << "..." << std::endl;
            std::string url = "ws://" + s->ip + ":9090";
            s->client->open(url.c_str());
            break;
        }
    }
}

void GoProMaster::disconnect(const std::string& ip){
    for(auto& s : servers){
        if(s->ip == ip && s->connected){
            std::cout << "Disconnecting to " << s->ip << "..." << std::endl;
            s->client->close();
            break;
        }
    }
}

void GoProMaster::clean(const std::string& ip){
    for(int i = servers.size() - 1; i >=0; --i){
        auto& s = servers[i];
        if(s->ip == ip && !s->connected){
            std::cout << "Cleaning " << s->ip << "..." << std::endl;
            servers.erase(servers.begin() + i);
        }
    }
}

void GoProMaster::command_only(const std::string command, std::string target){
    json data = json::object();
    data["key"] = "command";
    data["value"] = json::object();
    data["value"]["name"] = command;
    data["value"]["target"] = target;

    for(auto s : servers){
        if(s->connected){
            s->client->send(data.dump());
        }
    }
}

void GoProMaster::command_only(const std::string server, const std::string command, std::string target){
    json data = json::object();
    data["key"] = "command";
    data["value"] = json::object();
    data["value"]["name"] = command;
    data["value"]["target"] = target;

    for(auto s : servers){
        if(s->ip == server && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::command_with_value(const std::string command, std::string target, std::string value){
    json data = json::object();
    data["key"] = "command";
    data["value"] = json::object();
    data["value"]["name"] = command;
    data["value"]["target"] = target;
    data["value"]["value"] = value;

    for(auto s : servers){
        if(s->connected){
            s->client->send(data.dump());
        }
    }
}

void GoProMaster::query_only(const std::string command, std::string target){
    json data = json::object();
    data["key"] = "query";
    data["value"] = json::object();
    data["value"]["name"] = command;
    data["value"]["target"] = target;

    for(auto s : servers){
        if(s->connected){
            s->client->send(data.dump());
        }
    }
}

void GoProMaster::query_only(const std::string server, const std::string command, std::string target){
    json data = json::object();
    data["key"] = "query";
    data["value"] = json::object();
    data["value"]["name"] = command;
    data["value"]["target"] = target;

    for(auto s : servers){
        if(s->ip == server && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::webcam_only(const std::string command, std::string target){
    json data = json::object();
    data["key"] = "webcam";
    data["value"] = json::object();
    data["value"]["name"] = command;
    data["value"]["target"] = target;

    for(auto s : servers){
        if(s->connected){
            s->client->send(data.dump());
        }
    }
}

void GoProMaster::webcam_only(const std::string server, const std::string command, std::string target){
    json data = json::object();
    data["key"] = "webcam";
    data["value"] = json::object();
    data["value"]["name"] = command;
    data["value"]["target"] = target;

    for(auto s : servers){
        if(s->ip == server && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::webcam_start(const std::string server){

}

void GoProMaster::preview_start(std::string server, std::string target){
    json data = json::object();
    data["key"] = "preview";
    data["value"] = json::object();
    data["value"]["name"] = "start";
    data["value"]["target"] = target;

    for(auto s : servers){
        if(s->ip == server && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::preview_end(std::string server, std::string target){
    json data = json::object();
    data["key"] = "preview";
    data["value"] = json::object();
    data["value"]["name"] = "stop";
    data["value"]["target"] = target;

    for(auto s : servers){
        if((s->ip == server || server.size() == 0) && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::media_only(const std::string command, std::string target){

}

void GoProMaster::download_last_media(const std::string ip, const DownloadMediaParameters params){
    if(downloading_media_flag > 0) return;
    std::thread([=](){
        if(params.put_finish){
            downloading_media_flag = 2;
        }else{
            downloading_media_flag = 1;
        }
        downloading_media_total = 0;
        downloading_media_done = 0;

        for(auto& s : cameras){
            if(!s->connected) continue;
            if(ip.size() == 0 || s->ip != ip) continue;
            std::string ext = fs::path(s->last_media).extension().string();
            std::string filename = s->name;
            if(filename.size() == 0 || s->name.size() == 0) {
                std::cerr << "[download_last_media] filename size is 0, we just skip..." << std::endl;
                continue;
            }
            size_t filename_size = filename.size();
            std::cout << "[download_last_media] \ttype: " << params.type << std::endl;
            std::cout << "[download_last_media] \tfilename: " << filename.c_str() << std::endl;
            if(params.c_count > 0){
                std::string ccc = "";
                for(int32_t i = 0; i < params.c_count && i < filename_size; i++){
                    if(params.type == 1){
                        ccc += filename.at(0);
                        filename.erase(filename.begin());
                    }
                    if(params.type == 2){
                        ccc += filename.at(filename.size() - 1);
                        filename.erase(filename.begin() + filename.size() - 1);
                    }
                }
                if(params.type == 2){
                    ccc.reserve();
                }
                filename = ccc;
            }
            filename += ext;
            bool islocal = s->server == "127.0.0.1";

            json data = json::object();
            data["key"] = "media";
            data["value"] = json::object();
            data["value"]["name"] = "url";
            data["value"]["item"] = s->name;
            data["value"]["ip"] = s->ip;
            data["value"]["local"] = islocal;
            data["value"]["dir"] = params.dir;
            data["value"]["filename"] = filename;

            for(auto ss : servers){
                if(s->server == ss->ip && ss->connected){
                    ss->client->send(data.dump());
                    downloading_media_total++;
                    break;
                }
            }
        }
        if(downloading_media_total == 0){
            downloading_media_flag = 0;
        }
    }).detach();
}

void GoProMaster::download_all_media(const std::string server, const std::string ip, const std::string folder, std::vector<MediaInfo> media_list){
    if(downloading_media_flag > 0) return;
    std::thread([=](){
        downloading_media_flag = 1;
        downloading_media_total = 0;
        downloading_media_done = 0;

        int32_t index = findCamera(server, ip);
        if(index >= 0){
            const CameraInfo s = getCamera_Clone(index);
            std::string ext = fs::path(s.last_media).extension().string();
            bool islocal = s.server == "127.0.0.1";

            json data = json::object();
            data["key"] = "media";
            data["value"] = json::object();
            data["value"]["name"] = "d_all";
            data["value"]["item"] = s.name;
            data["value"]["ip"] = s.ip;
            data["value"]["local"] = islocal;
            data["value"]["dir"] = folder;
            data["value"]["filenames"] = json::array();

            for(auto& m : media_list){
                data["value"]["filenames"].push_back(m.filename);
            }
            
            for(auto ss : servers){
                if(s.server == ss->ip && ss->connected){
                    ss->client->send(data.dump());
                    downloading_media_total++;
                    break;
                }
            }
        }
        if(downloading_media_total == 0){
            downloading_media_flag = 0;
        }
    }).detach();
}

void GoProMaster::download_single_media(const std::string server, const std::string ip, const std::string filepath, MediaInfo media){
    if(downloading_media_flag > 0) return;
    std::thread([=](){
        downloading_media_flag = 1;
        downloading_media_total = 0;
        downloading_media_done = 0;

        int32_t index = findCamera(server, ip);
        if(index >= 0){
            const CameraInfo s = getCamera_Clone(index);
            std::string ext = fs::path(s.last_media).extension().string();
            bool islocal = s.server == "127.0.0.1";

            fs::path p(filepath);
            json data = json::object();
            data["key"] = "media";
            data["value"] = json::object();
            data["value"]["name"] = "d_single";
            data["value"]["item"] = s.name;
            data["value"]["ip"] = s.ip;
            data["value"]["local"] = islocal;
            data["value"]["dir"] = p.parent_path().string();
            data["value"]["filename"] = p.filename().string();

            for(auto ss : servers){
                if(s.server == ss->ip && ss->connected){
                    ss->client->send(data.dump());
                    downloading_media_total++;
                    break;
                }
            }
        }
        if(downloading_media_total == 0){
            downloading_media_flag = 0;
        }
    }).detach();
}

void GoProMaster::get_media_info(const std::string server, const std::string ip, const std::string path){
    json data = json::object();
    data["key"] = "media";
    data["value"] = json::object();
    data["value"]["name"] = "info";
    data["value"]["path"] = path;
    data["value"]["target"] = ip;

    for(auto s : servers){
        if(s->ip != server) continue;
        bool islocal = s->ip == "127.0.0.1";
        data["value"]["local"] = islocal;
        if((s->ip == server || server.size() == 0) && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::get_media_list(const std::string server, const std::string ip){
    json data = json::object();
    data["key"] = "media";
    data["value"] = json::object();
    data["value"]["name"] = "list";
    data["value"]["target"] = ip;

    for(auto s : servers){
        if(s->ip != server) continue;
        bool islocal = s->ip == "127.0.0.1";
        data["value"]["local"] = islocal;
        if((s->ip == server || server.size() == 0) && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::presetSwitch(const std::string server, const std::string target, int32_t mode) {
    std::thread([=](){
        for (auto& s : servers) {
            if (!s->connected) continue;
            if (server.size() > 0 && server != s->ip) continue;
            json get_status = json::object();
            get_status["key"] = "preset";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "load";
            get_status["value"]["mode"] = mode;
            get_status["value"]["target"] = target;
            s->client->send(get_status.dump());
        }
    }).detach();
}

void GoProMaster::locate(const std::string server, const std::string target){
    int32_t index = haslocate(server, target);
    if(index == -1){
        locates.push_back(std::pair<std::string, std::string>(server, target));
    }else{
        locates.erase(locates.begin() + index);
    }
}

int32_t GoProMaster::haslocate(const std::string server, const std::string target){
    for(int32_t i = 0; i < locates.size(); i++){
        auto& s = locates.at(i);
        if(s.first == server && s.second == target) return i;
    }
    return -1;
}

void GoProMaster::apply(const std::string& ip, const std::string& target, const int32_t id, const int32_t value){
    std::thread([=](){    
        for (auto& s : servers) {
            if (!s->connected) continue;
            json get_status = json::object();
            get_status["key"] = "query";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "set";
            get_status["value"]["source"] = ip;
            get_status["value"]["target"] = target;
            get_status["value"]["id"] = id;
            get_status["value"]["value"] =  std::to_string(value);
            s->client->send(get_status.dump());
        }
    }).detach();
}

void GoProMaster::applyAll(const std::string& ip, const json& res){
    std::thread([=](){    
        for (auto& s : servers) {
            if (!s->connected) continue;
            json get_status = json::object();
            get_status["key"] = "query";
            get_status["value"] = json::object();
            get_status["value"]["source"] = ip;
            get_status["value"]["name"] = "setall";
            get_status["value"]["value"] = res;
            s->client->send(get_status.dump());
        }
    }).detach();
}

void GoProMaster::quickApplyAll(const CameraInfo& target){
    int32_t model = InspectorWindow::_get_current_model(target.hw);
    json root = json::object();
    json _set = json::object();
    json _status = json::object();
    if(getSettingsFromCamera(target, _set) && getStatusFromCamera(target, _status)){
        // Execute the apply logic here
        int32_t p = _status[std::to_string(PRESET_ID)].get<int32_t>();
        root["model"] = model; // Added a model field for mark it's supported
        root["preset"] = p;
        root["setting"] = _set;
        std::cout << "trying apply all, preset: " << p << std::endl;
        applyAll(target.ip, root);
    }
}

void GoProMaster::stopApplyAll(const CameraInfo& target){
    std::thread([=](){    
        for (auto& s : servers) {
            if (!s->connected) continue;
            json get_status = json::object();
            get_status["key"] = "query";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "setall_cancel";
            s->client->send(get_status.dump());
        }
    }).detach();
}

bool GoProMaster::directoryExists(const std::string& path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        return true;
    }
    return false;
}

void GoProMaster::registerCameraMediaListFeedback(camera_media_list_feedback v){
    _camera_media_list_feedback = v;
}

void GoProMaster::registerCameraSettingFeedback(camera_setting_feedback v){
    _camera_setting_feedback = v;
}

void GoProMaster::registerCameraStatusFeedback(camera_status_feedback v){
    _camera_status_feedback = v;
}

void GoProMaster::registerCameraHWFeedback(camera_hw_feedback v){
    _camera_hw_feedback = v;
}

void GoProMaster::registerCameraLogFeedback(camera_log_feedback v){
    _camera_log_feedback = v;
}

void GoProMaster::registerApplyAllFeedback(camera_apply_all_feedback v){
    _camera_apply_all_feedback = v;
}

void GoProMaster::registerSavePreset(camera_preset_save v){
    _camera_preset_save = v;
}

void GoProMaster::set_preset_data(std::shared_ptr<json> _preset){
    preset_ptr = _preset;
}

int32_t GoProMaster::add_preset(const std::string name, json data){
    if(!(*preset_ptr)["data"].is_array()) {
        (*preset_ptr)["data"] = json::array();
    }else{
        for(int32_t i = 0; i < (*preset_ptr)["data"].size(); i++){
            json item = (*preset_ptr)["data"].at(i);
            if(item["name"].is_string()){
                if(item["name"].get<std::string>() == name){
                    // Name repeat
                    return 2;
                }
            }
        }
    }
    (*preset_ptr)["data"].push_back(data);
    return 0;
}

bool GoProMaster::get_preset(const std::string name, json& data){
    if(!(*preset_ptr)["data"].is_array()) {
        (*preset_ptr)["data"] = json::array();
        return false;
    }
    for(int32_t i = 0; i < (*preset_ptr)["data"].size(); i++){
        json item = (*preset_ptr)["data"].at(i);
        if(item["name"].is_string()){
            if(item["name"].get<std::string>() == name){
                data = item;
                return true;
            }
        }
    }
    return false;
}

bool GoProMaster::remove_preset(const std::string name){
    if(!(*preset_ptr)["data"].is_array()) {
        (*preset_ptr)["data"] = json::array();
        return false;
    }else{
        for(int32_t i = 0; i < (*preset_ptr)["data"].size(); i++){
            json item = (*preset_ptr)["data"].at(i);
            if(item["name"].is_string()){
                if(item["name"].get<std::string>() == name){
                    (*preset_ptr)["data"].erase((*preset_ptr)["data"].begin() + i);
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<std::string> GoProMaster::get_preset_names(){
    if(!(*preset_ptr)["data"].is_array()) {
        (*preset_ptr)["data"] = json::array();
        return std::vector<std::string>();
    }
    std::vector<std::string> a = std::vector<std::string>();
    for(int32_t i = 0; i < (*preset_ptr)["data"].size(); i++){
        json item = (*preset_ptr)["data"].at(i);
        if(item["name"].is_string()){
            a.push_back(item["name"].get<std::string>());
        }
    }
    return a;
}

const std::vector<std::shared_ptr<CameraInfo>>& GoProMaster::getCameras() const {
    return cameras;
}

const std::vector<CameraInfo> GoProMaster::getCameras_Clone() {
    std::vector<CameraInfo> buffer = std::vector<CameraInfo>();
    {
        std::lock_guard<std::mutex> lock(camera_mtx);
        for(auto& i : getCameras()){
            CameraInfo sc = CameraInfo();
            sc.hw = json::parse(i->hw.dump());
            sc.state = json::parse(i->state.dump());
            sc.ip = i->ip;
            sc.last_media = i->last_media;
            sc.name = i->name;
            sc.serial = i->serial;
            sc.connected = i->connected;
            sc.server = i->server;
            buffer.push_back(sc);
        }
    }
    return buffer;
}

const CameraInfo GoProMaster::getCamera_Clone(int32_t index) {
    if(index < 0 || index >= cameras.size()) return CameraInfo();
    CameraInfo sc = CameraInfo();
    auto i = getCameras().at(index).get();
    sc.hw = i->hw;
    sc.ip = i->ip;
    sc.last_media = i->last_media;
    sc.name = i->name;
    sc.serial = i->serial;
    sc.connected = i->connected;
    sc.state = i->state;
    sc.server = i->server;
    return sc;
}

const std::vector<std::shared_ptr<ServerConnection>>& GoProMaster::getServers() const {
    return servers;
}

const std::vector<ServerConnection> GoProMaster::getServers_Clone() {
    std::vector<ServerConnection> buffer = std::vector<ServerConnection>();
    {
        std::lock_guard<std::mutex> lock(server_mtx);
        for(auto& i : getServers()){
            ServerConnection sc = ServerConnection();
            sc.ip = i->ip;
            sc.connected = i->connected;
            sc.last_message = i->last_message;
            sc.client = i->client;
            buffer.push_back(sc);
        }
    }
    return buffer;
}

const ServerConnection GoProMaster::getServer_Clone(int32_t index) {
    if(index < 0 || index >= servers.size()) return ServerConnection();
    ServerConnection sc = ServerConnection();
    auto i = getServers().at(index).get();
    sc.ip = i->ip;
    sc.connected = i->connected;
    sc.last_message = i->last_message;
    sc.client = i->client;
    return sc;
}

void GoProMaster::update(){
    while (!done) {
        for (auto& s : servers) {
            if (!s->connected) continue;
            if (ipQueryFinish.count(s->ip) && ipQueryFinish.at(s->ip)) continue;
            json get_status = json::object();
            get_status["key"] = "command";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "ip";
            ipQueryFinish.insert_or_assign(s->ip, true);
            s->client->send(get_status.dump());
        }

        for (auto& s : servers) {
            if (!s->connected) continue;
            if (stateQueryFinish.count(s->ip) && stateQueryFinish.at(s->ip)) continue;
            json get_status = json::object();
            get_status["key"] = "query";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "getall";
            stateQueryFinish.insert_or_assign(s->ip, true);
            s->client->send(get_status.dump());
        }

        for (auto& s : servers) {
            if (!s->connected) continue;
            if (mediaQueryFinish.count(s->ip) && mediaQueryFinish.at(s->ip)) continue;
            json get_status = json::object();
            get_status["key"] = "media";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "lastmedia";
            mediaQueryFinish.insert_or_assign(s->ip, true);
            s->client->send(get_status.dump());
        }

        std::lock_guard<std::mutex> lock(locate_mtx);
        for (auto& s : locates) {
            int32_t index = findCamera(s.first, s.second);
            if(index == -1) continue;
            auto& c = getCameras().at(index);
            json status;
            if(getStatusFromCamera(*c, status)){
                if(status[std::to_string(PRESET_ID)].is_number()){
                    presetSwitch(s.first, s.second, status[std::to_string(PRESET_ID)].get<int32_t>());
                }
            }
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void GoProMaster::processMessage(const std::string& server, const std::string& msg){
    try{
        json data = json::parse(msg);
        if(!data["key"].is_string()){
            std::cerr << "Invalid message from " << server << ": " << msg << std::endl;
            std::cerr << "Key is not string" << std::endl;
            return;
        }
        if(data["value"].is_null()){
            std::cerr << "Invalid message from " << server << ": " << msg << std::endl;
            std::cerr << "Value is null" << std::endl;
            return;
        }
        std::string key = data["key"].get<std::string>();
        if(key == "command:ip"){
            if(!data["value"]["data"].is_array()){
                std::cerr << "Invalid message from " << server << ": " << msg << std::endl;
                std::cerr << "command:ip, return value should be array" << std::endl;
                return;
            }
            std::vector<std::string> ips = std::vector<std::string>();
            std::vector<std::string> serial = std::vector<std::string>();
            std::unordered_map<std::string, std::string> names = std::unordered_map<std::string, std::string>();
            for(auto ip = data["value"]["data"].begin(); ip != data["value"]["data"].end(); ++ip){
                if(!ip.value().is_string()){
                    continue;
                }
                std::string ip_ref = ip.value().get<std::string>();
                
                std::vector<std::string> words = std::vector<std::string>();
                std::stringstream ss(ip_ref);
                std::string word;
                while (ss >> word) { // Extracts words separated by any whitespace
                    words.push_back(word);
                }

                if(words.size() > 0){
                    std::string serial_buffer = "";
                    serial_buffer += words[0][5];
                    serial_buffer += words[0][8];
                    serial_buffer += words[0][9];
                    serial.push_back(serial_buffer);
                    ips.push_back(words[0]);
                }
                if(words.size() > 1){
                    names.insert_or_assign(words[0], words[1]);
                }
            }
            std::lock_guard<std::mutex> lock(camera_mtx);
            replaceCameraFromServer(server, ips);

            for(int32_t i = 0; i < ips.size(); i++){
                int32_t index = findCamera(server, ips[i]);
                if(index != -1){
                    cameras[index]->serial = serial[i];
                    if(names.count(ips[i])){
                        cameras[index]->name = names.at(ips[i]);
                    }
                }
            }

            ipQueryFinish.insert_or_assign(server, false);
        }
        else if(key == "query:get" || key == "query:getall"){
            if(key == "query:getall"){
                stateQueryFinish.insert_or_assign(server, false);
            }
            if(!data["value"]["data"].is_array()){
                std::cerr << "Invalid message from " << server << ": " << msg << std::endl;
                std::cerr << "query:get, return value should be array" << std::endl;
                return;
            }
            if(key == "query:get" && data["value"]["data"].size() == 0){
                std::cout << "Camera response null state from server: " << server << std::endl;
                return;
            }
            /**
             * In case you're confuse here...
             * The data is like this
             * * data
             * * key
             * * value
             *   * data
             *     * ip <- Go pro ip address
             *     * status <- Where all the go pro status keeps
             */
            std::lock_guard<std::mutex> lock(camera_mtx);
            int32_t count = 0;

            // Clear the message
            if(key == "query:getall"){
                for(auto& camera : cameras){
                    if(camera->server == server){
                        camera->connected = false;
                    }
                }
            }

            for(auto ip = data["value"]["data"].begin(); ip != data["value"]["data"].end(); ++ip){
                if(!ip.value()["ip"].is_string() || !ip.value()["status"].is_object()){
                    std::cerr << "query:get error: Require ip and status in value.data" << std::endl;
                    continue;
                }
                std::string ip_ref = ip.value()["ip"].get<std::string>();
                if(ip_ref.size() == 0){
                    continue;
                }
                int32_t found = findCamera(server, ip_ref);
                CameraInfo _cam;
                if(found == -1){
                    auto cam = std::make_shared<CameraInfo>();
                    cam->state = ip.value()["status"];
                    cam->hw = ip.value()["hw"];
                    cam->connected = true;
                    _cam = *cam;
                    cameras.push_back(cam);
                    std::cout << "Added camera state " << ip_ref << std::endl;
                    {
                        ImGuiToast toast(ImGuiToastType_Success, 3000);
                        toast.set_title("Camera Connected");
                        toast.set_content("Camera ip: %s", ip_ref.c_str());
                        ImGui::InsertNotification(toast);
                    }
                }else{
                    auto cam = cameras[found];
                    cam->state = ip.value()["status"];
                    cam->hw = ip.value()["hw"];
                    cam->connected = cam->state["settings"]["2"].is_number_integer();
                    _cam = *cam;
                }

                if(_camera_setting_feedback != NULL){
                    json buffer_setting = json::object();
                    if(getSettingsFromCamera(_cam, buffer_setting)){
                        _camera_setting_feedback(_cam.ip, buffer_setting);
                    }
                }else{
                    std::cout << "Skip setting feedback: Detect function pointer is NULL" << std::endl;
                }
                if(_camera_status_feedback != NULL){
                    json buffer_status = json::object();
                    if(getStatusFromCamera(_cam, buffer_status)){
                        _camera_status_feedback(_cam.ip, buffer_status);
                    }
                }else{
                    std::cout << "Skip status feedback: Detect function pointer is NULL" << std::endl;
                }
                if(_camera_hw_feedback != NULL){
                    _camera_hw_feedback(_cam.ip, _cam.hw);
                }else{
                    std::cout << "Skip hw feedback: Detect function pointer is NULL" << std::endl;
                }
                count++;
            }
        }
        else if(key == "query:set"){
            
        }
        else if(key == "query:setall"){
            if(_camera_apply_all_feedback != NULL) _camera_apply_all_feedback();
        }
        else if(key == "media:lastmedia"){
            if(!data["value"]["data"].is_array()){
                std::cerr << "Invalid message from " << server << ": " << msg << std::endl;
                std::cerr << "media:lastmedia, return value should be array" << std::endl;
                mediaQueryFinish.insert_or_assign(server, false);
                return;
            }

            for(auto ip = data["value"]["data"].begin(); ip != data["value"]["data"].end(); ++ip){
                if(!ip.value()["ip"].is_string() || !ip.value()["filename"].is_object()){
                    std::cerr << "media:lastmedia error: Require ip and filename in value.data" << std::endl;
                    std::cerr << data.dump() << std::endl;
                    continue;
                }
                std::string folder = "";
                std::string file = "";
                if(ip.value()["filename"]["folder"].is_string()){
                    folder = ip.value()["filename"]["folder"].get<std::string>();
                }
                if(ip.value()["filename"]["file"].is_string()){
                    file = ip.value()["filename"]["file"].get<std::string>();
                }
                
                std::string ip_ref = ip.value()["ip"].get<std::string>();
                std::lock_guard<std::mutex> lock(camera_mtx);
                int32_t found = findCamera(server, ip_ref);
                if(found != -1){
                    cameras[found]->last_media = folder + "/" + file;
                }else{
                    std::cerr << "Could find ip from server client list: " << ip_ref.c_str() << std::endl;
                }
            }
            mediaQueryFinish.insert_or_assign(server, false);
        }
        else if(key == "media:url"){
            std::string urls;

            std::string path = "";
            std::string dir = "";
            std::string item = "";
            std::string filename = "";
            bool islocal = false;
            if(data["value"]["path"].is_string()){
                path = data["value"]["path"].get<std::string>();
            }
            if(data["value"]["item"].is_string()){
                item = data["value"]["item"].get<std::string>();
            }
            if(data["value"]["dir"].is_string()){
                dir = data["value"]["dir"].get<std::string>();
            }
            if(data["value"]["filename"].is_string()){
                filename = data["value"]["filename"].get<std::string>();
            }
            if(data["value"]["local"].is_boolean()){
                islocal = data["value"]["local"].get<bool>();
            }

            std::string path_target = dir + "/" + filename;
            if(islocal){
                urls = path;
            }else{
                urls = "http://" + server + ":8080/res/" + path;
            }

            std::cout << "media download: " << urls.c_str() << "  " << path_target.c_str() << std::endl;
            if(urls.size() >= 1){
                size_t size = requests::downloadFile(urls.c_str(), path_target.c_str(), [&urls, &path_target](size_t received_bytes, size_t total_bytes){
                    std::cout << "[last_media] download " << urls << " => " << path_target << " " << received_bytes << " / " << total_bytes << std::endl;
                });
                downloading_media_done++;
                if(downloading_media_done == downloading_media_total){
                    if(downloading_media_flag == 2){
                        std::string finish_file = dir + "/" + "finish.txt";
                        FILE* f = fopen(finish_file.c_str(), "wb");
                        fclose(f);
                    }
                    downloading_media_total = 0;
                    downloading_media_done = 0;
                    downloading_media_flag = 0;
                }
            }
        }
        else if(key == "media:info"){
            
        }
        else if(key == "media:list"){
            std::vector<MediaInfo> media_list = std::vector<MediaInfo>();
            if(!data["value"]["data"].is_array()){
                std::cerr << "Invalid message from " << server << ": " << msg << std::endl;
                std::cerr << "media:list, return value should be array" << std::endl;
                return;
            }

            for(auto ip = data["value"]["data"].begin(); ip != data["value"]["data"].end(); ++ip){
                std::string source = "";
                if(ip.value()["ip"].is_string()){
                    source = ip.value()["ip"].get<std::string>();
                } else continue;
                if(ip.value()["status"].is_object()){
                    if(ip.value()["status"]["media"].is_array()){
                        auto mediaarr = ip.value()["status"]["media"];
                        for(auto ip2 = mediaarr.begin(); ip2 != mediaarr.end(); ++ip2){
                            std::string d = "";
                            if(ip2.value()["d"].is_string()){
                                d = ip2.value()["d"].get<std::string>();
                            } else continue;
                            if(ip2.value()["fs"].is_array()){
                                auto fsarr = ip2.value()["fs"];
                                for(auto ip3 = fsarr.begin(); ip3 != fsarr.end(); ++ip3){
                                    MediaInfo info = MediaInfo();
                                    if(ip3.value()["n"].is_string()){
                                        info.filename = d;
                                        info.filename += "/";
                                        info.filename += ip3.value()["n"].get<std::string>();
                                    } else continue;
                                    if(ip3.value()["s"].is_number()){
                                        info.size = ip3.value()["s"].get<int64_t>();
                                    }
                                    if(ip3.value()["cre"].is_number()){
                                        info.created = ip3.value()["cre"].get<int64_t>();
                                    }
                                    if(ip3.value()["mod"].is_number()){
                                        info.modified = ip3.value()["mod"].get<int64_t>();
                                    }
                                    media_list.push_back(info);
                                }
                            }
                        }
                    }
                }
            }

            if(_camera_media_list_feedback != NULL)
                _camera_media_list_feedback(media_list);
        }
        else if(key == "media:thumbnail"){
            if(!data["value"]["data"].is_string()){
                std::cerr << "Invalid message from " << server << ": " << msg << std::endl;
                std::cerr << "media:thumbnail, return value should be string" << std::endl;
                return;
            }

            std::vector<u_char> raw_data = decodeBase64(data["value"]["data"].get<std::string>());
        }
        else if(key == "media:d_single"){

        }
        else if(key == "media:d_all"){
            
        }
        else{
            std::cerr << "Invalid message from " << server << ": " << msg << std::endl;
            std::cerr << "No registerd action from this key: " << key << std::endl;
        }
    }catch(const std::exception& e){
        std::cerr << "JSON Parse error: " << e.what() << std::endl;
    }
}

void GoProMaster::sendToAll(const std::string& msg) {
    for (auto& s : servers) {
        if (s->connected) {
            s->client->send(msg);
        }
    }
}

void GoProMaster::cleanCameraFromServer(const std::string server){
    std::vector<std::shared_ptr<CameraInfo>>::iterator iter = std::find_if(cameras.begin(), cameras.end(),
        [&](auto &s){ return ((*s).server == server); }
    );

    while(iter != cameras.end()){
        cameras.erase(iter);
        iter = std::find_if(cameras.begin(), cameras.end(),
            [&](auto &s){ return ((*s).server == server); }
        );
    }
}

void GoProMaster::replaceCameraFromServer(const std::string server, const std::vector<std::string> ips){
    // Remove part
    auto it = std::remove_if(cameras.begin(), cameras.end(), [&](const std::shared_ptr<CameraInfo>& c) {
        // Only consider cameras belonging to this specific server
        if (c && c->server == server) {
            // If the camera's IP is NOT found in the new 'ips' list, delete it
            return std::find(ips.begin(), ips.end(), c->ip) == ips.end();
        }
        return false;
    });
    
    cameras.erase(it, cameras.end());

    // Append part
    for (const auto& new_ip : ips) {
        bool exists = false;
        for (const auto& existing_cam : cameras) {
            if (existing_cam && existing_cam->ip == new_ip && existing_cam->server == server) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            auto new_cam = std::make_shared<CameraInfo>();
            new_cam->server = server;
            new_cam->ip = new_ip;
            cameras.push_back(new_cam);
            {
                ImGuiToast toast(ImGuiToastType_Success, 3000);
                toast.set_title("New IP Detected");
                toast.set_content("Detected ip: %s, from server: %s", new_ip.c_str(), server.c_str());
                ImGui::InsertNotification(toast);
            }
        }
    }
}

void GoProMaster::setdone(){
    done = true;
}

bool GoProMaster::getSettingsFromCamera(CameraInfo target, json& res){
    json data = target.state;
    if(!data["settings"].is_object()){
        return false;
    }
    res = data["settings"];
    // Convert value id to index number
    for(int32_t i = 0; i < GOPRO_SETTING_SIZE; i++){
        int32_t id = GOPRO_SETTING_IDS[i];
        if(!res[std::to_string(id)].is_number()) continue;
        int32_t value = res[std::to_string(id)].get<int32_t>();

        const size_t size = GET_SETTING_SIZE_BY_ID(id);
        const int32_t* all_values = GET_SETTING_VALUE_BY_ID(id);
        for(int32_t j = 0; j < size; j++){
            if(all_values[j] == value){
                res[std::to_string(id)] = j; // Set index, instead of value id
                break;
            }
        }
    }
    return true;
}

bool GoProMaster::getStatusFromCamera(CameraInfo target, json& res){
    json data = target.state;
    if(!data["status"].is_object()){
        return false;
    }
    res = data["status"];
    // Convert value id to index number
    for(int32_t i = 0; i < GOPRO_STATUS_SIZE; i++){
        int32_t id = GOPRO_STATUS_IDS[i];
        const int32_t type = GET_STATUS_TYPE_BY_ID(id);
        if(type != (int32_t)CAMERA_STATUS_TYPE::OPTION){
            continue; // Only option type need to convert
        }
        if(!res[std::to_string(id)].is_number()) continue;
        int32_t value = res[std::to_string(id)].get<int32_t>();

        const size_t size = GET_STATUS_SIZE_BY_ID(id);
        const int32_t* all_values = GET_STATUS_VALUE_BY_ID(id);
        for(int32_t j = 0; j < size; j++){
            if(all_values[j] == value){
                res[std::to_string(id)] = j; // Set index, instead of value id
                break;
            }
        }
    }
    return true;
}

std::string GoProMaster::getBarInfo(const std::shared_ptr<CameraInfo> &c){
    return getBarInfo(*c);
}

std::string GoProMaster::getBarInfo(const CameraInfo &c){
    json obj = c.state;
    bool find = false;
    std::string result = c.name + "  " + c.serial + "  " + c.ip + "  ";
    if(obj["settings"].is_object()){
        if(obj["settings"]["2"].is_number()){
            int32_t vr = obj["settings"]["2"].get<int32_t>();
            for(int32_t i = 0; i < VIDEO_RESOLUTION_SIZE; i++){
                if(vr == VIDEO_RESOLUTION_VALUE[i]){
                    vr = i;
                }
            }
            result += VIDEO_RESOLUTION_STRING[vr];
            result += "  ";
            find = true;
        }
        if(obj["settings"]["3"].is_number()){
            int32_t vr = obj["settings"]["3"].get<int32_t>();
            for(int32_t i = 0; i < FRAMES_PER_SECOND_SIZE; i++){
                if(vr == FRAMES_PER_SECOND_VALUE[i]){
                    vr = i;
                }
            }
            result += FRAMES_PER_SECOND_STRING[vr];
            result += "  ";
            find = true;
        }
    }
    if(!find) return c.ip + "  ...";
    return result;
}

size_t GoProMaster::getServerCount(){
    return servers.size();
}

int32_t GoProMaster::findServer(const std::string ip){
    int32_t index = 0;
    for(const auto& c : servers){
        if(c->ip == ip){
            return index;
        }
        ++index;
    }
    return -1;
}

int32_t GoProMaster::findCamera(const std::string server, const std::string ip){
    int32_t index = 0;
    //std::lock_guard<std::mutex> lock(camera_mtx);
    for(const auto& c : cameras){
        if(c->server == server && c->ip == ip){
            return index;
        }
        ++index;
    }
    return -1;
}

std::vector<u_char> GoProMaster::decodeBase64(const std::string& input) {
    static const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::vector<int32_t> T(256, -1);
    for (int32_t i = 0; i < 64; i++) T[base64_chars[i]] = i;

    std::vector<u_char> out;
    int32_t val = 0, valb = -8;
    for (u_char c : input) {
        if (T[c] == -1) continue; // Skip non-base64 characters
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(static_cast<u_char>((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}
