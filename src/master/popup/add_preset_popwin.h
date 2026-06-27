/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_ADD_PRESET_POPUP_H
#define POPUP_ADD_PRESET_POPUP_H
#include "base_pop_window.h"

struct Add_preset_popup {

};

class AddPresetPopup : public BasePopWindow {
public:
    AddPresetPopup(
        std::shared_ptr<json> _setting, 
        std::shared_ptr<GlobalState> _state, 
        std::shared_ptr<GoProMaster> _master);
    ~AddPresetPopup();

    virtual void trigger(bool value) override;
    virtual void render() override;
    void save_preset();
private:
    std::string preset_name;
};

#endif