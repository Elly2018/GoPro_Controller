/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../inspector.h"
#include <exception>

void InspectorWindow::draw_system(){
    _draw_setting(system_list_ordered);
}

void InspectorWindow::draw_setting(){
    if (state->current_status_items[std::to_string(PRESET_ID)].is_number()) {
        int32_t preset = state->current_status_items[std::to_string(PRESET_ID)].get<int32_t>();
        if(preset == 65536){
            _draw_setting(photo_setting_list_ordered);
        }
        else if (preset == 65538){
            _draw_setting(burst_setting_list_ordered);
        }
        else {
            _draw_setting(video_setting_list_ordered);
        }
    }
}

void InspectorWindow::draw_protune(){
    if (state->current_status_items[std::to_string(PRESET_ID)].is_number()) {
        int32_t preset = state->current_status_items[std::to_string(PRESET_ID)].get<int32_t>();
        if(preset == 65536){
            _draw_setting(photo_protune_list_ordered);
        }
        else if (preset == 65538){
            _draw_setting(burst_protune_list_ordered);
        }
        else {
            _draw_setting(video_protune_list_ordered);
        }
    }
}

void InspectorWindow::global_draw_setting(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c){
    json status = json::object();
    master->getStatusFromCamera(c, status);
    if (status[std::to_string(PRESET_ID)].is_number()) {
        int32_t preset = status[std::to_string(PRESET_ID)].get<int32_t>();
        if(preset == 0){
            _global_draw_setting(state, master, c, video_setting_list_ordered);
        }else{
            _global_draw_setting(state, master, c, photo_setting_list_ordered);       
        }
    }
}

void InspectorWindow::global_draw_protune(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c){
    json status = json::object();
    master->getStatusFromCamera(c, status);
    if (status[std::to_string(PRESET_ID)].is_number()) {
        int32_t preset = status[std::to_string(PRESET_ID)].get<int32_t>();
        if(preset == 0){
            _global_draw_setting(state, master, c, video_protune_list_ordered);
        }else{
            _global_draw_setting(state, master, c, photo_protune_list_ordered);       
        }
    }
}

void InspectorWindow::_draw_setting(std::vector<int32_t>& ordered){
    int32_t current = master->findCamera(state->current_camera_server, state->current_camera_item);
    if(current < 0) return;
    const CameraInfo c = master->getCamera_Clone(current);
    int32_t move_from = -1, move_to = -1;
    for(int32_t i = 0; i < ordered.size(); i++){
        int32_t id = ordered[i];
        std::string name = GET_SETTING_NAME_BY_ID(id);
        bool pass = _global_draw_setting_item(i, state, master, c, ordered);
        if(!pass) continue;

        ImGuiDragDropFlags src_flags = 0;
        src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;
        src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
        //src_flags |= ImGuiDragDropFlags_SourceNoPreviewTooltip;
        if(ImGui::BeginDragDropSource(src_flags)){
            if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
                ImGui::Text("Moving \"%s\"", name.c_str());
            ImGui::SetDragDropPayload("INSPECTOR_SETTING", &i, sizeof(int));
            ImGui::EndDragDropSource();
        }

        if(ImGui::BeginDragDropTarget()){
            ImGuiDragDropFlags target_flags = 0;
            target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
            target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("INSPECTOR_SETTING", target_flags))
            {
                move_from = *(const int*)payload->Data;
                move_to = i;
            }
            ImGui::EndDragDropTarget();
        }
    }
    if (move_from != -1 && move_to != -1)
    {
        const int32_t tmp = ordered[move_from];
        ordered[move_from] = ordered[move_to];
        ordered[move_to] = tmp;
        //ImGui::SetDragDropPayload("INSPECTOR_SETTING", &move_to, sizeof(int));
        state->update_server();
    }
}

void InspectorWindow::_global_draw_setting(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c, std::vector<int32_t>& ordered){
    for(int32_t i = 0; i < ordered.size(); i++){
        _global_draw_setting_item(i, state, master, c, ordered);
    }
}

bool InspectorWindow::_global_draw_setting_item(int32_t i, std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c, std::vector<int32_t>& ordered){
    int32_t id = ordered[i];
    std::string name = GET_SETTING_NAME_BY_ID(id);
    size_t size = GET_SETTING_SIZE_BY_ID(id);
    int32_t ava = GET_SETTING_AVA_BY_ID(id);
    int32_t model_enum = _get_current_model(c.hw);

    json setting = json::object();
    json status = json::object();
    master->getSettingsFromCamera(c, setting);
    master->getStatusFromCamera(c, status);

    if((model_enum&ava) == 0){
        return false;
    }
    if (!setting[std::to_string(id)].is_number()) {
        return false;
    }
    if (name.size() == 0) {
        return false;
    }
    if(!conditional_filter(state, model_enum, id)){
        return false;
    }

    name += "##InspectorTitle";
    int32_t select_index = setting[std::to_string(id)].get<int32_t>();
    const char** select_string_list = GET_SETTING_STRING_BY_ID(id);
    if(select_string_list == nullptr) {
        std::cerr << "Inspector: select_string_list == nullptr" << std::endl;
        return false;
    }
    if(select_index >= size) {
        std::cerr << "Inspector: select_index >= size..." << id << "..." << select_index << "..." << size << std::endl;
        return false;
    }
    const char* select_string = select_string_list[select_index];
    if(select_string == nullptr) return false;

    const int32_t* values_id = GET_SETTING_VALUE_BY_ID(id);
    const int32_t* support_id = GET_SETTING_SUPPORT_BY_ID(id);

    if(ImGui::BeginCombo(name.c_str(), select_string)){
        for (int n = 0; n < size; n++)
        {
            int32_t supp = support_id[n];
            if((model_enum&supp) == 0){
                continue;
            }
            if(!conditional_filter_option(state, model_enum, id, n)){
                continue;
            }
            std::string option = GET_SETTING_STRING_BY_ID(id)[n];
            if(option.size() == 0) continue;
            bool is_selected = (setting[std::to_string(id)] == n); // You can store your selection however you want, outside or inside your objects
            option += ("##InspectorOption_" + name); 
            if (ImGui::Selectable(option.c_str(), is_selected))
            {
                setting[std::to_string(id)] = n; // Change index
                master->apply("", c.ip, id, values_id[n]);
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }
    return true;
}
