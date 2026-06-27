#include "style_setting.h"
#include <string_view>
#include "../imgui_helper.h"
#include "../data/state.h"

static void store_vec4(json& j, ImVec4& value);
static void store_vec2(json& j, ImVec2& value);
static void fetch_vec4(json& j, ImVec4& value);
static void fetch_vec2(json& j, ImVec2& value);

static void GET_DATA_COLOR4(json& jdata, const ImVec4* colors, int32_t idx, std::string_view name) {
    jdata["colors"][name] = json::object();
    store_vec4(jdata["colors"][name], colors[idx]);
}

static void GET_DATA_FLOAT(json& x, float value, std::string_view name) {
    x["fields"][name] = value;
}

static void GET_DATA_FLOAT2(json& x, const ImVec2& value, std::string_view name) {
    x["fields"][name] = json::object();
    store_vec2(x["fields"][name], value);
}

static void SET_DATA_COLOR4(const json& x, ImVec4* colors, int idx, std::string_view name) {
    fetch_vec4(x["colors"][name], colors[idx]);
}

static void SET_DATA_FLOAT(const json& x, float& target, std::string_view name) {
    target = x["fields"][name].get<float>();
}

static void SET_DATA_FLOAT2(const json& x, ImVec2& target, std::string_view name) {
    fetch_vec2(x["fields"][name], target);
}

static void store_vec4(json& j, const ImVec4& value){
    j["x"] = value.x;
    j["y"] = value.y;
    j["z"] = value.z;
    j["w"] = value.w;
}
static void store_vec2(json& j, const ImVec2& value){
    j["x"] = value.x;
    j["y"] = value.y;
}
static void fetch_vec4(json& j, const ImVec4& value){
    value.x = j["x"];
    value.y = j["y"];
    value.z = j["z"];
    value.w = j["w"];
}
static void fetch_vec2(json& j, const ImVec2& value){
    value.x = j["x"];
    value.y = j["y"];
}


void style_window_render(Style_window& win) {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    bool changed = false;

    ImGui::Begin(title.c_str(), &enable, w_flag);
    {
        if(ImGui::BeginCombo("Theme##style_themes", "")){
            if(ImGui::Selectable("Dark Theme")){
                ImGui::StyleColorsDark();
                changed = true;
            }
            if(ImGui::Selectable("Light Theme")){
                ImGui::StyleColorsLight();
                changed = true;
            }
            if(ImGui::Selectable("Mocha Theme")){
                setup_catppuccin_mocha_theme();
                changed = true;
            }
            ImGui::EndCombo();
        }

        ImGui::Separator();
        
        if(ImGui::BeginTabBar("Style Fields##style_win")){
            if(ImGui::BeginTabItem("Colors##style_win")){
                changed = changed | style_window_render_colors(win);
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Fields##style_win")){
                changed = style_window_render_fields(win);
                ImGui::EndTabItem();
            }
            if(changed){
                style_window_update_style(win);
                changed = false;
            }
            ImGui::EndTabBar();
        }
    }
    ImGui::End();
}

