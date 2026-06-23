#include "../inspector.h"
#include <iostream>
#include <string>

bool InspectorWindow::conditional_filter(const std::shared_ptr<GlobalState>& state, int32_t mymodel, int32_t setting_id){
    int32_t preset = state->try_get_status_int32_by_id(PRESET_ID);

    int32_t profile = state->try_get_setting_int32_by_id(PROFILES_ID);
    int32_t res = state->try_get_setting_int32_by_id(VIDEO_RESOLUTION_ID);
    int32_t aspect = state->try_get_setting_int32_by_id(VIDEO_ASPECT_RATIO_ID);
    int32_t fps = state->try_get_setting_int32_by_id(FRAMES_PER_SECOND_ID);
    int32_t antif = state->try_get_setting_int32_by_id(ANTI_FLICKER_V2_ID);
    int32_t videolen = state->try_get_setting_int32_by_id(VIDEO_LENS_ID);
    int32_t photo_out = state->try_get_setting_int32_by_id(PHOTO_OUTPUT_ID);
    int32_t iso_auto = state->try_get_setting_int32_by_id(ISO_AUTO_ID);
    
    int32_t profile_id = PROFILES_VALUE[profile];
    int32_t res_id = VIDEO_RESOLUTION_VALUE[res];
    int32_t aspect_id = VIDEO_ASPECT_RATIO_VALUE[aspect];
    int32_t fps_id = FRAMES_PER_SECOND_VALUE[fps];
    int32_t videolen_id = VIDEO_LENS_VALUE[videolen];
    int32_t photo_out_id = PHOTO_OUTPUT_VALUE[photo_out];
    int32_t iso_auto_id = ISO_AUTO_VALUE[iso_auto];

    bool isMission1 = mymodel == MODEL_MISSION;

    if(setting_id == SHUTTER_SPEED_VIDEO_ID){
        if(profile_id == 1 || profile_id == 101) return false; // HDR
    }
    else if(setting_id == EXPOSURE_ID){
        int32_t shutter = state->try_get_setting_int32_by_id(SHUTTER_SPEED_VIDEO_ID);
        if(shutter != 0) return false; // Shutter Auto
        if(preset == 0){ // Video
            if(profile_id == 1 || profile_id == 101){ // HDR
                return false; 
            }
        }
    }
    else if(setting_id == SHUTTER_SPEED_PHOTO_ID){
        if(photo_out_id == 2) return false;
    }
    else if(setting_id == EXPOSURE_ID){
        if(preset == 0){ // Video

        }else { // Photo
            if(photo_out_id == 2) return false;
        }
    }
    else if(setting_id == ISO_MAX_PHOTO_ID){
        if(photo_out_id == 2) return false;
    }
    else if(setting_id == ISO_MIN_PHOTO_ID){
        if(photo_out_id == 2) return false;
    }
    else if(setting_id == ISO_MAX_VIDEO_ID){
        if(isMission1){
            if(iso_auto_id == 0) return false; // Auto
        }
        else{
            if(profile_id == 1 || profile_id == 101) { // HDR
                return false;
            }
        }
    }
    else if(setting_id == ISO_MIN_VIDEO_ID){
        if(profile_id == 1 || profile_id == 101) { // HDR
            return false;
        }
    }
    else if(setting_id == HLG_ID){
        if(profile_id != 1 && profile_id != 101) { // Must be HDR so the option will show up
            return false;
        }
    }
    else if(setting_id == COLOR_ID){
        if(preset != 0) return false;
        if(preset == 0){ // Video
            if(profile_id == 2){ // LOG
                return false;
            }
        }
    }
    return true;
}

