/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../inspector.h"


void InspectorWindow::draw_status(){
    _draw_status(status_software_list_ordered);
}

void InspectorWindow::draw_hardware(){
    _draw_status(status_hardware_list_ordered);
}

void InspectorWindow::draw_network(){
    _draw_status(status_network_list_ordered);
}

void InspectorWindow::draw_encode(){
    _draw_status(status_encode_list_ordered);
}

void InspectorWindow::draw_media_status(){
    _draw_status(status_media_list_ordered);
}

void InspectorWindow::_draw_status(std::vector<int32_t>& ordered){
    int move_from = -1, move_to = -1;
    int32_t model_enum = _get_current_model(state->current_hw_items);
    for(int32_t i = 0; i < ordered.size(); i++){
        float x = ImGui::GetCursorPosX();
        int32_t id = ordered.at(i);
        const int32_t type = GET_STATUS_TYPE_BY_ID(id);
        std::string name = GET_STATUS_NAME_BY_ID(id);
        int32_t ava = GET_STATUS_AVA_BY_ID(id);

        if((model_enum&ava) == 0){
            continue;
        }

        if (name.size() == 0) continue;

        name += "##InspectorTitle_status";
        std::string pp = "##InspectorTitle_status_option_" + std::string(GET_STATUS_NAME_BY_ID(id));

        if(type == (int32_t)CAMERA_STATUS_TYPE::OPTION){
            size_t size = GET_STATUS_SIZE_BY_ID(id);
            if (!state->current_status_items[std::to_string(id)].is_number()) continue;
            int32_t select_index = state->current_status_items[std::to_string(id)].get<int32_t>();
            const char** select_string_list = GET_STATUS_STRING_BY_ID(id);
            std::string select_value_display = select_string_list[select_index];
            pp = std::to_string(select_index) + " " + select_value_display + pp;
        }else if (type == (int32_t)CAMERA_STATUS_TYPE::BOOLEAN){
            if (!state->current_status_items[std::to_string(id)].is_number()) continue;
            int32_t value = state->current_status_items[std::to_string(id)].get<int32_t>();
            std::string display = "";
            if(value == 1) display = "true";
            else display = "false";
            pp = display + pp;
        }else if (type == (int32_t)CAMERA_STATUS_TYPE::INT){
            if (!state->current_status_items[std::to_string(id)].is_number()) continue;
            int32_t value = state->current_status_items[std::to_string(id)].get<int32_t>();
            pp = std::to_string(value) + pp;
        }else if (type == (int32_t)CAMERA_STATUS_TYPE::LONG){
            if (!state->current_status_items[std::to_string(id)].is_number()) continue;
            int64_t value = state->current_status_items[std::to_string(id)].get<int64_t>();
            pp = std::to_string(value) + pp;
        }else if (type == (int32_t)CAMERA_STATUS_TYPE::STRING){
            if (!state->current_status_items[std::to_string(id)].is_string()) continue;
            std::string value = state->current_status_items[std::to_string(id)].get<std::string>();
            pp = value + pp;
        }else {
            std::cout << "Type is unknown: " << type << std::endl;
            continue;   
        }

        ImGui::Selectable(pp.c_str(), false, ImGuiSelectableFlags_SpanAllColumns);

        ImGuiDragDropFlags src_flags = 0;
        src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;
        src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
        if(ImGui::BeginDragDropSource(src_flags)){
            if (!(src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
                ImGui::Text("Moving \"%s\"", name.c_str());
            ImGui::SetDragDropPayload("INSPECTOR_STATUS", &i, sizeof(int));
            ImGui::EndDragDropSource();
        }

        if(ImGui::BeginDragDropTarget()){
            ImGuiDragDropFlags target_flags = 0;
            target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
            target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("INSPECTOR_STATUS", target_flags))
            {
                move_from = *(const int*)payload->Data;
                move_to = i;
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::SameLine();
        ImGui::SetCursorPosX(x + ImGui::CalcItemWidth() + ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::TextUnformatted(GET_STATUS_NAME_BY_ID(id));
    }
    if (move_from != -1 && move_to != -1)
    {
        const int32_t tmp = ordered[move_from];
        ordered[move_from] = ordered[move_to];
        ordered[move_to] = tmp;
        state->update_server();
    }
}

