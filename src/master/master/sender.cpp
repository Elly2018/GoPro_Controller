/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"

void gopro_master_packet_sender(AppData& data, const std::string key, const std::string server, const std::string command, const std::string target, const std::string value) {
    json data = json::object();
    data["key"] = key;
    data["value"] = json::object();
    data["value"]["name"] = command;
    data["value"]["target"] = target;
    data["value"]["value"] = value;

    for(auto s : data.master.servers){
        if(!s.vaild) continue;
        if(!s.connected) continue;
        if(server.size() > 0 && server != std::string(s.ip)) continue;
        s.client.send(data.dump());
    }
}

void gopro_master_command_only(AppData& data, const std::string command, const std::string target) {
    gopro_master_packet_sender(data, "command", "", command, target, "");
}

void gopro_master_command_only(AppData& data, const std::string server, const std::string command, const std::string target) {    
    gopro_master_packet_sender(data, "command", server, command, target, "");
}

void gopro_master_command_with_value(AppData& data, const std::string command, std::string target, const std::string value) {
    gopro_master_packet_sender(data, "command", "", command, target, value);
}

void gopro_master_query_only(AppData& data, const std::string command, const std::string target) {
    gopro_master_packet_sender(data, "command", "", command, target);
}

void gopro_master_query_only(AppData& data, const std::string server, const std::string command, const std::string target) {
    gopro_master_packet_sender(data, "query", server, command, target);
}

void gopro_master_webcam_only(AppData& data, const std::string command, const std::string target = "") {
    gopro_master_packet_sender(data, "query", "", command, target);
}

void gopro_master_webcam_only(AppData& data, const std::string server, const std::string command, const std::string target = "") {
    gopro_master_packet_sender(data, "query", server, command, target);
}

void gopro_master_webcam_start(AppData& data, const std::string server) {
    
}

void gopro_master_preview_start(AppData& data, const std::string server, const std::string target) {
    gopro_master_packet_sender(data, "preview", server, "start", target);
}

void gopro_master_preview_end(AppData& data, const std::string server, const std::string target) {
    gopro_master_packet_sender(data, "preview", server, "start", target);
}

void gopro_master_get_media_info(AppData& data, const std::string server, const std::string ip, const std::string path) {

}

void gopro_master_get_media_list(AppData& data, const std::string server, const std::string ip) {

}
