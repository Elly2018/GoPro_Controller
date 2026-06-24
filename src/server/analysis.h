/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
 */
#pragma once
#ifndef ANALYSIS_H
#define ANALYSIS_H
#include <nlohmann/json.hpp>
#include "hv/WebSocketServer.h"
#include "data.h"

using json = nlohmann::json;

void execute_command(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void query_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void webcam_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void mode_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void media_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void preview_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;

#endif