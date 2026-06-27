/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"

void gopro_master_process_message(AppData& data, const std::string& ip, const std::string& msg) {
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

void gopro_master_send_2_all(AppData& data, const std::string& msg) {
    for (const Server_connection& s : data.master.servers) {
        if (!s.vaild) continue;
        if (s.connected) {
            s.client.send(msg);
        }
    }
}
