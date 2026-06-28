/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef GCG_CONFIG_H
#define GCG_CONFIG_H

/**
 * @brief When server received master, print out what header it got
 */
static constexpr bool SERVER_QUERY_LOG = true;
/**
 * @brief Print the progress bar in console when server is download the media from GoPro
 */
static constexpr bool SERVER_MEDIA_DOWNLOAD_LOG = true;
/**
 * @brief The progress bar wait period time (second)
 */
static constexpr float SERVER_MEDIA_DOWNLOAD_PERIOD = 1.0f;

static constexpr const char* SERVER_CLIENT_RECORD_FILENAME = "record.txt";

#endif