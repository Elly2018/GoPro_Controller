/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "add_preset_popwin.h"
#include "src/imgui_notify.h"
#include "../windows/inspector.h"
#include "../../common/camera_code.h"

void add_preset_popup_render(Add_preset_popup& win) {
    if(ImGui::BeginPopupModal(title.c_str(), NULL, wp_flag)){
        bool updated = ImGui::InputText("Preset Name", &preset_name);
        if(ImGui::IsItemHovered()){
            ImGui::SetItemTooltip("Enter preset name");
        }
        if (ImGui::Button("Confirm")) {
            save_preset();
        }
        ImGui::SameLine();
        if(ImGui::Button("Cancel")){
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void add_preset_popup_savepreset(Add_preset_popup& win) {
    json status = json::object();
    json setting = json::object();
    json data = json::object();
    int32_t t = master->findCamera(state->current_camera_server, state->current_camera_item);
    if(t < 0) return;
    std::lock_guard lock(master->camera_mtx);
    const std::shared_ptr<CameraInfo>& c = master->getCameras().at(t);
    if(preset_name.size() == 0){
        ImGuiToast toast(ImGuiToastType_Error, 3000);
        toast.set_title("Preset Save Failed");
        toast.set_content("You need to enter preset name");
        ImGui::InsertNotification(toast);
        return;
    }
    if(!master->getSettingsFromCamera(*c, setting)) return;
    if(!master->getStatusFromCamera(*c, status)) return;
    int32_t preset_id = status[std::to_string(PRESET_ID)].get<int32_t>();
    data["name"] = preset_name;
    data["model"] = InspectorWindow::_get_current_model(c->hw);
    data["preset"] = preset_id;
    data["setting"] = setting;
    int32_t result = master->add_preset(preset_name, data);
    if(result == 0){
        ImGuiToast toast(ImGuiToastType_Success, 3000);
        toast.set_title("Preset Save Success");
        toast.set_content("Preset name: %s", preset_name.c_str());
        ImGui::InsertNotification(toast);
        state->update_preset();
        trigger(false);
    }else if(result == 2){
        ImGuiToast toast(ImGuiToastType_Error, 3000);
        toast.set_title("Preset Save Failed");
        toast.set_content("Name already used: %s", preset_name.c_str());
        ImGui::InsertNotification(toast);
    }
}