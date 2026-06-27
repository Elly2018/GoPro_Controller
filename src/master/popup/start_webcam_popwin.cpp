/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "start_webcam_popwin.h"
#include "../../common/camera_code.h"

void start_webcam_popup_render(Start_webcam_popup& win) {
    if(ImGui::BeginPopupModal(win.base.base.title, NULL, wp_flag)){
        bool updated = false;

        updated = ImGui::InputText("Server IP", &win.server_ip_buf, sizeof(win.server_ip_buf));
        updated = ImGui::InputText("Port Start", &win.port_buf, sizeof(win.port_buf));
        updated = ImGui::Checkbox("Use TS", &win.ts_buf, sizeof(win.ts_buf));

        if(ImGui::BeginCombo("Res", &win.res_string_buf)){

            for(int32_t n = 0; n < WEBCAM_START_RES_SIZE; n++){

                std::string option = WEBCAM_START_RES_STRING[n];

                if(option.size() == 0) continue;
                bool is_selected = (std::string(res_string_buf) == option); // You can store your selection however you want, outside or inside your objects
                std::string option_r = option + ("##WebcamOption_" + std::string(WEBCAM_START_RES_NAME)); 
                if (ImGui::Selectable(option_r.c_str(), is_selected))
                {
                    updated = true;
                    win.res_buf = n;
                    win.res_string_buf = option.c_str();
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus(); 
            }

            ImGui::EndCombo();
        }

        if(ImGui::BeginCombo("Fov", &win.fov_string_buf)){

            for(int32_t n = 0; n < WEBCAM_START_FOV_SIZE; n++){
                std::string option = WEBCAM_START_FOV_STRING[n];
                if(option.size() == 0) continue;
                bool is_selected = (std::string(win.fov_string_buf) == option); // You can store your selection however you want, outside or inside your objects
                std::string option_r = option + ("##WebcamOption_" + std::string(WEBCAM_START_FOV_NAME)); 
                if (ImGui::Selectable(option.c_str(), is_selected))
                {
                    updated = true;
                    fov_buf = n; // Change index
                    fov_string_buf = option;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus(); 
            }
            ImGui::EndCombo();
        }
        
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", error.c_str());
        if(updated){
            error.clear();
        }
        if(ImGui::Button("Confirm")){
            
        }
        ImGui::SameLine();
        if(ImGui::Button("Cancel")){
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}