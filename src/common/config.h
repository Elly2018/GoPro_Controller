#pragma once
#ifndef GPC_CONFIG_H
#define GPC_CONFIG_H

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

#endif