json style_window_get_window_data(Style_window& win) {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    json buffer = json::object();

    buffer["colors"] = json::object();
    buffer["fields"] = json::object();
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_WindowBg, "ImGuiCol_WindowBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ChildBg, "ImGuiCol_ChildBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_PopupBg, "ImGuiCol_PopupBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_Border, "ImGuiCol_Border");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_BorderShadow, "ImGuiCol_BorderShadow");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_FrameBg, "ImGuiCol_FrameBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_FrameBgHovered, "ImGuiCol_FrameBgHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_FrameBgActive, "ImGuiCol_FrameBgActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TitleBg, "ImGuiCol_TitleBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TitleBgActive, "ImGuiCol_TitleBgActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TitleBgCollapsed, "ImGuiCol_TitleBgCollapsed");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_MenuBarBg, "ImGuiCol_MenuBarBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ScrollbarBg, "ImGuiCol_ScrollbarBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ScrollbarGrab, "ImGuiCol_ScrollbarGrab");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ScrollbarGrabHovered, "ImGuiCol_ScrollbarGrabHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ScrollbarGrabActive, "ImGuiCol_ScrollbarGrabActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_CheckMark, "ImGuiCol_CheckMark");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_SliderGrab, "ImGuiCol_SliderGrab");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_SliderGrabActive, "ImGuiCol_SliderGrabActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_Button, "ImGuiCol_Button");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ButtonHovered, "ImGuiCol_ButtonHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ButtonActive, "ImGuiCol_ButtonActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_Header, "ImGuiCol_Header");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_HeaderHovered, "ImGuiCol_HeaderHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_HeaderActive, "ImGuiCol_HeaderActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_Separator, "ImGuiCol_Separator");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_SeparatorHovered, "ImGuiCol_SeparatorHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_SeparatorActive, "ImGuiCol_SeparatorActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ResizeGrip, "ImGuiCol_ResizeGrip");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ResizeGripHovered, "ImGuiCol_ResizeGripHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ResizeGripActive, "ImGuiCol_ResizeGripActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_Tab, "ImGuiCol_Tab");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TabHovered, "ImGuiCol_TabHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TabActive, "ImGuiCol_TabActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TabUnfocused, "ImGuiCol_TabUnfocused");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TabUnfocusedActive, "ImGuiCol_TabUnfocusedActive");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_DockingPreview, "ImGuiCol_DockingPreview");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_DockingEmptyBg, "ImGuiCol_DockingEmptyBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_PlotLines, "ImGuiCol_PlotLines");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_PlotLinesHovered, "ImGuiCol_PlotLinesHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_PlotHistogram, "ImGuiCol_PlotHistogram");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_PlotHistogramHovered, "ImGuiCol_PlotHistogramHovered");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TableHeaderBg, "ImGuiCol_TableHeaderBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TableBorderStrong, "ImGuiCol_TableBorderStrong");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TableBorderLight, "ImGuiCol_TableBorderLight");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TableRowBg, "ImGuiCol_TableRowBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TableRowBgAlt, "ImGuiCol_TableRowBgAlt");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TextSelectedBg, "ImGuiCol_TextSelectedBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_DragDropTarget, "ImGuiCol_DragDropTarget");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_NavHighlight, "ImGuiCol_NavHighlight");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_NavWindowingHighlight, "ImGuiCol_NavWindowingHighlight");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_NavWindowingDimBg, "ImGuiCol_NavWindowingDimBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_ModalWindowDimBg, "ImGuiCol_ModalWindowDimBg");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_Text, "ImGuiCol_Text");
    GET_DATA_COLOR4(buffer, colors, ImGuiCol_TextDisabled, "ImGuiCol_TextDisabled");
    
    GET_DATA_FLOAT(buffer, style, FontScaleMain);

    GET_DATA_FLOAT(buffer, style, WindowRounding);
    GET_DATA_FLOAT(buffer, style, ChildRounding);
    GET_DATA_FLOAT(buffer, style, FrameRounding);
    GET_DATA_FLOAT(buffer, style, PopupRounding);
    GET_DATA_FLOAT(buffer, style, ScrollbarRounding);
    GET_DATA_FLOAT(buffer, style, GrabRounding);
    GET_DATA_FLOAT(buffer, style, TabRounding);

    GET_DATA_FLOAT2(buffer, style, WindowPadding);
    GET_DATA_FLOAT2(buffer, style, FramePadding);
    GET_DATA_FLOAT2(buffer, style, ItemSpacing);
    GET_DATA_FLOAT2(buffer, style, ItemInnerSpacing);
    GET_DATA_FLOAT(buffer, style, IndentSpacing);
    GET_DATA_FLOAT(buffer, style, ScrollbarSize);
    GET_DATA_FLOAT(buffer, style, GrabMinSize);

    GET_DATA_FLOAT(buffer, style, WindowBorderSize);
    GET_DATA_FLOAT(buffer, style, ChildBorderSize);
    GET_DATA_FLOAT(buffer, style, PopupBorderSize);
    GET_DATA_FLOAT(buffer, style, FrameBorderSize);
    GET_DATA_FLOAT(buffer, style, TabBorderSize);
    GET_DATA_FLOAT(buffer, style, TabRounding);

    return buffer;
}