bool InspectorWindow::conditional_filter_option(const std::shared_ptr<GlobalState>& state, int32_t mymodel, int32_t setting_id, int32_t value_index){
    int32_t preset = state->try_get_status_int32_by_id(PRESET_ID);

    int32_t profile = state->try_get_setting_int32_by_id(PROFILES_ID);
    int32_t res = state->try_get_setting_int32_by_id(VIDEO_RESOLUTION_ID);
    int32_t aspect = state->try_get_setting_int32_by_id(VIDEO_ASPECT_RATIO_ID);
    int32_t fps = state->try_get_setting_int32_by_id(FRAMES_PER_SECOND_ID);
    int32_t antif = state->try_get_setting_int32_by_id(ANTI_FLICKER_V2_ID);
    int32_t videolen = state->try_get_setting_int32_by_id(VIDEO_LENS_ID);
    int32_t hlg = state->try_get_setting_int32_by_id(HLG_ID);
    int32_t iso_auto = state->try_get_setting_int32_by_id(ISO_AUTO_ID);
    
    int32_t profile_id = PROFILES_VALUE[profile];
    int32_t res_id = VIDEO_RESOLUTION_VALUE[res];
    int32_t aspect_id = VIDEO_ASPECT_RATIO_VALUE[aspect];
    int32_t fps_id = FRAMES_PER_SECOND_VALUE[fps];
    int32_t videolen_id = VIDEO_LENS_VALUE[videolen];
    int32_t hlg_id = HLG_VALUE[hlg];
    int32_t iso_auto_id = ISO_AUTO_VALUE[iso_auto];

    bool isMission1 = mymodel == MODEL_MISSION;

    if(setting_id == VIDEO_RESOLUTION_ID){
        int32_t value_id = VIDEO_RESOLUTION_VALUE[value_index];
        if(preset == 0){
            if(profile_id == 0){ // Standard
                if(aspect_id == 0){ // "4:3"
                    if(isMission1){
                        if(fps_id == 18){ // 480
                            // 1440 4:3, 4K 4:3
                            if(value_id != 44 && value_id != 112) return false;
                        }
                        else if(fps_id == 0){ // 240
                            // 1440 4:3, 4K 4:3
                            if(value_id != 44 && value_id != 112) return false;
                        }
                        else if(fps_id == 1){ // 120
                            // 1440 4:3, 4K 4:3
                            if(value_id != 44 && value_id != 112) return false;
                        }
                        else if(fps_id == 5){ // 60
                            // 1440 4:3, 4K 4:3
                            if(value_id != 44 && value_id != 112) return false;
                        }
                        else if(fps_id == 8){ // 30
                            // 1440 4:3, 4K 4:3, 8K 4:3
                            if(value_id != 44 && value_id != 112 && value_id != 40) return false;
                        }
                        else if(fps_id == 10){ // 24
                            // 1440 4:3, 4K 4:3, 8K 4:3
                            if(value_id != 44 && value_id != 112 && value_id != 40) return false;
                        }
                    }else{
                        // 2.7K 4:3
                        if(value_id != 6) return false;
                    }
                }
                else if(aspect_id == 1){ // "16:9"
                    if(fps_id == 18){ // 480
                        if(isMission1){
                            // 1080
                            if(value_id != 1) return false;
                        }
                        return false;
                    }
                    else if(fps_id == 0){ // 240
                        if(isMission1){
                            // 1080, 4K
                            if(value_id != 1 && value_id != 9) return false;
                        }else{
                            // 2.7K, 1080
                        if(value_id != 4 && value_id != 9) return false;
                        }
                    }
                    else if(fps_id == 1){ // 120
                        if(isMission1){
                            // 1080, 4K
                            if(value_id != 1 && value_id != 9) return false;
                        }else{
                            // 1080, 4K
                        if(value_id != 9 && value_id != 1) return false;
                        }
                    }
                    else if(fps_id == 5){ // 60
                        if(isMission1){
                            // 1080, 4K, 8K
                            if(value_id != 1 && value_id != 9 && value_id != 31) return false;
                        }
                        else{
                            if(videolen_id == 9){ // Hyperview
                                // 4K
                                if(value_id != 1) return false;
                            }else{
                                // 1080, 4K, 5.3K
                                if(value_id != 9 && value_id != 1 && value_id != 100) return false;
                            }
                        }
                    }
                    else if(fps_id == 8){ // 30
                        if(isMission1){
                            // 1080, 4K, 8K
                            if(value_id != 1 && value_id != 9 && value_id != 31) return false;
                        }
                        else{
                            // 1080, 4K, 5.3K
                            if(value_id != 9 && value_id != 1 && value_id != 100) return false;
                        }
                    }
                    else if(fps_id == 10){ // 24
                        if(isMission1){
                            // 1080, 4K, 8K
                            if(value_id != 1 && value_id != 9 && value_id != 31) return false;
                        }else{
                            // 4K, 5.3K
                            if(value_id != 1 && value_id != 100) return false;
                        }
                    }
                }
                else if(aspect_id == 3){ // "8:7"
                    // 60
                    if(fps_id == 5){
                        // 4K 8:7
                        if(value_id != 108) return false;
                    }else{
                        // 4K 8:7, 5.3K 8:7
                        if(value_id != 107 && value_id != 108) return false;
                    }
                }
                else if(aspect_id == 4){ // "9:16"
                    if(isMission1){
                        if(fps_id == 8){ // 30
                            // 4K 9:16, 1080 9:16
                            if(value_id != 109 && value_id != 110) return false;
                        }
                        else if(fps_id == 5){ // 60
                            // 1080 9:16
                            if(value_id != 110) return false;
                        }
                    }else{
                        // 4K 9:16, 1080 9:16
                        if(value_id != 109 && value_id != 110) return false;
                    }
                }
            }
            else if(profile_id == 1 || profile_id == 101){ // HDR
                if(aspect_id == 3){ // "8:7"
                    // 4K 8:7
                    if(value_id != 108) return false;
                }
                else if(aspect_id == 1){ // "16:9"
                    if(fps_id == 5 || videolen_id == 9) { // 60
                        // 4K
                        if(value_id != 1) return false;
                    }else{
                        // 4K, 5.3K
                        if(value_id != 1 && value_id != 100) return false;
                    }
                }
            }
            else if(profile_id == 2){ // LOG
                if(aspect_id == 3){ // "8:7"
                    if(fps_id == 5){ // 60
                        // 4K 8:7
                        if(value_id != 108) return false;
                    }else{
                        // 5.3K 8:7, 4K 8:7
                        if(value_id != 107 && value_id != 108) return false;
                    }
                }
                else if(aspect_id == 1){ // "16:9"
                    if(fps_id == 1 || videolen_id == 9){ // 120
                        // 4K
                        if(value_id != 1) return false;
                    }else{
                        // 4K, 5.3K
                        if(value_id != 1 && value_id != 100) return false;
                    }
                }
            }
        }
    }
    else if(setting_id == VIDEO_ASPECT_RATIO_ID){
        int32_t value_id = VIDEO_ASPECT_RATIO_VALUE[value_index];
        if(preset == 0){ // Video
            if(profile_id == 0){ // Standard
                if(value_id > 4) return false;
            }
            else if(profile_id == 1 || profile_id == 101){ // HDR
                if(value_id != 1 && value_id != 3) return false;
            }
            else if(profile_id == 2){ // LOG
                if(value_id != 1 && value_id != 3) return false;
            }
        }
    }
    else if(setting_id == FRAMES_PER_SECOND_ID){
        int32_t value_id = FRAMES_PER_SECOND_VALUE[value_index];
        if(preset == 0){ // Video
            if(profile_id == 0) { // Standard
                if(aspect_id == 0){ // "4:3"
                    // 120
                    if(value_id != 1) return false;
                }
                else if(aspect_id == 1){ // "16:9"
                    if(res_id == 1){ // 4K
                        // 30, 60, 120, 24
                        if(value_id != 8 && value_id != 5 && value_id != 1 && value_id != 10) return false;
                    }
                    else if(res_id == 100){ // 5.3K
                    }
                    else if(res_id == 4){ // 2.7K
                        // 240
                        if(value_id != 0) return false;
                    }else{ // 1080
                        // 30, 60, 120, 240
                        if(value_id != 8 && value_id != 5 && value_id != 1 && value_id != 0) return false;
                    }
                }
                else if(aspect_id == 3){ // "8:7"
                    if(res_id == 107){ // 5.3K 8:7
                        // 24, 30
                        if(value_id != 10 && value_id != 8) return false;
                    }else{ // 4K 8:7
                        // 24, 30, 60
                        if(value_id != 10 && value_id != 8 && value_id != 5) return false;
                    }
                }
                else if(aspect_id == 4){ // "9:16"
                    // 60, 30
                    if(value_id != 5 && value_id != 8) return false;
                }
            }
            else if(profile_id == 1 || profile_id == 101) { // HDR
                if(aspect_id == 3){ // 8:7
                    // 24, 30
                    if(value_id != 10 && value_id != 8) return false;
                }else{ // 16:9
                    if(res_id == 100 || videolen_id == 9 || videolen_id == 3){ // 5.3K
                        // 24, 30
                        if(value_id != 10 && value_id != 8) return false;
                    }else{ // 4K
                        // 24, 30, 60
                        if(value_id != 10 && value_id != 8 && value_id != 5) return false;
                    }
                }
            }
            else if(profile_id == 2) { // LOG
                if(aspect_id == 1){ // 16:9
                    if(res_id == 100){ // 5.3K
                        if(videolen_id == 9) { // Hyperview
                            // 30, 24
                            if(value_id != 8 && value_id != 10) return false;
                        }else{
                            // 30, 60, 24
                            if(value_id != 8 && value_id != 5 && value_id != 10) return false;
                        }
                    }else{ // 4K
                        if(videolen_id == 9) { // Hyperview
                            // 30, 60, 24
                            if(value_id != 8 && value_id != 5 && value_id != 10) return false;
                        }else{
                            // 30, 60, 120, 24
                            if(value_id != 8 && value_id != 5 && value_id != 1 && value_id != 10) return false;
                        }
                    }
                }
                else if(aspect_id == 3){ // 8:7
                    if(res_id == 107){ // 5.3K 8:7
                        // 24, 30
                        if(value_id != 10 && value_id != 8) return false;
                    }else{ // 4K 8:7
                        // 24, 30, 60
                        if(value_id != 10 && value_id != 8 && value_id != 5) return false;
                    }                   
                }
            }
        }
    }
    else if(setting_id == VIDEO_LENS_ID){
        int32_t value_id = VIDEO_LENS_VALUE[value_index];
        if(preset == 0){ // video
            if(profile_id == 0){ // standard
                if(aspect_id == 1){ // 16:9
                    if(res_id == 1){ // 4K
                        if(fps_id == 1){ // 120
                            // L, W, SV
                            if(value_id != 4 && value_id != 0 && value_id != 3) return false;
                        }else{
                            // L, W, SV, HV
                            if(value_id != 4 && value_id != 0 && value_id != 3 && value_id != 9) return false;
                        }
                    }else if(res_id == 4){ // 2.7K
                        // L, W
                        if(value_id != 4 && value_id != 0) return false;
                    }else if(res_id == 9){ // 1080
                        if(fps_id == 0){ // 240
                            // L, W, SV
                            if(value_id != 4 && value_id != 0 && value_id != 3) return false;
                        }else{
                            // L, W, SV, HV
                            if(value_id != 4 && value_id != 0 && value_id != 3 && value_id != 9) return false;
                        }
                    }else if(res_id == 100){ // 5.3K
                        if(fps_id == 5){ // 60
                            // L, W, SV
                            if(value_id != 4 && value_id != 0 && value_id != 3) return false;
                        }else{
                            // L, W, SV, HV
                            if(value_id != 4 && value_id != 0 && value_id != 3 && value_id != 9) return false;
                        }
                    }
                }else if(aspect_id == 4){ // 9:16
                    // W
                    if(value_id != 0) return false;
                }else if(aspect_id == 0){ // 4:3
                    // L, W
                    if(value_id != 4 && value_id != 0) return false;
                }else if(aspect_id == 3){ // 8:7
                    // W
                    if(value_id != 0) return false;
                }
            }
            else if(profile_id == 1 || profile_id == 101){ // HDR
                if(aspect_id == 1){ // 16:9
                    if(res_id == 1){ // 4K
                        if(fps_id == 5){ // 60
                            // L, W
                            if(value_id != 4 && value_id != 0) return false;
                        }else{
                            // L+, L, W, SV, HV
                            if(value_id != 10 && value_id != 4 && value_id != 0 && value_id != 3 && value_id != 9) return false;
                        }
                    }else if(res_id == 100){ // 5.3K
                        // L+, L, W, SV
                        if(value_id != 10 && value_id != 4 && value_id != 0 && value_id != 3) return false;
                    }
                }else if(aspect_id == 3){ // 8:7
                    // W
                    if(value_id != 0) return false;
                }
            }
            else if(profile_id == 2){ // LOG
                if(aspect_id == 1){ // 16:9
                    if(res_id == 1){ // 4K
                        if(fps_id == 1){ // 120
                            // L+, L, W, SV
                            if(value_id != 10 && value_id != 4 && value_id != 0 && value_id != 3) return false;
                        }else{
                            // L+, L, W, SV, HV
                            if(value_id != 10 && value_id != 4 && value_id != 0 && value_id != 3 && value_id != 9) return false;
                        }
                    }else if(res_id == 100){ // 5.3K
                        if(fps_id == 5){ // 60
                            // L+, L, W, SV
                            if(value_id != 10 && value_id != 4 && value_id != 0 && value_id != 3) return false;
                        }else{
                            // L+, L, W, SV, HV
                            if(value_id != 10 && value_id != 4 && value_id != 0 && value_id != 3 && value_id != 9) return false;
                        }
                    }
                }else if(aspect_id == 3){ // 8:7
                    if(value_id != 0) return false;
                }
            }
        }
    }
    else if(setting_id == SHUTTER_SPEED_VIDEO_ID){
        if((mymodel&(ANTI_FLICKER_V2_AVA)) > 0){
            int32_t value_id = SHUTTER_SPEED_VIDEO_VALUE[value_index];
            if(antif == 1){
                if(value_id != 0 && value_id != 51 && value_id != 50 &&
                value_id != 30 && value_id != 49 && value_id != 29 &&
                value_id != 48 && value_id != 28 && value_id != 47 &&
                value_id != 21 && value_id != 46 && value_id != 17 &&
                value_id != 45 && value_id != 12 && value_id != 44){
                    return false;
                }
            }else{
                if(value_id != 0 && value_id != 56 && value_id != 55 &&
                value_id != 31 && value_id != 54 && value_id != 24 &&
                value_id != 53 && value_id != 23 && value_id != 27 &&
                value_id != 22 && value_id != 20 && value_id != 18 &&
                value_id != 15 && value_id != 13 && value_id != 10 &&
                value_id != 8){
                    return false;
                }
            }
        }
    }
    else if(setting_id == PHOTO_LENS_ID){
        int32_t value_id = PHOTO_LENS_VALUE[value_index];
        if(value_id != 31 && value_id != 32) return false;
    }
    else if(setting_id == COLOR_ID){
        int32_t value_id = COLOR_VALUE[value_index];
        if(preset == 0){ // Video
            if(profile_id == 1){ // HDR
                // Natural, Vibrant
                if(value_id != 2 && value_id != 100) return false;
            }else{
                // Flat, Natural, Vibrant
                if(value_id != 1 && value_id != 2 && value_id != 100) return false;
            }
        }
    }
    else if(setting_id == PROFILES_ID){
        int32_t value_id = PROFILES_VALUE[value_index];
        if(mymodel == MODEL_13){
            // Standard, HDR, LOG
            if(hlg_id == 1){
                if(value_id != 0 && value_id != 101 && value_id != 2) return false;
            }else{
                if(value_id != 0 && value_id != 1 && value_id != 2) return false;
            }
        }else{
            // Standard, HDR, LOG
            if(value_id != 0 && value_id != 1 && value_id != 2) return false;
        }
    }
    else if(setting_id == ISO_MAX_VIDEO_ID){
        int32_t value_id = ISO_MAX_VIDEO_VALUE[value_index];
        if(isMission1){
            if(iso_auto_id == 1) { // Const
                // All const value and minus Auto
                if(value_id == 9 || value_id >= 100) return false;
            }
            else if(iso_auto_id == 2) { // Range
                if(value_id <= 100) return false;
            }
        }
    }
    return true;
}
