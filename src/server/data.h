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
#include "hv/EventLoop.h"
#include "hv/UdpServer.h"
#include "hv/UdpClient.h"
#include "hv/hsocket.h"
#include <cinttypes>
#include <string>
#include <mutex>
#include "../common/thread_safe_queue.h"
#include "gopro_controller.h"

struct Sender_struct
{
    static constexpr uint64_t ip_str_length = 24UL;
    char host_ip[ip_str_length];
    char websocket_ip[ip_str_length];
    int32_t sock_fd;
    struct sockaddr_in bcsa;
    bool vaild;
};

struct InboundEvent {
    WebSocketChannelPtr channel;
    std::string payload;
};

struct AppData
{
    gopro_controller controller;

    hv::WebSocketServer server;
    hv::HttpServer http_server;
    hv::UdpServer us;

    std::mutex download_mtx;
    std::mutex broadcast_mtx;

    thread_safe_queue<InboundEvent> message_queue;
    std::array<Sender_struct, 10> broadcast_addrs = std::array<Sender_struct, 10>();

    bool should_quit;
};

constexpr int32_t listen_port = 8556;
constexpr int32_t broadcast_port = 8554;

#endif