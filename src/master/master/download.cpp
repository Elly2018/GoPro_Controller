/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"

static void gopro_master_download_x_media(AppData& data, const std::string tag, const std::string server, const std::string ip, const std::string filepath, const std::vector<Media_info> media_list) {
    data.master.downloading_media_total = 0;
    data.master.downloading_media_done = 0;

    int32_t index = gopro_master_find_camera(data, server, ip);
    if (index == -1) {
        downloading_media_flag = 0;
        return;
    }
    const Camera_info c = Camera_info(data.master.cameras.at(index));
    std::string ext = fs::path(c.last_media).extension().string();
    bool islocal = c.server == "127.0.0.1";

    fs::path p(filepath);
    json data = json::object();
    data["key"] = "media";
    data["value"] = json::object();
    data["value"]["name"] = tag;
    data["value"]["item"] = c.name;
    data["value"]["ip"] = c.ip;
    data["value"]["local"] = islocal;
    data["value"]["dir"] = p.parent_path().string();
    data["value"]["filenames"] = json::array();

    for(const Media_info& m : media_list){
        data["value"]["filenames"].push_back(m.filename);
    }

    for(Server_connection& s : data.master.servers){
        if(!s.vaild) continue;
        if(c.server == s.ip && s.connected){
            s.client.send(data.dump());
            downloading_media_total++;
            break;
        }
    }
    
    data.master.downloading_media_flag = 0;
}

void gopro_master_media_only(AppData& data, const std::string command, std::string target = "") {

}

void gopro_master_download_last_media(AppData& data, const std::string ip, const Download_media_parameters params) {
    if(data.master.downloading_media_flag > 0) return;

    if(params.put_finish){
        data.master.downloading_media_flag = 2;
    }else{
        data.master.downloading_media_flag = 1;
    }

    data.master.downloading_thread = std::thread([&]() {
        data.master.downloading_media_total = 0;
        data.master.downloading_media_done = 0;

        for(Camera_info& c : data.master.cameras) {
            if(!c.vaild) continue;
            if(!c.connected) continue;
            if(!c.ip == 0 || c.ip != ip) continue;
            std::string ext = fs::path(c.last_media).extension().string();
            std::string filename = c.name;
            if(filename.size() == 0 || std::string(c.name).size() == 0) {
                std::cerr << "[download_last_media] filename size is 0, we just skip...\n";
                continue;
            }
            size_t filename_size = filename.size();
            std::cout << "[download_last_media] \ttype: " << params.type << "\n";
            std::cout << "[download_last_media] \tfilename: " << filename.c_str() << "\n";
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
            bool islocal = c.server == "127.0.0.1";

            json data = json::object();
            data["key"] = "media";
            data["value"] = json::object();
            data["value"]["name"] = "url";
            data["value"]["item"] = c.name;
            data["value"]["ip"] = c.ip;
            data["value"]["local"] = islocal;
            data["value"]["dir"] = params.dir;
            data["value"]["filename"] = filename;

            for(Server_connection& s : data.master.servers){
                if(!s.vaild) continue;
                if(c.server == s.ip && s.connected){
                    s.client.send(data.dump());
                    data.master.downloading_media_total++;
                    break;
                }
            }
        }
        
        data.master.downloading_media_flag = 0;

    });
}

void gopro_master_download_all_media(AppData& data, const std::string server, const std::string ip, const std::string filepath, const std::vector<Media_info> media_list) {
    if(data.master.downloading_media_flag > 0) return;

    data.master.downloading_media_flag = 1;

    data.master.downloading_thread = std::thread([=](){
        gopro_master_download_x_media(data, "d_single", server, ip, filepath, media_list);
    });
}

void gopro_master_download_single_media(AppData& data, const std::string server, const std::string ip, const std::string filepath, const Media_info media) {
    if(data.master.downloading_media_flag > 0) return;

    data.master.downloading_media_flag = 1;

    data.master.downloading_thread = std::thread([=](){
        std::vector<Media_info> media_list;
        media_list.push_back(media);
        gopro_master_download_x_media(data, "d_single", server, ip, filepath, media_list);
    });
}