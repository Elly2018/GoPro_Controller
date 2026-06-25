/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller.h"
#include "../gopro_controller_local.h"
#include <vector>
#include <string>
#include <thread>
#include <future>
#include "../../common/config.h"

json gopro_controller_get_media_list(gopro_controller& controller, const std::string target) {
    json arr = json::array();
    if(target.size() > 0){
        SingleResponse result = gopro_controller_local_get_media_list(controller, target);
        json buff;
        buff["ip"] = result.first;
        buff["status"] = result.second;
        arr.push_back(buff);
    }else{
        std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
        std::vector<SingleResponse> results = gopro_controller_local_get_media_list(controller, buffer);

        for(int32_t i = 0; i < results.size(); i++){
            json buff = json::object();
            buff["ip"] = results[i].first;
            buff["status"] = results[i].second;
            arr.push_back(buff);
        }
    }
    return arr;
}

json gopro_controller_get_last_media(gopro_controller& controller, const std::string target) {
    json arr = json::array();
    if(target.size() > 0){
        SingleResponse result = gopro_controller_local_get_last_media(controller, target);
        json buff;
        buff["ip"] = result.first;
        buff["filename"] = result.second;
        arr.push_back(buff);
    }else{
        std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
        std::vector<SingleResponse> results = gopro_controller_local_get_last_media(controller, buffer);

        for(int32_t i = 0; i < results.size(); i++){
            json buff = json::object();
            buff["ip"] = results[i].first;
            buff["filename"] = results[i].second;
            arr.push_back(buff);
        }
    }
    return arr.dump();
}

std::string gopro_controller_get_fetch_URL(gopro_controller& controller, const std::string target_ip, const bool is_local) {
    std::cout << "Http GET /last_media " << target_ip << ", " << is_local << std::endl;

    if (target_ip.empty()) {
        std::cerr << "[last_media] " << target_ip << " Missing ip parameter" << std::endl;
        return "";
    }

    std::string res = exec("http://" + target_ip + ":8080/gopro/media/last_captured");

    if(res.size() == 0) {
        std::cerr << "[last_media] " << target_ip << " IP fetch failed" << std::endl;
        return "";
    }

    json last_data = json::object();
    if(!json::accept(res)){
        std::cerr << "[last_media] " << target_ip << " IP fetch result cannot parse to json" << std::endl;
        return "";
    }
    last_data = json::parse(res);
    
    if(!last_data["file"].is_string() || !last_data["folder"].is_string()){
        std::cerr << "[last_media] " << target_ip << " no last media file" << std::endl;
        return "";
    }
    const std::string folder = last_data["folder"].get<std::string>();
    const std::string file = last_data["file"].get<std::string>();
    std::cout << "[last_media] get last_media " << target_ip << "/" << folder << "/" << file << std::endl;

    const std::string gopro_url = "http://" + target_ip + ":8080/videos/DCIM/" + folder + "/" + file + "?download=true";

    if(is_local){
        std::cout << "[last_media] return value: " << target_ip << " => " << gopro_url << std::endl;
        return gopro_url;
    }

    int32_t t = 0;
    std::string download_path = "temp.download";
    while(fs::exists("res/" + download_path)){
        download_path = "temp.download" + std::to_string(t);
        t++;
    }
    std::cout << "[last_media] try download " << gopro_url.c_str() << std::endl;
    if (SERVER_MEDIA_DOWNLOAD_LOG){
        auto start = std::chrono::high_resolution_clock::now();
    }
    size_t size = requests::downloadFile(gopro_url.c_str(), ("res/" + download_path).c_str(), [&target_ip, &start](size_t received_bytes, size_t total_bytes){
        if (SERVER_MEDIA_DOWNLOAD_LOG){
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            if(elapsed.count() >= SERVER_MEDIA_DOWNLOAD_PERIOD){
                start = end;
                std::cout << "[last_media] download " << target_ip << " " << received_bytes << " / " << total_bytes << std::endl;
            }
        }
    });
    std::cout << "[last_media] return value: " << target_ip << " => " << download_path << std::endl;
    return download_path;
}

