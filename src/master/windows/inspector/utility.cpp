#include "../inspector.h"


std::vector<int32_t> Decode_Schedule_Time(int32_t value){
    std::vector<int32_t> a = std::vector<int32_t>();
    a.push_back(0); a.push_back(0); a.push_back(0);

    if(value % 4 == 0) return std::vector<int32_t>();
    if((value - 1) % 4 == 0 && value < 3073) a[0] = 1;
    else if((value - 1) % 4 == 0 && value >= 3073) a[0] = 2;
    else if((value + 1) % 4 == 0) a[0] = 3;

    if(a[0] == 3){ // 24H
        for(int32_t i = 0; i < 24; i++){ // 256 gap
            int32_t starter = 3 + (256 * i);
            if(value >= starter && value <= starter + 236){
                a[1] = i;
                a[2] = (value - starter) / 4;
                break;
            }
        }
    }else{ // 12H
        for(int32_t i = 0; i < 12; i++){ // 256 gap
            int32_t starter = -1;
            if(a[0] == 2){ // PM
                starter = 3073 + (256 * i);
            }else{ // AM
                starter = 1 + (256 * i);
            }

            if(value >= starter && value <= starter + 236){
                a[1] = i;
                a[2] = (value - starter) / 4;
                break;
            }
        }
    }

    return a;
}

int32_t Encode_Schedule_Time(std::vector<int32_t> value){
    if(value.size() == 0) return 0;
    int32_t a = 0;
    if(value.at(0) == 0) return 0;

    if(value.at(0) == 1) a = 1; // AM
    if(value.at(0) == 2) a = 3073; // PM
    if(value.at(0) == 3) a = 3; // 24H

    a += value.at(1) * 256;
    a += value.at(2) * 4;
    return a;
}


void InspectorWindow::reset_setting_order(){
    for(int32_t i = 0; i < system_list_ordered.size(); i++){
        system_list_ordered[i] = GOPRO_SYSTEM_SETTING_IDS[i];
    }
    for(int32_t i = 0; i < video_setting_list_ordered.size(); i++){
        video_setting_list_ordered[i] = GOPRO_VIDEO_SETTING_IDS[i];
    }
    for(int32_t i = 0; i < video_protune_list_ordered.size(); i++){
        video_protune_list_ordered[i] = GOPRO_VIDEO_PROTUNE_SETTING_IDS[i];
    }
    for(int32_t i = 0; i < photo_setting_list_ordered.size(); i++){
        photo_setting_list_ordered[i] = GOPRO_PHOTO_SETTING_IDS[i];
    }
    for(int32_t i = 0; i < photo_protune_list_ordered.size(); i++){
        photo_protune_list_ordered[i] = GOPRO_PHOTO_PROTUNE_SETTING_IDS[i];
    }
    for(int32_t i = 0; i < burst_setting_list_ordered.size(); i++){
        burst_setting_list_ordered[i] = GOPRO_BURST_SETTING_IDS[i];
    }
    for(int32_t i = 0; i < burst_protune_list_ordered.size(); i++){
        burst_protune_list_ordered[i] = GOPRO_BURST_PROTUNE_SETTING_IDS[i];
    }
}

void InspectorWindow::reset_status_order(){
    for(int32_t i = 0; i < GOPRO_SOFTWARE_STATUS_SIZE; i++){
        status_software_list_ordered[i] = GOPRO_SOFTWARE_STATUS_IDS[i];
    }
    for(int32_t i = 0; i < GOPRO_HARDWARE_STATUS_SIZE; i++){
        status_hardware_list_ordered[i] = GOPRO_HARDWARE_STATUS_IDS[i];
    }
    for(int32_t i = 0; i < GOPRO_ENCODE_STATUS_SIZE; i++){
        status_encode_list_ordered[i] = GOPRO_ENCODE_STATUS_IDS[i];
    }
    for(int32_t i = 0; i < GOPRO_NETWORK_STATUS_SIZE; i++){
        status_network_list_ordered[i] = GOPRO_NETWORK_STATUS_IDS[i];
    }
    for(int32_t i = 0; i < GOPRO_MEDIA_STATUS_SIZE; i++){
        status_media_list_ordered[i] = GOPRO_MEDIA_STATUS_IDS[i];
    }
}

int32_t InspectorWindow::_get_current_model(json hwinfo){
    if(hwinfo["model_name"].is_string()){
        std::string model_name = hwinfo["model_name"].get<std::string>();
        if(model_name == "MISSION 1 PRO") return MODEL_MISSION;
        else if(model_name == "MAX 2") return MODEL_MAX2;
        else if(model_name == "HERO13 Black") return MODEL_13;
        else if(model_name == "HERO12 Black") return MODEL_12;
        else if(model_name == "HERO11 Black") return MODEL_11_BLACK;
        else if(model_name == "HERO11 Black Mini") return MODEL_11;
        else if(model_name == "HERO10 Black") return MODEL_10;
        else if(model_name == "HERO9 Black") return MODEL_9;
    }
    return 0;
}
