/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"

void gopro_master_add_server(AppData& data, const std::string& ip) {

}

void gopro_master_reconnect(AppData& data) {
    for (Server_connection& s : data.master.servers){
        if(!s.vaild) continue;
        std::cout << "Connecting to " << s.ip << "...\n";
        std::string url = "ws://" + std::string(s.ip) + ":9090";
        s.client.open(url.c_str());
    }
}

void gopro_master_reconnect(AppData& data, const std::string& ip) {

}

void gopro_master_disconnect(AppData& data) {
    for (Server_connection& s : data.master.servers){
        if(!s.vaild) continue;
        if(!s.connected) continue;
        std::cout << "Disconnect to " << s.ip << "...\n";
        s.client.close();
    }
}

void gopro_master_disconnect(AppData& data, const std::string& ip) {

}

void gopro_master_clean(AppData& data) {
    for (Server_connection& s : data.master.servers){
        if(!s.vaild) continue;
        if(s.connected) continue;
        std::cout << "Cleaning " << s.ip << "...\n";
        s.vaild = false;
    }
}

void gopro_master_clean(AppData& data, const std::string& ip) {

}