json gopro_controller_get_filename_fetch_URL(gopro_controller& controller, const std::string target_ip, const std::string filename, bool is_local) {
    std::cout << "Http GET /single_media " << target_ip << ", " << is_local << std::endl;

    if (target_ip.empty()) {
        std::cerr << "[single_media] " << target_ip << " Missing ip parameter" << std::endl;
        return "";
    }

    std::string gopro_url = "http://" + target_ip + ":8080/videos/DCIM/" + filename + "?download=true";
    if(is_local){
        std::cout << "[last_media] return value: " << target_ip << " => " << gopro_url << std::endl;
        return gopro_url;
    }else{
        int32_t t = 0;
        std::string download_path = "temp.download";
        while(fs::exists("res/" + download_path)){
            download_path = "temp.download" + std::to_string(t);
            t++;
        }
        std::cout << "[last_media] try download " << gopro_url.c_str() << std::endl;
        if(SERVER_MEDIA_DOWNLOAD_LOG){
            auto start = std::chrono::high_resolution_clock::now();
        }
        size_t size = requests::downloadFile(gopro_url.c_str(), ("res/" + download_path).c_str(), [&target_ip, &start](size_t received_bytes, size_t total_bytes){
            if(SERVER_MEDIA_DOWNLOAD_LOG){
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                if(elapsed.count() >= SERVER_MEDIA_DOWNLOAD_PERIOD){
                    start = end;
                    std::cout << "[last_media] download " << target_ip << " " << received_bytes << " / " << total_bytes << std::endl;
                }
            }
        });
        std::cout << "[last_media] return value: " << target_ip << " => " << download_path << std::endl;
        return download_path;
    }
}

std::vector<SingleResponse> gopro_controller_get_filename_fetch_IRL(gopro_controller& controller, const std::string target_ip, const std::vector<std::string> filenames, const bool is_local) {
    std::cout << "Http GET /all_media " << target_ip << ", " << is_local << std::endl;

    if (target_ip.empty()) {
        std::cerr << "[all_media] " << target_ip << " Missing ip parameter" << std::endl;
        return std::vector<std::pair<std::string, std::string>>();
    }
    
    std::vector<std::pair<std::string, std::string>> results = std::vector<std::pair<std::string, std::string>>();
    for(auto filename : filenames){
        std::string gopro_url = "http://" + target_ip + ":8080/videos/DCIM/" + filename + "?download=true";
        if(is_local){
            std::cout << "[last_media] return value: " << target_ip << " => " << gopro_url << std::endl;
            results.push_back(std::make_pair(filename, gopro_url));
        }else{
            int32_t t = 0;
            std::string download_path = "temp.download";
            while(fs::exists("res/" + download_path)){
                download_path = "temp.download" + std::to_string(t);
                t++;
            }
            std::cout << "[last_media] try download " << gopro_url.c_str() << std::endl;
#ifdef SERVER_MEDIA_DOWNLOAD_LOG
            auto start = std::chrono::high_resolution_clock::now();
#endif
            size_t size = requests::downloadFile(gopro_url.c_str(), ("res/" + download_path).c_str(), [&target_ip, &start](size_t received_bytes, size_t total_bytes){
#ifdef SERVER_MEDIA_DOWNLOAD_LOG
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                if(elapsed.count() >= SERVER_MEDIA_DOWNLOAD_PERIOD){
                    start = end;
                    std::cout << "[last_media] download " << target_ip << " " << received_bytes << " / " << total_bytes << std::endl;
                }
#endif
            });
            std::cout << "[last_media] return value: " << target_ip << " => " << download_path << std::endl;
            results.push_back(std::make_pair(filename, download_path));
        }
    }
    return results;
}

std::string gopro_controller_get_thumbnail_data(gopro_controller& controller, const std::string target_ip, const std::string path, const bool is_local) {
    std::cout << "Http GET /thumbnail " << target_ip << ", " << is_local << std::endl;

    if (target_ip.empty()) {
        std::cerr << "[thumbnail] " << target_ip << " Missing ip parameter" << std::endl;
        return "";
    }

    const std::vector<uint8_t> res = exec_byte("http://" + target_ip + ":8080/gopro/media/screennail?path=" + path);
    std::string result = base64_encode(res);
    return result;
}

std::string gopro_controller_get_media_info_data(gopro_controller& controller, const std::string target_ip, const std::string path, const bool is_local) {
    std::cout << "Http GET /media_info " << target_ip << ", " << is_local << std::endl;

    if (target_ip.empty()) {
        std::cerr << "[media_info] " << target_ip << " Missing ip parameter" << std::endl;
        return "";
    }

    std::string result = exec("http://" + target_ip + ":8080/gopro/media/info?path=" + path);
    return result;
}