void style_window_set_window_data(Style_window& win, const json& data) {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    SET_DATA_COLOR4(data, colors, ImGuiCol_WindowBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ChildBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_PopupBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_Border);
    SET_DATA_COLOR4(data, colors, ImGuiCol_BorderShadow);
    SET_DATA_COLOR4(data, colors, ImGuiCol_FrameBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_FrameBgHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_FrameBgActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TitleBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TitleBgActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TitleBgCollapsed);
    SET_DATA_COLOR4(data, colors, ImGuiCol_MenuBarBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ScrollbarBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ScrollbarGrab);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ScrollbarGrabHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ScrollbarGrabActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_CheckMark);
    SET_DATA_COLOR4(data, colors, ImGuiCol_SliderGrab);
    SET_DATA_COLOR4(data, colors, ImGuiCol_SliderGrabActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_Button);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ButtonHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ButtonActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_Header);
    SET_DATA_COLOR4(data, colors, ImGuiCol_HeaderHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_HeaderActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_Separator);
    SET_DATA_COLOR4(data, colors, ImGuiCol_SeparatorHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_SeparatorActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ResizeGrip);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ResizeGripHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ResizeGripActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_Tab);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TabHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TabActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TabUnfocused);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TabUnfocusedActive);
    SET_DATA_COLOR4(data, colors, ImGuiCol_DockingPreview);
    SET_DATA_COLOR4(data, colors, ImGuiCol_DockingEmptyBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_PlotLines);
    SET_DATA_COLOR4(data, colors, ImGuiCol_PlotLinesHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_PlotHistogram);
    SET_DATA_COLOR4(data, colors, ImGuiCol_PlotHistogramHovered);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TableHeaderBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TableBorderStrong);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TableBorderLight);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TableRowBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TableRowBgAlt);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TextSelectedBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_DragDropTarget);
    SET_DATA_COLOR4(data, colors, ImGuiCol_NavHighlight);
    SET_DATA_COLOR4(data, colors, ImGuiCol_NavWindowingHighlight);
    SET_DATA_COLOR4(data, colors, ImGuiCol_NavWindowingDimBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_ModalWindowDimBg);
    SET_DATA_COLOR4(data, colors, ImGuiCol_Text);
    SET_DATA_COLOR4(data, colors, ImGuiCol_TextDisabled);

    SET_DATA_FLOAT(data, style, FontScaleMain);

    SET_DATA_FLOAT(data, style, WindowRounding);
    SET_DATA_FLOAT(data, style, ChildRounding);
    SET_DATA_FLOAT(data, style, FrameRounding);
    SET_DATA_FLOAT(data, style, PopupRounding);
    SET_DATA_FLOAT(data, style, ScrollbarRounding);
    SET_DATA_FLOAT(data, style, GrabRounding);
    SET_DATA_FLOAT(data, style, TabRounding);

    SET_DATA_FLOAT2(data, style, WindowPadding);
    SET_DATA_FLOAT2(data, style, FramePadding);
    SET_DATA_FLOAT2(data, style, ItemSpacing);
    SET_DATA_FLOAT2(data, style, ItemInnerSpacing);
    SET_DATA_FLOAT(data, style, IndentSpacing);
    SET_DATA_FLOAT(data, style, ScrollbarSize);
    SET_DATA_FLOAT(data, style, GrabMinSize);

    SET_DATA_FLOAT(data, style, WindowBorderSize);
    SET_DATA_FLOAT(data, style, ChildBorderSize);
    SET_DATA_FLOAT(data, style, PopupBorderSize);
    SET_DATA_FLOAT(data, style, FrameBorderSize);
    SET_DATA_FLOAT(data, style, TabBorderSize);
    SET_DATA_FLOAT(data, style, TabRounding);
}

