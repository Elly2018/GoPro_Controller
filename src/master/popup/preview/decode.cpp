/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../preview_popwin.h"
#include <format>
#include <cstdlib>
#include "../../gopro_master.h"
#include "../../data/camera_info.h"

void preview_popup_update_decoder(Preview_popup& win) {
    Global_state& state = win.base.base.state;
    Gopro_master& master = win.base.base.master;
    AppData& appdata = state.appdata;
    win.stream_open = false;
    win.trying = true;
    int32_t s = -1;
    int32_t model;

    if(win.first){
        std::cout << "===== OpenCV Build Info =====\n";
        std::cout << cv::getBuildInformation() << "\n";
        std::cout << "=============================\n";
        win.first = false;
    }

    s = gopro_master_find_camera(appdata, state.preview_server, state.preview_ip);

    if(s == -1){
        std::cout << "[Preview Decoder] Cannot find camera: " << state.preview_ip << std::endl;
        win.trying = false;
        return;
    }

    const Camera_info& c = master.cameras.at(s);
    model = preview_popup_get_current_model(c.hw);
    json buffer_setting = json::object();
    gopro_master_get_settings_from_camera(appdata, c, buffer_setting);

    if(gl_texture != 0){
        glDeleteTextures(1, &gl_texture);
        gl_texture = 0;
    }

    win.pipeline = 
        "udpsrc port=8554 timeout=1000000000 "
        "! watchdog timeout=1000 "
        "! queue max-size-buffers=0 max-size-bytes=0 max-size-time=1000000000 "
        // Treet incoming UDP byte array as TS format
        "! tsdemux "
        /**
         * We nned to use general decodebin, because GOPRO model might have use
         * H265 or H264, We have no way to find out except fetch info from the incoming camera
         * But i'm too lazy for that. so i just want GStreamer do the detection for me
         */
        "! decodebin "
        // Convert to video feed
        "! videoconvert "
        // Leave video only and drop audio data
        "! video/x-raw,format=BGR "
        // Output to application use sink
        "! appsink sync=false drop=true max-buffers=1";
    
    for(int32_t j = 0; j < Preview_popup::MAX_REDECODE; j++){
        win.cap.open(win.pipeline, cv::CAP_GSTREAMER);
        std::cout << "[Preview Decoder] Pipeline use:" << "\n" << pipeline << "\n";

        if(win.cap.isOpened()){
            cv::Mat test;
            for(int i = 0; i < MAX_ATTEMPT; i++) {
                std::cout << "[Preview Decoder] Try cap.grab" << std::endl;
                if(cap.grab()) {
                    std::cout << "[Preview Decoder] cap.retrieve" << std::endl;
                    if(cap.retrieve(test) && !test.empty()){
                        stream_open = true;
                        std::cout << "[Preview Decoder] Pipeline opened successfully! " << test.cols << "x" << test.rows << std::endl;
                        texture_width = test.cols;
                        texture_height = test.rows;
                        std::cout << "[Preview Decoder] Get resolution setting from camera: " << texture_width << ", " << texture_height << std::endl;
                        break;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(33)); // Match ~30fps
            }
            if(!stream_open){
                std::cout << "[Preview Decoder] No valid frames in first " << MAX_ATTEMPT << " attempts, releasing..." << std::endl;
                cap.release();
            }
        } else {
            std::cout << "[Preview Decoder] Failed to open pipeline, retrying in 1s..." << std::endl;
            cap.release();
        }
    }

    if(!stream_open){
        std::cerr << "[Preview Decoder] Could not open pipeline" << std::endl;
        trying = false;
        return;
    }
    
    cv::Mat frame;
    std::cout << "[Preview Decoder] Decoding started!" << std::endl;

    while(stream_open){
        if(!cap.isOpened()){
            std::cerr << "[Preview Decoder] Pipeline closed unexpectedly!" << std::endl;
            trying = false;
            break;
        }

        if(cap.read(frame)){
            if(!frame.empty()){
                std::lock_guard<std::mutex> lock(queue_mutex);
                if(frame_queue.size() >= MAX_QUEUE_SIZE){
                    frame_queue.pop();
                }
                frame_queue.push(frame.clone());
            }
        } else {
            // cap.read failed - stream might have dropped
            std::cerr << "[Preview Decoder] cap.read() failed, stream dropped?" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if(!isopen) break;
    }

    std::cout << "[Preview Decoder] Update decoder end !" << std::endl;
    trying = false;
}
