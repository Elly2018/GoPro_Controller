/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"

bool gopro_master_get_settings_from_camera(AppData& data, const Camera_info& target, json& res) {
    json data = target.state;
    if(!data["settings"].is_object()){
        return false;
    }
    res = data["settings"];
    for(int32_t i = 0; i < GOPRO_SETTING_SIZE; i++){
        int32_t id = GOPRO_SETTING_IDS[i];
        if(!res[std::to_string(id)].is_number()) continue;
        int32_t value = res[std::to_string(id)].get<int32_t>();

        const size_t size = GET_SETTING_SIZE_BY_ID(id);
        const int32_t* all_values = GET_SETTING_VALUE_BY_ID(id);
        for(int32_t j = 0; j < size; j++){
            if(all_values[j] == value){
                res[std::to_string(id)] = j;
                break;
            }
        }
    }
    return true;
}

bool gopro_master_get_status_from_camera(AppData& data, const Camera_info& target, json& res) {
    json data = target.state;
    if(!data["status"].is_object()){
        return false;
    }
    res = data["status"];
    for(int32_t i = 0; i < GOPRO_STATUS_SIZE; i++){
        int32_t id = GOPRO_STATUS_IDS[i];
        const int32_t type = GET_STATUS_TYPE_BY_ID(id);
        if(type != (int32_t)CAMERA_STATUS_TYPE::OPTION){
            continue; 
        }
        if(!res[std::to_string(id)].is_number()) continue;
        int32_t value = res[std::to_string(id)].get<int32_t>();

        const size_t size = GET_STATUS_SIZE_BY_ID(id);
        const int32_t* all_values = GET_STATUS_VALUE_BY_ID(id);
        for(int32_t j = 0; j < size; j++){
            if(all_values[j] == value){
                res[std::to_string(id)] = j; 
                break;
            }
        }
    }
    return true;
}

std::string gopro_master_get_bar_info(AppData& data, const Camera_info &c) {
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

uint32_t gopro_master_get_server_count(AppData& data) {
    uint32_t a = 0;
    for(const Server_connection& s : data.master.servers){ 
        if(!s.vaild) continue;
        a++;
    }
    return a;
}

int32_t gopro_master_find_server(AppData& data, const std::string ip) {
    int32_t index = 0;
    for(const Server_connection& s : data.master.servers){
        if(!s.vaild) continue;
        if(s.ip == ip){
            return index;
        }
        ++index;
    }
    return -1;
}

int32_t gopro_master_find_camera(AppData& data, const std::string server, const std::string ip) {
    int32_t index = 0;
    for(const Camera_info& c : data.master.cameras){
        if(!c.vaild) continue;
        if(c.server == server && c.ip == ip){
            return index;
        }
        ++index;
    }
    return -1;
}

std::vector<u_char> gopro_master_decode_base64(const std::string& input) {
    static const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::vector<int32_t> T(256, -1);
    for (int32_t i = 0; i < 64; i++) T[base64_chars[i]] = i;

    std::vector<u_char> out;
    int32_t val = 0, valb = -8;
    for (u_char c : input) {
        if (T[c] == -1) continue;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(static_cast<u_char>((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}
