/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef GCG_CAMERA_OTHER
#define GCG_CAMERA_OTHER
#include <cinttypes>
#include <string>

#pragma region GoPro Mode
constexpr int32_t GOPRO_MODE_SIZE = 9;
constexpr std::string GOPRO_MODE_NAME = "Webcam Mode";
const static char* GOPRO_MODE_STRING[] = {
    "Video",
    "Photo Burst",
    "Photo Single",
    "Timelapse",
    "Timelapse Trail",
    "Timelapse Light Painting",
    "Timelapse Light Trail",
    "Timelapse Video",
    "Timelapse Night Video",
};
const static int32_t GOPRO_MODE_VALUE[] = {
    0, // Video
    65538, // Photo Burst
    65536, // Photo Single
    131072, // Timelapse
    131075, // Timelapse Trail
    131076, // Timelapse Light Painting
    131077, // Timelapse Light Trail
    131073, // Timelapse Video
    131074, // Timelapse Night Video
};
#pragma endregion

#pragma region Media Download Type
constexpr int32_t MEDIA_DOWNLOAD_TYPE_SIZE = 3;
constexpr std::string MEDIA_DOWNLOAD_TYPE_NAME = "Media Download Type";
const static char* MEDIA_DOWNLOAD_TYPE_STRING[] = {
    "All",
    "Front Chars",
    "Back Chars"
};
const static int32_t MEDIA_DOWNLOAD_TYPE_VALUE[] = {
    0, 1, 2
};
#pragma endregion

constexpr int32_t WEBCAM_START_RES_SIZE = 3;
constexpr std::string WEBCAM_START_RES_NAME = "Webcam Resolution";

const static char* WEBCAM_START_RES_STRING[] = {
    "480p",
    "720p",
    "1080p"
};

const static int32_t WEBCAM_START_RES_VALUE[] = {
    4, 7, 12
};

constexpr int32_t WEBCAM_START_FOV_SIZE = 4;
constexpr std::string WEBCAM_START_FOV_NAME = "Webcam Field-of-View";

const static char* WEBCAM_START_FOV_STRING[] = {
    "Wide",
    "Narrow",
    "Superview",
    "Linear"
};

const static int32_t WEBCAM_START_FOV_VALUE[] = {
    0, 2, 3, 4
};

enum class ExecutionType {
    Set, SetAll
};

#endif