/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "preset_manager_popwin.h"
#include <cstddef>
#include "imgui.h"
#include "src/imgui_notify.h"

static void PresetManagerPopup::draw_preset_list(){
    ImGui::Text("%s", "Presets: ");
    ImGui::Separator();
    for(std::string& n : master->get_preset_names()){
        if(ImGui::Selectable((n + "##Preset_Manager_Item").c_str(), n == preset_select)){
            if(n == preset_select){
                preset_select = "";
            }else{
                preset_select = n;
            }
        }
    }
}

static void PresetManagerPopup::draw_preset_detail(){
    ImGui::Text("%s", "Detail: ");
    ImGui::Separator();
    if(preset_select.size() == 0) return;
    json data;
    if(!master->get_preset(preset_select, data)) return;
    if(data["name"].is_string()){
        ImGui::LabelText("Name", "%s", data["name"].get<std::string>().c_str());
    }
    if(data["model"].is_number_integer()){
        ImGui::LabelText("Model", "%i", data["model"].get<int32_t>());
    }
    if(data["preset"].is_number_integer()){
        ImGui::LabelText("Preset", "%i", data["preset"].get<int32_t>());
    }
    ImGui::Separator();
    ImGui::Indent(5.0F);
    if(data["setting"].is_object()){
        for(auto item = data["setting"].begin(); item != data["setting"].end(); item++){
            int32_t id = std::atoi(item.key().c_str());
            if(!item->is_number()) continue;
            int32_t value = item->get<int32_t>();
            std::string name = GET_SETTING_NAME_BY_ID(id);
            size_t size = GET_SETTING_SIZE_BY_ID(id);
            if(value >= size) continue;
            std::string display = GET_SETTING_STRING_BY_ID(id)[value];
            ImGui::LabelText(name.c_str(), "%s", display.c_str());
        }
    }
    ImGui::Indent(-5.0F);
}

void preset_manager_popup_render(Preset_manager_popup& win) {
    
    if(win.base.base.enable != win.base.base.enable_last) {
        win.preset_select = "";
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 display_size = io.DisplaySize;
    ImVec2 unit = ImVec2(display_size.x / 12.0f, display_size.y / 12.0f);
    float unit_width;
    float unit_height;

    ImGui::SetNextWindowPos(ImVec2(unit.x * 0.5F, unit.y * 0.5F), wp_cond);
    ImGui::SetNextWindowSize(ImVec2(unit.x * 11.0F, unit.y * 11.0F), wp_cond);
    
    unit_width = (unit.x * 11.0F) / 2.0F - style.ItemSpacing.x;
    unit_height = unit.y * 9.5F;

    if(ImGui::BeginPopupModal(title.c_str(), NULL, wp_flag)){
        ImGui::SameLine();
        {
            ImGui::BeginChild("Preset List##Preset_Manager", ImVec2(unit_width - 50.0F, unit_height));
            draw_preset_list();
            ImGui::EndChild();
        }
        ImGui::SameLine();
        {
            ImGui::BeginChild("Preset Detail##Preset_Manager", ImVec2(unit_width + 50.0F, unit_height));
            draw_preset_detail();
            ImGui::EndChild();
        }

        bool can_apply = preset_select.size() > 0;
        ImGui::BeginDisabled(!can_apply || state->applying_all);
        if(ImGui::Button("Apply")){
            json data = json::object();
            if(master->get_preset(preset_select, data)){
                master->applyAll("", data);
                state->applying_all = true;
            }
        }
        ImGui::EndDisabled();

        ImGui::SameLine();

        ImGui::BeginDisabled(preset_select.size() == 0 || state->applying_all);
        if(ImGui::Button("Delete##Preset_Manager_Item_Action")){
            master->remove_preset(preset_select);
            state->update_preset();
            preset_select = "";
        }
        ImGui::EndDisabled();

        ImGui::SameLine();

        ImGui::BeginDisabled(state->applying_all);
        if(ImGui::Button("Cancel")){
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndDisabled();

        ImGui::EndPopup();
    }
}

