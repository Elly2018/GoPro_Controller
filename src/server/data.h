/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
 */
#pragma once
#ifndef DATA_H
#define DATA_H
#include "hv/WebSocketServer.h"
#include <cinttypes>
#include <string>
#include <mutex>
#include "../common/thread_safe_queue.h"
#include "gopro_controller.h"

struct Sender_struct
{
    static constexpr uint64_t ip_str_length = 24UL;
    bool vaild;
    char host_ip[ip_str_length];
    char websocket_ip[ip_str_length];
    int32_t sock_fd;
    struct sockaddr_in bcsa;
};

struct InboundEvent {
    WebSocketChannelPtr channel;
    std::string payload;
};

struct AppData
{
    gopro_controller controller;
    bool should_quit;
    std::mutex download_mtx;
    std::mutex broadcast_mtx;
    thread_safe_queue<InboundEvent> message_queue;
    std::array<Sender_struct, 10> broadcast_addrs = std::array<Sender_struct, 10>();
};

constexpr int32_t listen_port = 8556;
constexpr int32_t broadcast_port = 8554;

#endif