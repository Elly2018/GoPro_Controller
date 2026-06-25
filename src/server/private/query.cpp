/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller_local.h"
#include "../gopro_controller.h"
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include "../../common/camera_code.h"

static void setting_utility_call(
    gopro_controller& controller,
    std::vector<SingleResponse>& r, 
    std::vector<SingleResponse>& a, 
    std::vector<int32_t>& buffer, 
    int32_t size, 
    const int32_t field[],
    std::string target, 
    json res
) {
    buffer.clear();
    for(int32_t i = 0; i < size; i++){ 
        buffer[i] = field[i]; 
    } 
    a = gopro_controller_local_set_setting_utility(controller, target, res, buffer); 
    r.insert(r.end(), a.begin(), a.end()); 
}

std::vector<SingleResponse> gopro_controller_local_query_status(gopro_controller& controller, const std::vector<std::string> targets){
    return gopro_controller_local_get_responses(controller, targets, "/gopro/camera/state");
}

SingleResponse gopro_controller_local_query_status(gopro_controller& controller, const std::string target){
    return gopro_controller_local_get_response(controller, target, "/gopro/camera/state");
}

std::vector<SingleResponse> gopro_controller_local_query_HW(gopro_controller& controller, std::vector<std::string> targets){
    return gopro_controller_local_get_responses(controller, targets, "/gopro/camera/info");
}

SingleResponse gopro_controller_local_query_HW(gopro_controller& controller, std::string target){
    return gopro_controller_local_get_response(controller, target, "/gopro/camera/info");
}

std::vector<SingleResponse> gopro_controller_local_set_setting_preset(gopro_controller& controller, const std::vector<std::string> targets, const int32_t preset, json res){
    std::vector<SingleResponse> r = std::vector<SingleResponse>();
    std::vector<SingleResponse> a = std::vector<SingleResponse>();
    std::vector<int32_t> buffer = std::vector<int32_t>();

    for(auto& target : targets){
        std::cout << "Set setting json: " << target << ", " << preset << std::endl;
        if(preset == 65538){ // Burst
            setting_utility_call(controller, r, a, buffer, GOPRO_BURST_SETTING_SIZE, GOPRO_BURST_SETTING_IDS, target, res);
            setting_utility_call(controller, r, a, buffer, GOPRO_BURST_PROTUNE_SETTING_SIZE, GOPRO_BURST_PROTUNE_SETTING_IDS, target, res);
        }else if(preset == 65536){ // Photo
            setting_utility_call(controller, r, a, buffer, GOPRO_PHOTO_SETTING_SIZE, GOPRO_PHOTO_SETTING_IDS, target, res);
            setting_utility_call(controller, r, a, buffer, GOPRO_PHOTO_PROTUNE_SETTING_SIZE, GOPRO_PHOTO_PROTUNE_SETTING_IDS, target, res);
        }else{ // Video
            setting_utility_call(controller, r, a, buffer, GOPRO_VIDEO_SETTING_SIZE, GOPRO_VIDEO_SETTING_IDS, target, res);
            setting_utility_call(controller, r, a, buffer, GOPRO_VIDEO_PROTUNE_SETTING_SIZE, GOPRO_VIDEO_PROTUNE_SETTING_IDS, target, res);
        }
        setting_utility_call(controller, r, a, buffer, GOPRO_SYSTEM_SETTING_SIZE, GOPRO_SYSTEM_SETTING_IDS, target, res);
    }
    std::cout << "[LOG] end of _setAllSetting" << std::endl;

    return r;
}