bool style_window_render_colors(Style_window& win) {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    bool changed = false;
    changed = changed | ImGui::ColorEdit4("ImGuiCol_WindowBg##style_color_edit", (float*)&colors[ImGuiCol_WindowBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ChildBg##style_color_edit", (float*)&colors[ImGuiCol_ChildBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_PopupBg##style_color_edit", (float*)&colors[ImGuiCol_PopupBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_Border##style_color_edit", (float*)&colors[ImGuiCol_Border]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_BorderShadow##style_color_edit", (float*)&colors[ImGuiCol_BorderShadow]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_FrameBg##style_color_edit", (float*)&colors[ImGuiCol_FrameBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_FrameBgHovered##style_color_edit", (float*)&colors[ImGuiCol_FrameBgHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_FrameBgActive##style_color_edit", (float*)&colors[ImGuiCol_FrameBgActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TitleBg##style_color_edit", (float*)&colors[ImGuiCol_TitleBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TitleBgActive##style_color_edit", (float*)&colors[ImGuiCol_TitleBgActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TitleBgCollapsed##style_color_edit", (float*)&colors[ImGuiCol_TitleBgCollapsed]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_MenuBarBg##style_color_edit", (float*)&colors[ImGuiCol_MenuBarBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ScrollbarBg##style_color_edit", (float*)&colors[ImGuiCol_ScrollbarBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ScrollbarGrab##style_color_edit", (float*)&colors[ImGuiCol_ScrollbarGrab]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ScrollbarGrabHovered##style_color_edit", (float*)&colors[ImGuiCol_ScrollbarGrabHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ScrollbarGrabActive##style_color_edit", (float*)&colors[ImGuiCol_ScrollbarGrabActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_CheckMark##style_color_edit", (float*)&colors[ImGuiCol_CheckMark]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_SliderGrab##style_color_edit", (float*)&colors[ImGuiCol_SliderGrab]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_SliderGrabActive##style_color_edit", (float*)&colors[ImGuiCol_SliderGrabActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_Button##style_color_edit", (float*)&colors[ImGuiCol_Button]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ButtonHovered##style_color_edit", (float*)&colors[ImGuiCol_ButtonHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ButtonActive##style_color_edit", (float*)&colors[ImGuiCol_ButtonActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_Header##style_color_edit", (float*)&colors[ImGuiCol_Header]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_HeaderHovered##style_color_edit", (float*)&colors[ImGuiCol_HeaderHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_HeaderActive##style_color_edit", (float*)&colors[ImGuiCol_HeaderActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_Separator##style_color_edit", (float*)&colors[ImGuiCol_Separator]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_SeparatorHovered##style_color_edit", (float*)&colors[ImGuiCol_SeparatorHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_SeparatorActive##style_color_edit", (float*)&colors[ImGuiCol_SeparatorActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ResizeGrip##style_color_edit", (float*)&colors[ImGuiCol_ResizeGrip]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ResizeGripHovered##style_color_edit", (float*)&colors[ImGuiCol_ResizeGripHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ResizeGripActive##style_color_edit", (float*)&colors[ImGuiCol_ResizeGripActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_Tab##style_color_edit", (float*)&colors[ImGuiCol_Tab]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TabHovered##style_color_edit", (float*)&colors[ImGuiCol_TabHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TabActive##style_color_edit", (float*)&colors[ImGuiCol_TabActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TabUnfocused##style_color_edit", (float*)&colors[ImGuiCol_TabUnfocused]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TabUnfocusedActive##style_color_edit", (float*)&colors[ImGuiCol_TabUnfocusedActive]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_DockingPreview##style_color_edit", (float*)&colors[ImGuiCol_DockingPreview]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_DockingEmptyBg##style_color_edit", (float*)&colors[ImGuiCol_DockingEmptyBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_PlotLines##style_color_edit", (float*)&colors[ImGuiCol_PlotLines]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_PlotLinesHovered##style_color_edit", (float*)&colors[ImGuiCol_PlotLinesHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_PlotHistogram##style_color_edit", (float*)&colors[ImGuiCol_PlotHistogram]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_PlotHistogramHovered##style_color_edit", (float*)&colors[ImGuiCol_PlotHistogramHovered]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TableHeaderBg##style_color_edit", (float*)&colors[ImGuiCol_TableHeaderBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TableBorderStrong##style_color_edit", (float*)&colors[ImGuiCol_TableBorderStrong]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TableBorderLight##style_color_edit", (float*)&colors[ImGuiCol_TableBorderLight]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TableRowBg##style_color_edit", (float*)&colors[ImGuiCol_TableRowBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TableRowBgAlt##style_color_edit", (float*)&colors[ImGuiCol_TableRowBgAlt]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TextSelectedBg##style_color_edit", (float*)&colors[ImGuiCol_TextSelectedBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_DragDropTarget##style_color_edit", (float*)&colors[ImGuiCol_DragDropTarget]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_NavHighlight##style_color_edit", (float*)&colors[ImGuiCol_NavHighlight]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_NavWindowingHighlight##style_color_edit", (float*)&colors[ImGuiCol_NavWindowingHighlight]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_NavWindowingDimBg##style_color_edit", (float*)&colors[ImGuiCol_NavWindowingDimBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_ModalWindowDimBg##style_color_edit", (float*)&colors[ImGuiCol_ModalWindowDimBg]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_Text##style_color_edit", (float*)&colors[ImGuiCol_Text]);
    changed = changed | ImGui::ColorEdit4("ImGuiCol_TextDisabled##style_color_edit", (float*)&colors[ImGuiCol_TextDisabled]);
    return changed;
}

bool style_window_render_fields(Style_window& win) {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    bool changed = false;

    changed = changed || ImGui::SliderFloat("Font Scale Main##style_field", &style.FontScaleMain, 0.1f, 2.0f, "%.1f");

    ImGui::Separator();

    changed = changed || ImGui::InputFloat("WindowRounding##style_field", &style.WindowRounding);
    changed = changed || ImGui::InputFloat("ChildRounding##style_field", &style.ChildRounding);
    changed = changed || ImGui::InputFloat("FrameRounding##style_field", &style.FrameRounding);
    changed = changed || ImGui::InputFloat("PopupRounding##style_field", &style.PopupRounding);
    changed = changed || ImGui::InputFloat("ScrollbarRounding##style_field", &style.ScrollbarRounding);
    changed = changed || ImGui::InputFloat("GrabRounding##style_field", &style.GrabRounding);
    changed = changed || ImGui::InputFloat("TabRounding##style_field", &style.TabRounding);

    ImGui::Separator();

    changed = changed || ImGui::InputFloat2("WindowPadding##style_field", (float*)&style.WindowPadding);
    changed = changed || ImGui::InputFloat2("FramePadding##style_field", (float*)&style.FramePadding);
    changed = changed || ImGui::InputFloat2("ItemSpacing##style_field", (float*)&style.ItemSpacing);
    changed = changed || ImGui::InputFloat2("ItemInnerSpacing##style_field", (float*)&style.ItemInnerSpacing);
    changed = changed || ImGui::InputFloat("IndentSpacing##style_field", &style.IndentSpacing);
    changed = changed || ImGui::InputFloat("ScrollbarSize##style_field", &style.ScrollbarSize);
    changed = changed || ImGui::InputFloat("GrabMinSize##style_field", &style.GrabMinSize);

    ImGui::Separator();

    changed = changed || ImGui::InputFloat("WindowBorderSize##style_field", &style.WindowBorderSize);
    changed = changed || ImGui::InputFloat("ChildBorderSize##style_field", &style.ChildBorderSize);
    changed = changed || ImGui::InputFloat("PopupBorderSize##style_field", &style.PopupBorderSize);
    changed = changed || ImGui::InputFloat("FrameBorderSize##style_field", &style.FrameBorderSize);
    changed = changed || ImGui::InputFloat("TabBorderSize##style_field", &style.TabBorderSize);
    changed = changed || ImGui::InputFloat("TabRounding##style_field", &style.TabRounding);

    return changed;
}

bool style_window_update_style(Style_window& win){
    win.base.state.update_server(&win.base.state.appdata);
    return true;
}
