#include "../camera_list.h"
#include "../inspector.h"

void CameraListWindow::draw_group_header(const CameraInfo& c){
    json status = json::object();
    json setting = json::object();
    int32_t model_enum = InspectorWindow::_get_current_model(c.hw);
    int preset = 0;
    master->getStatusFromCamera(c, status);
    master->getSettingsFromCamera(c, setting);

    ImGui::BeginGroup();
    ImGuiStyle& style = ImGui::GetStyle();
    float fontsize = ImGui::GetFontSize();
    std::string id = c.ip + "##Grid_Item_ID";
    std::string pid = c.ip + "##Grid_Popup_Item_ID";
    ImGui::PushID(id.c_str());

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 image_pos = ImGui::GetCursorScreenPos();
    ImVec2 rect_size = get_rect_size();
    ImVec2 rect_size_unit = ImVec2(rect_size.x / 12.0F, rect_size.y / 12.0F);

    ImVec2 image_pos_max = image_pos + rect_size;
    uint32_t col_white = IM_COL32(255, 255, 255, 255);
    uint32_t col_grey = IM_COL32(210, 210, 210, 255);
    uint32_t col_grey_light = IM_COL32(210, 210, 210, 50);
    uint32_t col_red = IM_COL32(230, 10, 10, 255);
    uint32_t col_orange = IM_COL32(230, 230, 10, 255);
    uint32_t col_orange_dark = IM_COL32(80, 80, 10, 255);
    uint32_t col_greed = IM_COL32(10, 230, 10, 255);

    {
        if(status[std::to_string(PRESET_ID)].is_number_integer()){
            preset = status[std::to_string(PRESET_ID)].get<int32_t>();
        }
    }

    // Drawing outline
    {
        uint32_t col = col_red;
        if(c.connected) col = col_greed;
        draw_list->AddRect(image_pos + ImVec2(5, 5), image_pos_max - ImVec2(5, 5), col, 2.0F, 0, 2.0F);
    }
    // Drawing Battery
    if(c.connected){
        bool batteryHave = false;
        bool batteryCharging = false;
        int precentage = 0;
        uint32_t col_inner_color;
        if(status[std::to_string(BATTERY_PRESENT_ID)].is_number()){
            batteryHave = status[std::to_string(BATTERY_PRESENT_ID)].get<int32_t>() == 1;
        }
        if(status[std::to_string(INTERNAL_BATTERY_PERCENTAGE_ID)].is_number()){
            precentage = status[std::to_string(INTERNAL_BATTERY_PERCENTAGE_ID)].get<int32_t>();
        }
        if(status[std::to_string(INTERNAL_BATTERY_BARS_ID)].is_number()){
            batteryCharging = status[std::to_string(INTERNAL_BATTERY_BARS_ID)].get<int32_t>() == 4;
        }
        ImVec2 battery_text_size;
        std::string battery_text;
        if(batteryHave){
            if(precentage <= 25){
                col_inner_color = col_orange;
            }else{
                col_inner_color = col_greed;
            }
            battery_text = std::to_string(precentage) + "%";
        }else{
            col_inner_color = col_red;
            battery_text = "X";
        }
        battery_text_size = ImGui::CalcTextSize(battery_text.c_str());
        ImVec2 bettery_size = ImVec2(rect_size_unit.x * 2.2, rect_size_unit.y * 1.2F);
        ImVec2 frame_padding = ImVec2(10, 10);
        ImVec2 inner_padding = ImVec2(2, 2);
        int32_t spacing = 15;

        // Drawing Battery outline
        ImVec2 outter_min = image_pos + ImVec2(rect_size.x - (frame_padding.x + bettery_size.x), frame_padding.y);
        ImVec2 outter_max = image_pos + ImVec2(rect_size.x - frame_padding.x, frame_padding.y + bettery_size.y);
        draw_list->AddRectFilled(
            outter_min, 
            outter_max, 
            col_grey);
            
        // Drawing Battery inline
        ImVec2 inner_min = outter_min + inner_padding;
        ImVec2 inner_max = outter_max - inner_padding;
        float w = inner_max.y - inner_min.y;
        float wc = w * (precentage / 100.0F);
        float wr = w - wc;
        inner_max.x -= wr;
        draw_list->AddRectFilled(
            inner_min, 
            inner_max, 
            col_inner_color);

        // Drawing Battery text
        ImVec2 text_pos = ImVec2(outter_max.x - battery_text_size.x, outter_max.y);
        draw_list->AddText(text_pos, col_white, battery_text.c_str());

        if(batteryCharging){
            std::string charging_text = "C=>";
            ImVec2 charging_text_size = ImGui::CalcTextSize(charging_text.c_str());
            ImVec2 charging_text_pos = ImVec2(inner_min.x, 
                ((inner_max.y + inner_min.y) / 2.0F) - (charging_text_size.y / 2.0F)
            );
            draw_list->AddText(charging_text_pos, col_orange_dark, charging_text.c_str());
        }
    }
    // Drawing SD card
    if(c.connected){
        bool sdHave = false;
        int64_t remaining = 0;
        uint32_t col_inner_color;
        if(status[std::to_string(PRIMARY_STORAGE_ID)].is_number()){
            int b = status[std::to_string(PRIMARY_STORAGE_ID)].get<int32_t>() == 1;
            if(b == 1) sdHave = true;
        }
        if(status[std::to_string(SD_CARD_REMAINING_ID)].is_number()){
            remaining = status[std::to_string(SD_CARD_REMAINING_ID)].get<int64_t>();
        }
        ImVec2 sd_text_size;
        std::string sd_text;
        if(sdHave){
            col_inner_color = col_greed;
            sd_text = bytesToGbString(remaining);
        }else{
            col_inner_color = col_red;
            sd_text = "X";
        }
        sd_text_size = ImGui::CalcTextSize(sd_text.c_str());
        ImVec2 sd_size = ImVec2(rect_size_unit.x * 2.2, rect_size_unit.y * 1.2F);
        ImVec2 frame_padding = ImVec2(10, 10);
        ImVec2 inner_padding = ImVec2(2, 2);
        int32_t spacing = 15;

        // Drawing SD outline
        ImVec2 outter_min = image_pos + frame_padding;
        ImVec2 outter_max = image_pos + frame_padding + sd_size;
        draw_list->AddRectFilled(
            outter_min, 
            outter_max, 
            col_grey);
            
        // Drawing SD inline
        ImVec2 inner_min = outter_min + inner_padding;
        ImVec2 inner_max = outter_max - inner_padding;
        draw_list->AddRectFilled(
            inner_min, 
            inner_max, 
            col_inner_color);

        // Drawing SD text
        ImVec2 text_pos = ImVec2(outter_min.x, outter_max.y);
        draw_list->AddText(text_pos, col_white, sd_text.c_str());
    }
    // Center text
    {
        std::string shutter_speed;
        std::string camera_title = c.name;
        std::string iso_setting;
        std::string white_balance_setting;
        float spacing = 0.75F;

        ImVec2 camera_title_size = ImGui::CalcTextSize(camera_title.c_str());

        // Draw Title in center
        ImVec2 center = ImVec2(
            image_pos.x + (rect_size.x / 2.0F),
            image_pos.y + (rect_size.y / 2.0F)
        );
        ImVec2 camera_title_min = ImVec2(
            center.x + ( camera_title_size.x / -2.0F ),
            center.y + ( camera_title_size.y / -2.0F ) + (rect_size_unit.y * (spacing * -3.0F))
        );
        draw_list->AddText(camera_title_min, col_white, camera_title.c_str());
        if(c.connected) {
            int32_t SHUTTER_SPEED_ID = SHUTTER_SPEED_PHOTO_ID;
            int32_t ISO_MIN_ID = ISO_MIN_PHOTO_ID;
            int32_t ISO_MAX_ID = ISO_MAX_PHOTO_ID;
            if(preset == 0){
                SHUTTER_SPEED_ID = SHUTTER_SPEED_VIDEO_ID;
                ISO_MIN_ID = ISO_MIN_VIDEO_ID;
                ISO_MAX_ID = ISO_MAX_VIDEO_ID;
            }

            if(setting[std::to_string(SHUTTER_SPEED_ID)].is_number_integer()){
                int32_t re = setting[std::to_string(SHUTTER_SPEED_ID)].get<int32_t>();
                shutter_speed = SHUTTER_SPEED_VIDEO_STRING[re];
                shutter_speed = "S: " + shutter_speed;
            }
            if(model_enum == MODEL_MISSION) {
                if(setting[std::to_string(ISO_AUTO_ID)].is_number() && setting[std::to_string(ISO_MAX_ID)].is_number()){
                    int32_t iso_auto = setting[std::to_string(ISO_AUTO_ID)].get<int32_t>();
                    int32_t iso_max = setting[std::to_string(ISO_MAX_ID)].get<int32_t>();
                    std::string iso_max_text = "ISO MAX";
                    if(iso_auto == 0){
                        iso_max_text = "AUTO";
                    }else{
                        if(preset == 0){
                            iso_max_text = ISO_MAX_VIDEO_STRING[iso_max];
                        }else{
                            iso_max_text = ISO_MAX_PHOTO_STRING[iso_max];
                        }
                    }
                    iso_setting = "I: " + iso_max_text;
                }
            }else{
                if(setting[std::to_string(ISO_MIN_ID)].is_number() && setting[std::to_string(ISO_MAX_ID)].is_number()){
                    int32_t iso_min = setting[std::to_string(ISO_MIN_ID)].get<int32_t>();
                    int32_t iso_max = setting[std::to_string(ISO_MAX_ID)].get<int32_t>();
                    std::string iso_min_text = "ISO MIN";
                    std::string iso_max_text = "ISO MAX";
                    if(preset == 0){
                        iso_min_text = ISO_MIN_VIDEO_STRING[iso_min];
                        iso_max_text = ISO_MAX_VIDEO_STRING[iso_max];
                    }else{
                        iso_min_text = ISO_MIN_PHOTO_STRING[iso_min];
                        iso_max_text = ISO_MAX_PHOTO_STRING[iso_max];
                    }
                    iso_setting = "I: " + iso_min_text + " " + iso_max_text;
                }
            }
            if(setting[std::to_string(WHITE_BALANCE_ID)].is_number()){
                int32_t white_bal = setting[std::to_string(WHITE_BALANCE_ID)].get<int32_t>();
                white_balance_setting = WHITE_BALANCE_STRING[white_bal];
            }

            ImVec2 shutter_speed_size = ImGui::CalcTextSize(shutter_speed.c_str());
            ImVec2 shutter_speed_min = ImVec2(
                center.x + ( shutter_speed_size.x / -2.0F ),
                center.y + ( shutter_speed_size.y / -2.0F ) + (rect_size_unit.y * (spacing * -1.0F))
            );
            draw_list->AddText(shutter_speed_min, col_white, shutter_speed.c_str());

            ImVec2 iso_setting_size = ImGui::CalcTextSize(iso_setting.c_str());
            ImVec2 iso_setting_min = ImVec2(
                center.x + ( iso_setting_size.x / -2.0F ),
                center.y + ( iso_setting_size.y / -2.0F ) + (rect_size_unit.y * (spacing * 1.0F))
            );
            draw_list->AddText(iso_setting_min, col_white, iso_setting.c_str());

            ImVec2 white_balance_setting_size = ImGui::CalcTextSize(white_balance_setting.c_str());
            ImVec2 white_balance_setting_min = ImVec2(
                center.x + ( white_balance_setting_size.x / -2.0F ),
                center.y + ( white_balance_setting_size.y / -2.0F ) + (rect_size_unit.y * (spacing * 3.0F))
            );
            draw_list->AddText(white_balance_setting_min, col_white, white_balance_setting.c_str());
        }
    }
    // Record Time
    if(c.connected){
        ImVec2 frame_padding = ImVec2(10, 10);
        ImVec2 center = ImVec2(
            image_pos.x + (rect_size.x / 2.0F),
            image_pos.y + (rect_size.y / 2.0F)
        );

        std::string record_time;

        if(status[std::to_string(VIDEO_ENCODING_DURATION_ID)].is_number_integer()){
            int32_t re = status[std::to_string(VIDEO_ENCODING_DURATION_ID)].get<int32_t>();
            record_time = toTimeCode(re);
        }

        ImVec2 record_time_size = ImGui::CalcTextSize(record_time.c_str());
        ImVec2 record_time_min = ImVec2(
            center.x + ( record_time_size.x / -2.0F ),
            image_pos.y + frame_padding.y
        );
        draw_list->AddText(record_time_min, col_white, record_time.c_str());
    }
    // Preset mode
    if(c.connected){
        int32_t preset;
        std::string preset_text;
        if(status[std::to_string(PRESET_ID)].is_number_integer()){
            preset = status[std::to_string(PRESET_ID)].get<int32_t>();
        }

        if(preset == GOPRO_MODE_VALUE[0]) preset_text = "V";
        else if(preset == GOPRO_MODE_VALUE[1]) preset_text = "PB";
        else if(preset == GOPRO_MODE_VALUE[2]) preset_text = "PS";
        else if(preset == GOPRO_MODE_VALUE[3]) preset_text = "T";
        else if(preset == GOPRO_MODE_VALUE[4]) preset_text = "TT";
        else if(preset == GOPRO_MODE_VALUE[5]) preset_text = "TLP";
        else if(preset == GOPRO_MODE_VALUE[6]) preset_text = "TLT";
        else if(preset == GOPRO_MODE_VALUE[7]) preset_text = "TV";
        else if(preset == GOPRO_MODE_VALUE[8]) preset_text = "TNV";
        else preset_text = std::to_string(preset);

        ImVec2 frame_padding = ImVec2(10, 10);
        ImVec2 preset_text_size = ImGui::CalcTextSize(preset_text.c_str());
        draw_list->AddText(ImVec2(
            image_pos.x + frame_padding.x,
            (image_pos.y + rect_size.y) - (frame_padding.y + preset_text_size.y)
        ), col_white, preset_text.c_str());
    }
    // Setting
    if(c.connected){
        float spacing = 0.75F;
        float word_spacing = 10;
        std::string res;
        std::string fps;
        std::string profile;
        std::string framing;

        if(setting[std::to_string(VIDEO_RESOLUTION_ID)].is_number_integer()){
            int32_t re = setting[std::to_string(VIDEO_RESOLUTION_ID)].get<int32_t>();
            res = VIDEO_RESOLUTION_STRING[re];
        }
        if(setting[std::to_string(FRAMES_PER_SECOND_ID)].is_number_integer()){
            int32_t re = setting[std::to_string(FRAMES_PER_SECOND_ID)].get<int32_t>();
            fps = FRAMES_PER_SECOND_STRING[re];
        }
        if(setting[std::to_string(PROFILES_ID)].is_number_integer()){
            int32_t re = setting[std::to_string(PROFILES_ID)].get<int32_t>();
            profile = PROFILES_STRING[re];
        }
        if(setting[std::to_string(FRAMING_ID)].is_number_integer()){
            int32_t re = setting[std::to_string(FRAMING_ID)].get<int32_t>();
            framing = FRAMING_STRING[re];
            while(framing.size() > 1){
                framing.pop_back();
            }
        }

        ImVec2 res_text_size = ImGui::CalcTextSize(res.c_str());
        ImVec2 fps_text_size = ImGui::CalcTextSize(fps.c_str());
        ImVec2 profile_text_size = ImGui::CalcTextSize(profile.c_str());
        ImVec2 framing_text_size = ImGui::CalcTextSize(framing.c_str());
        ImVec2 frame_padding = ImVec2(5, 5);

        ImVec2 corner = image_pos + rect_size;
        ImVec2 profile_pos = ImVec2(
            corner.x - (frame_padding.x + profile_text_size.x),
            corner.y - (frame_padding.y + profile_text_size.y + ((rect_size_unit.y * 2.0F) * spacing))
        );
        draw_list->AddText(profile_pos, col_white, profile.c_str());

        ImVec2 framing_pos = ImVec2(
            corner.x - (frame_padding.x + framing_text_size.x),
            corner.y - (frame_padding.y + framing_text_size.y)
        );
        draw_list->AddText(framing_pos, col_white, framing.c_str());

        ImVec2 fps_pos = framing_pos - ImVec2(word_spacing + fps_text_size.x, 0);
        draw_list->AddText(fps_pos, col_white, fps.c_str());

        ImVec2 res_pos = fps_pos - ImVec2(word_spacing + res_text_size.x, 0);
        draw_list->AddText(res_pos, col_white, res.c_str());
    }
    
    ImGui::PopID();
    ImGui::Dummy(rect_size);
    bool is_select = state->current_camera_item == c.ip && state->current_camera_server == c.server;
    if(ImGui::IsItemHovered()){
        std::string displayText = "";
        displayText += "name: ";
        displayText += state->current_camera_name;
        displayText += "\n";

        displayText += "server: ";
        displayText += c.server;
        displayText += "\n";

        displayText += "ip: ";
        displayText += c.ip;
        displayText += "\n";

        displayText += "serial: ";
        if(c.hw.is_object() && c.hw["serial_number"].is_string()){
            displayText += c.hw["serial_number"].get<std::string>();
        }
        displayText += "\n";

        displayText += "model: ";
        if(c.hw.is_object() && c.hw["model_name"].is_string()){
            displayText += c.hw["model_name"].get<std::string>();
        }
        displayText += "\n";

        displayText += "firmware: ";
        if(c.hw.is_object() && c.hw["firmware_version"].is_string()){
            displayText += c.hw["firmware_version"].get<std::string>();
        }
        displayText += "\n";
        ImGui::SetItemTooltip("%s", displayText.c_str());
        draw_list->AddRect(image_pos, image_pos_max, col_grey, 2.0F, 0, 5.0F);
    }
    else if(is_select){
        draw_list->AddRect(image_pos, image_pos_max, col_grey_light, 2.0F, 0, 5.0F);
    }
    item_event( c);
    ImGui::EndGroup();
}