std::vector<SingleResponse> gopro_controller_local_set_setting_preset(gopro_controller& controller, const std::string target, const int32_t preset, json res){
    std::cout << "Set setting json: " << target << ", " << preset << std::endl;
    std::vector<SingleResponse> r = std::vector<SingleResponse>();
    std::vector<SingleResponse> a = std::vector<SingleResponse>();
    std::vector<int32_t> buffer = std::vector<int32_t>();
    
    if(preset == 65538){ // Burst
        setting_utility_call(controller, r, a, buffer, GOPRO_BURST_SETTING_SIZE, GOPRO_BURST_SETTING_IDS, target, res);
        setting_utility_call(controller, r, a, buffer, GOPRO_BURST_PROTUNE_SETTING_SIZE, GOPRO_BURST_PROTUNE_SETTING_IDS, target, res);
    }else if(preset == 65536){ // Photo
        setting_utility_call(controller, r, a, buffer, GOPRO_PHOTO_SETTING_SIZE, GOPRO_PHOTO_SETTING_IDS, target, res);
        setting_utility_call(controller, r, a, buffer, GOPRO_PHOTO_PROTUNE_SETTING_SIZE, GOPRO_PHOTO_PROTUNE_SETTING_IDS, target, res);
    }else{
        setting_utility_call(controller, r, a, buffer, GOPRO_VIDEO_SETTING_SIZE, GOPRO_VIDEO_SETTING_IDS, target, res);
        setting_utility_call(controller, r, a, buffer, GOPRO_VIDEO_PROTUNE_SETTING_SIZE, GOPRO_VIDEO_PROTUNE_SETTING_IDS, target, res);
    }
    setting_utility_call(controller, r, a, buffer, GOPRO_SYSTEM_SETTING_SIZE, GOPRO_SYSTEM_SETTING_IDS, target, res);

    return r;
}

std::vector<SingleResponse> gopro_controller_local_set_setting_utility(gopro_controller& controller, const std::string target, json res, const std::vector<int32_t> setting_ids){
    std::vector<SingleResponse> r = std::vector<SingleResponse>();
    std::string url = "/gopro/camera/setting?option=";

    int32_t model;
    int32_t target_model;
    json setting;
    json target_hw;
    int32_t index = gopro_controller_local_element_find(controller, target);
    if(index == -1){
        return r;
    }

    gopro_element &e = controller.camera_elements.at(index);
    std::string_view sv = e.hw;
    if(!json::accept(sv)) {
        return r;
    }

    target_hw = json::parse(sv);
    target_model = gopro_controller_local_get_current_model(controller, target_hw);
    
    if(res["model"].is_number()){
        model = res["model"].get<int32_t>();
    }
    if(res["setting"].is_object()){
        setting = res["setting"];
    }

    for(int32_t i = 0; i < setting_ids.size(); i++){
        int32_t id = setting_ids.at(i);
        if(!setting[std::to_string(id)].is_number()) continue;

        int32_t value = setting[std::to_string(id)].get<int32_t>();

        size_t size = GET_SETTING_SIZE_BY_ID(id);
        const int32_t* options = GET_SETTING_VALUE_BY_ID(id);

        if(value >= size) continue;

        std::string suburl = url + std::to_string(options[value]);
        suburl += "&setting=";
        suburl += std::to_string(id);
        r.push_back(gopro_controller_local_get_response(controller, target, suburl));
        //std::this_thread::sleep_for(std::chrono::milliseconds(350));
    }

    return r;
}

std::vector<SingleResponse> gopro_controller_local_set_setting(gopro_controller& controller, const std::vector<std::string> targets, const int32_t ID, const std::string value){
    std::string url = "/gopro/camera/setting?option=";
    url += value;
    url += "&setting=";
    url += std::to_string(ID);
    return gopro_controller_local_get_responses(controller, targets, url);
}

SingleResponse gopro_controller_local_set_setting(gopro_controller& controller, const std::string target, const int32_t ID, const std::string value){
    std::string url = "/gopro/camera/setting?option=";
    url += value;
    url += "&setting=";
    url += std::to_string(ID);
    return gopro_controller_local_get_response(controller, target, url);
}

int32_t gopro_controller_local_get_current_model(gopro_controller& controller, json hwinfo){
    if(hwinfo["model_name"].is_string()){
        std::string model_name = hwinfo["model_name"].get<std::string>();
        if(model_name == "MAX 2") return MODEL_MAX2;
        else if(model_name == "HERO13 Black") return MODEL_13;
        else if(model_name == "HERO12 Black") return MODEL_12;
        else if(model_name == "HERO11 Black") return MODEL_11_BLACK;
        else if(model_name == "HERO11 Black Mini") return MODEL_11;
        else if(model_name == "HERO10 Black") return MODEL_10;
        else if(model_name == "HERO9 Black") return MODEL_9;
    }
    return 0;
}