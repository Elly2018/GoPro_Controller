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

void Execute_command(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void Query_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void Webcam_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void Mode_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void Media_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;
void Preview_action(gopro_controller& controller, const WebSocketChannelPtr &channel, json j) noexcept;

#endif