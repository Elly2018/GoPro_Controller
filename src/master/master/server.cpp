/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"
#include "../common/thread_safe_queue.h"
#include <imgui.h>

bool gopro_master_add_server(AppData& data, const std::string& ip) {
    int32_t index = -1;

    for (Server_connection& s : data.master.servers) {
        if(s.ip != ip) continue;
        std::cout << "Server " << ip << " already exists.\n";
        return false;
    }

    for (int32_t i = 0; i < data.master.servers.size(); i++) {
        Server_connection& s = data.master.servers.at(i);
        if(s.vaild) continue;
        index = i;
        break;
    }

    if(index == -1) {
        std::cout << "Reached server limit: " << data.master.servers.size() << "\n";
        return false;
    }

    Server_connection conn = Server_connection();
    conn.client = hv::WebSocketClient();
    conn.ip = ip;

    conn.client.onopen = [&data, &conn]() {
        std::cout << "Connected to server: " << conn.ip << "\n";
        conn.connected = true;
        {
            ImGuiToast toast(ImGuiToastType_Success, 3000);
            toast.set_title("Server Connected");
            toast.set_content("Server ip: %s", conn->ip.c_str());
            ImGui::InsertNotification(toast);
        }
    };
    conn.client.onmessage = [&data, &conn](const std::string& msg) {
        data.master.msg_queue.push({ std::string(conn.ip), msg });
    };
    conn.client.onclose = [&data, &conn]() {
        if(conn.connected){
            std::cout << "Disconnected from server: " << conn->ip << std::endl;
            conn.connected = false;
            std::lock_guard<std::mutex> lock(camera_mtx);
            gopro_master_clean_cameras_from_server(data, conn.ip);
            
            data.master.ip_query_finish.insert_or_assign(conn.ip, false);
            data.master.state_query_finish.insert_or_assign(conn.ip, false);
            data.master.media_query_finish.insert_or_assign(conn.ip, false);
            
            ImGuiToast toast(ImGuiToastType_Warning, 3000);
            toast.set_title("Server Disconnected");
            toast.set_content("Server ip: %s", conn->ip.c_str());
            ImGui::InsertNotification(toast);
        }
    };

    data.master.servers[index] = conn;
    return true;
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
    for (Server_connection& s : data.master.servers){ 
        if(!s.vaild) continue;
        if(s.ip != ip) continue;
        std::cout << "Connecting to " << s.ip << "...\n";
        std::string url = "ws://" + std::string(s.ip) + ":9090";
        s.client.open(url.c_str());
    }
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
    for (Server_connection& s : data.master.servers){
        if(!s.vaild) continue;
        if(!s.connected) continue;
        if(s.ip != ip) continue;
        std::cout << "Disconnect to " << s.ip << "...\n";
        s.client.close();
    }
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
    for (Server_connection& s : data.master.servers){
        if(!s.vaild) continue;
        if(s.connected) continue;
        if(s.ip != ip) continue;
        std::cout << "Cleaning " << s.ip << "...\n";
        s.vaild = false;
    }
}

