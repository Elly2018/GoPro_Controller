/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"

void gopro_master_update(AppData& data) {
    for (Server_connection& s : data.master.servers) {
        if (!s.connected) continue;
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