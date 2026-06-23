#pragma once
#ifndef CAMERA_SETTING
#define CAMERA_SETTING
#include <cinttypes>
#include <array>
#include "camera_model.h"

// Reference: https://gopro.github.io/OpenGoPro/http#schema/State

#pragma region Resolution
#define VIDEO_RESOLUTION_ID 2
#define VIDEO_RESOLUTION_SIZE 29
#define VIDEO_RESOLUTION_NAME "Video Resolution"
#define VIDEO_RESOLUTION_AVA MODEL_MISSION_ALL
const static char* VIDEO_RESOLUTION_STRING[] = {
    "4K",
    "2.7K",
    "2.7K 4:3",
    "1440",
    "1080",
    "720",
    "4K 4:3",
    "5.6K",
    "5K",
    "5K 4:3",
    "5.3K 8:7",
    "5.3K 4:3",
    "4K 8:7",
    "8K",
    "5.3K 21:9",
    "4K 21:9",
    "4K 1:1",
    "900",
    "4K SPH",
    "8K V2",
    "1440 V2",
    "5.3K",
    "5.3K 8:7 V2",
    "4K 8:7 V2",
    "4K 9:16 V2",
    "1080 9:16 V2",
    "2.7K 4:3 V2",
    "4K 4:3 V2",
    "5.3K 4:3 V2"
};
const static int32_t VIDEO_RESOLUTION_VALUE[] = {
    1, // 4K
    4, // 2.7K
    6, // 2.7K 4:3
    7, // 1440
    9, // 1080
    12, // 720
    18, // 4K 4:3
    21, // 5.6K
    24, // 5K
    25,// 5K 4:3
    26, // 5.3K 8:7
    27, // 5.3K 4:3
    28, // 4K 8:7
    31, // 8K
    35, // 5.3K 21:9
    36, // 4K 21:9
    37, // 4K 1:1
    38, // 900
    39, // 4K SPH
    40, // 8K V2
    44, // 1440 V2
    100,// 5.3K
    107, // 5.3K 8:7 V2
    108, // 4K 8:7 V2
    109, // 4K 9:16 V2
    110, // 1080 9:16 V2
    111, // 2.7K 4:3 V2
    112, // 4K 4:3 V2
    113, // 5.3K 4:3 V
};
const static int32_t VIDEO_RESOLUTION_SUPPORT[] = {
    MODEL_MISSION_ALL, // 4K
    MODEL_13_ALL, // 2.7K
    MODEL_11_ALL, // 2.7K 4:3
    MODEL_9, // 1440
    MODEL_MISSION_ALL, // 1080
    MODEL_13, // 720
    MODEL_12_ALL, // 4K 4:3
    MODEL_MISSION|MODEL_MAX2, // 5.6K
    MODEL_9, // 5K
    MODEL_10, // 5K 4:3
    MODEL_11S, // 5.3K 8:7
    MODEL_11S, // 5.3K 4:3
    MODEL_11S, // 4K 8:7
    MODEL_MISSION|MODEL_MAX2, // 8K
    MODEL_13, // 5.3K 21:9
    MODEL_13, // 4K 21:9
    MODEL_13, // 4K 1:1
    MODEL_13, // 900
    MODEL_MISSION|MODEL_MAX2, // 4K SPH
    MODEL_MISSION, // 8K V2
    MODEL_MISSION, // 1440 V2
    MODEL_13_ALL, // 5.3K
    MODEL_13|MODEL_12, // 5.3K 8:7 V2
    MODEL_13|MODEL_12, // 4K 8:7 V2
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 4K 9:16 V2
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 1080 9:16 V2
    MODEL_13|MODEL_12, // 2.7K 4:3 V2
    MODEL_MISSION|MODEL_13|MODEL_12, // 4K 4:3 V2
    MODEL_13 // 5.3K 4:3 V
};
const static int32_t VIDEO_RESOLUTION_RES[][2] = {
    {3840, 2160},  // 4K
    {2704, 1520},  // 2.7K
    {2704, 2028},  // 2.7K 4:3
    {1920, 1440},  // 1440
    {1920, 1080},  // 1080
    {1280, 720},   // 720
    {3840, 2880},  // 4K 4:3
    {5568, 3128},  // 5.6K
    {5120, 2880},  // 5K
    {5120, 3840}, // 5K 4:3
    {5312, 4648},  // 5.3K 8:7
    {5312, 3984},  // 5.3K 4:3
    {4000, 3500},  // 4K 8:7
    {7680, 4320},  // 8K
    {5312, 2272},  // 5.3K 21:9
    {3840, 1645},  // 4K 21:9
    {3840, 3840},  // 4K 1:1
    {1600, 900},   // 900
    {3840, 1920},  // 4K SPH
    {7680, 4320},  // 8K V2
    {1920, 1440},  // 1440 V2
    {5312, 2988}, // 5.3K
    {5312, 4648},  // 5.3K 8:7 V2
    {4000, 3500},  // 4K 8:7 V2
    {2160, 3840},  // 4K 9:16 V2
    {1080, 1920},  // 1080 9:16 V2
    {2704, 2028},  // 2.7K 4:3 V2
    {3840, 2880}, // 4K 4:3 V2
    {5312, 3984}, // 5.3K 4:3 V
};
#pragma endregion

#pragma region FPS
#define FRAMES_PER_SECOND_ID 3
#define FRAMES_PER_SECOND_SIZE 13
#define FRAMES_PER_SECOND_NAME "Frames Per Second"
#define FRAMES_PER_SECOND_AVA MODEL_MISSION_ALL
const static char* FRAMES_PER_SECOND_STRING[] = {
    "960.0",
    "800.0",
    "480.0",
    "400.0",
    "240.0",
    "120.0",
    "100.0",
    "90.0",
    "60.0",
    "50.0",
    "30.0",
    "25.0",
    "24.0",
    "200.0",
    "400.0",
    "360.0",
    "300.0",
};
const static int32_t FRAMES_PER_SECOND_VALUE[] = {
    19, // 960.0
    20, // 800.0
    18, // 480.0
    15, // 400.0
    0, // 240.0
    1, // 120.0
    2, // 100.0
    3, // 90.0
    5, // 60.0
    6, // 50.0
    8, // 30.0
    9, // 25.0
    10, // 24.0
    13, // 200.0
    15, // 400.0
    16, // 360.0
    17, // 300.0
};
const static int32_t FRAMES_PER_SECOND_SUPPORT[] = {
    MODEL_MISSION, // 960.0
    MODEL_MISSION, // 800.0
    MODEL_MISSION, // 480.0
    MODEL_MISSION, // 400.0
    MODEL_13_ALL, // 240.0
    MODEL_13_ALL, // 120.0
    MODEL_MISSION_ALL, // 100.0
    MODEL_MISSION|MODEL_MAX2, // 90.0
    MODEL_MISSION_ALL, // 60.0
    MODEL_MISSION_ALL, // 50.0
    MODEL_MISSION_ALL, // 30.0
    MODEL_MISSION_ALL, // 25.0
    MODEL_MISSION_ALL, // 24.0
    MODEL_13_ALL, // 200.0
    MODEL_13, // 400.0
    MODEL_13, // 360.0
    MODEL_13, // 300.0
};
#pragma endregion

#pragma region Video Time Lapse
#define VIDEO_TIMELAPSE_RATE_ID 5
#define VIDEO_TIMELAPSE_RATE_SIZE 12
#define VIDEO_TIMELAPSE_RATE_NAME "Video Timelapse Rate"
#define VIDEO_TIMELAPSE_RATE_AVA MODEL_MISSION_ALL
const static char* VIDEO_TIMELAPSE_RATE_STRING[] = {
    "0.5 Sec",
    "1 Sec",
    "2 Sec",
    "5 Sec",
    "10 Sec",
    "30 Sec",
    "60 Sec",
    "2 Min",
    "5 Min",
    "30 Min",
    "60 Min",
    "30 Sec",
};
const static int32_t VIDEO_TIMELAPSE_RATE_VALUE[] = {
    0, // 0.5 Sec
    1, // 1 Sec
    2, // 2 Sec
    3, // 5 Sec
    4, // 10 Sec
    5, // 30 Sec
    6, // 60 Sec
    7, // 2 Min
    8, // 5 Min
    9, // 30 Min
    10, // 60 Min
    11, // 30 Sec
};
const static int32_t VIDEO_TIMELAPSE_RATE_SUPPORT[] = {
    MODEL_MISSION_ALL, // 0.5 Sec
    MODEL_MISSION_ALL, // 1 Sec
    MODEL_MISSION_ALL, // 2 Sec
    MODEL_MISSION_ALL, // 5 Sec
    MODEL_MISSION_ALL, // 10 Sec
    MODEL_MISSION_ALL, // 30 Sec
    MODEL_MISSION_ALL, // 60 Sec
    MODEL_MISSION_ALL, // 2 Min
    MODEL_MISSION_ALL, // 5 Min
    MODEL_MISSION_ALL, // 30 Min
    MODEL_MISSION_ALL, // 60 Min
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 30 Sec
};
#pragma endregion

#pragma region Photo Time Lapse
#define PHOTO_TIMELAPSE_RATE_ID 30
#define PHOTO_TIMELAPSE_RATE_SIZE 12
#define PHOTO_TIMELAPSE_RATE_NAME "Photo Timelapse Rate"
#define PHOTO_TIMELAPSE_RATE_AVA MODEL_MISSION_ALL&(~MODEL_11)
const static char* PHOTO_TIMELAPSE_RATE_STRING[] = {
    "3 Sec",
    "60 Min",
    "30 Min",
    "5 Min",
    "2 Min",
    "60 Sec",
    "30 Sec",
    "10 Sec",
    "5 Sec",
    "2 Sec",
    "1 Sec",
    "0.5 Sec",
};
const static int32_t PHOTO_TIMELAPSE_RATE_VALUE[] = {
    11, // 3 Sec
    100, // 60 Min
    101, // 30 Min
    102, // 5 Min
    103, // 2 Min
    104, // 60 Sec
    105, // 30 Sec
    106, // 10 Sec
    107, // 5 Sec
    108, // 2 Sec
    109, // 1 Sec
    110, // 0.5 Sec
};
const static int32_t PHOTO_TIMELAPSE_RATE_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 3 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 60 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 30 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 5 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 2 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 60 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 30 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 10 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 5 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 2 Sec
    MODEL_13_ALL&(~MODEL_11), // 1 Sec
    MODEL_13_ALL&(~MODEL_11), // 0.5 Sec
};
#pragma endregion

#pragma region Night Lapse Rate
#define NIGHTLAPSE_RATE_ID 32
#define NIGHTLAPSE_RATE_SIZE 12
#define NIGHTLAPSE_RATE_NAME "Nightlapse Rate"
#define NIGHTLAPSE_RATE_AVA MODEL_MISSION_ALL
const static char* NIGHTLAPSE_RATE_STRING[] = {
    "4 Sec",
    "5 Sec",
    "10 Sec",
    "15 Sec",
    "20 Sec",
    "30 Sec",
    "60 Sec",
    "2 Min",
    "5 Min",
    "30 Min",
    "60 Min",
    "Auto",
};
const static int32_t NIGHTLAPSE_RATE_VALUE[] = {
    4, // 4 Sec
    5, // 5 Sec
    10, // 10 Sec
    15, // 15 Sec
    20, // 20 Sec
    30, // 30 Sec
    100, // 60 Sec
    120, // 2 Min
    300, // 5 Min
    1800, // 30 Min
    3600, // 60 Min
    3601, // Auto
};
const static int32_t NIGHTLAPSE_RATE_SUPPORT[] = {
    MODEL_MISSION_ALL, // 4 Sec
    MODEL_MISSION_ALL, // 5 Sec
    MODEL_MISSION_ALL, // 10 Sec
    MODEL_MISSION_ALL, // 15 Sec
    MODEL_MISSION_ALL, // 20 Sec
    MODEL_MISSION_ALL, // 30 Sec
    MODEL_MISSION_ALL, // 60 Sec
    MODEL_MISSION_ALL, // 2 Min
    MODEL_MISSION_ALL, // 5 Min
    MODEL_MISSION_ALL, // 30 Min
    MODEL_MISSION_ALL, // 60 Min
    MODEL_MISSION_ALL, // Auto
};
#pragma endregion

#pragma region Webcam Digital Lenses
#define WEBCAM_DIGITAL_LENSES_ID 43
#define WEBCAM_DIGITAL_LENSES_SIZE 4
#define WEBCAM_DIGITAL_LENSES_NAME "Webcam Digital Lenses"
#define WEBCAM_DIGITAL_LENSES_AVA MODEL_MISSION_ALL
const static char* WEBCAM_DIGITAL_LENSES_STRING[] = {
    "Wide",
    "Narrow",
    "Superview",
    "Linear",
};
const static int32_t WEBCAM_DIGITAL_LENSES_VALUE[] = {
    0, // Wide
    2, // Narrow
    3, // Superview
    4, // Linear
};
const static int32_t WEBCAM_DIGITAL_LENSES_SUPPORT[] = {
    MODEL_MISSION_ALL, // Wide
    MODEL_MISSION_ALL, // Narrow
    MODEL_MISSION_ALL, // Superview
    MODEL_MISSION_ALL, // Linear
};
#pragma endregion

#pragma region Auto Power Down
#define AUTO_POWER_DOWN_ID 59
#define AUTO_POWER_DOWN_SIZE 7
#define AUTO_POWER_DOWN_NAME "Auto Power Down"
#define AUTO_POWER_DOWN_AVA MODEL_MISSION_ALL
const static char* AUTO_POWER_DOWN_STRING[] = {
    "Never",
    "1 Min",
    "5 Min",
    "15 Min",
    "30 Min",
    "8 Sec",
    "30 Sec",
};
const static int32_t AUTO_POWER_DOWN_VALUE[] = {
    MODEL_MISSION_ALL, // Never
    MODEL_MISSION_ALL&(~(MODEL_10|MODEL_9)), // 1 Min
    MODEL_MISSION_ALL, // 5 Min
    6, // 15 Min
    7, // 30 Min
    11, // 8 Sec
    12, // 30 Sec
};
const static int32_t AUTO_POWER_DOWN_SUPPORT[] = {
    0, // Never
    1, // 1 Min
    4, // 5 Min
    6, // 15 Min
    7, // 30 Min
    11, // 8 Sec
    12, // 30 Sec
};
#pragma endregion

#pragma region GPS
#define GPS_ID 83
#define GPS_SIZE 2
#define GPS_NAME "GPS"
#define GPS_AVA MODEL_MISSION_ALL&(~(MODEL_12|MODEL_11))
const static char* GPS_STRING[] = {
    "Off",
    "On"
};
const static int32_t GPS_VALUE[] = {
    0, // Off 
    1, // On
};
const static int32_t GPS_SUPPORT[] = {
    MODEL_MISSION_ALL&(~(MODEL_12|MODEL_11)), // Off
    MODEL_MISSION_ALL&(~(MODEL_12|MODEL_11)), // On
};
#pragma endregion

#pragma region Shot Countdown
#define SHOT_COUNTDOWN_ID 105
#define SHOT_COUNTDOWN_SIZE 3
#define SHOT_COUNTDOWN_NAME "Shut Countdown"
#define SHOT_COUNTDOWN_AVA MODEL_13_ALL
const static char* SHOT_COUNTDOWN_STRING[] = {
    "Off",
    "3 Seconds",
    "10 Seconds",
};
const static int32_t SHOT_COUNTDOWN_VALUE[] = {
    0, // Off
    1, // 3 Seconds
    2, // 10 Second
};
const static int32_t SHOT_COUNTDOWN_SUPPORT[] = {
    MODEL_13_ALL, // Off
    MODEL_13_ALL, // 3 Seconds
    MODEL_13_ALL, // 10 Second
};
#pragma endregion

#pragma region HLS
#define HLG_ID 199
#define HLG_SIZE 2
#define HLG_NAME "HLG"
#define HLG_AVA MODEL_13
const static char* HLG_STRING[] = {
    "Off",
    "On"
};
const static int32_t HLG_VALUE[] = {
    0, // Off 
    1, // On
};
const static int32_t HLG_SUPPORT[] = {
    MODEL_13, // Off
    MODEL_13, // On
};
#pragma endregion


#pragma region LCE Brightness
#define LCD_BRIGHTNESS_ID 88
#define LCD_BRIGHTNESS_SIZE 10
#define LCD_BRIGHTNESS_NAME "LCD Brightness"
#define LCD_BRIGHTNESS_AVA MODEL_MISSION_ALL&(~MODEL_11)
const static char* LCD_BRIGHTNESS_STRING[] = {
    "10%",
    "20%",
    "30%",
    "40%",
    "50%",
    "60%",
    "70%",
    "80%",
    "90%",
    "100%",
};
const static int32_t LCD_BRIGHTNESS_VALUE[] = {
    10, // 10%
    20, // 20%
    30, // 30%
    40, // 40%
    50, // 50%
    60, // 60%
    70, // 70%
    80, // 80%
    90, // 90%
    100, // 100%
};
const static int32_t LCD_BRIGHTNESS_SUPPORT[] = {
    MODEL_MISSION_ALL&(~MODEL_11), // 10%
    MODEL_MISSION_ALL&(~MODEL_11), // 20%
    MODEL_MISSION_ALL&(~MODEL_11), // 30%
    MODEL_MISSION_ALL&(~MODEL_11), // 40%
    MODEL_MISSION_ALL&(~MODEL_11), // 50%
    MODEL_MISSION_ALL&(~MODEL_11), // 60%
    MODEL_MISSION_ALL&(~MODEL_11), // 70%
    MODEL_MISSION_ALL&(~MODEL_11), // 80%
    MODEL_MISSION_ALL&(~MODEL_11), // 90%
    MODEL_MISSION_ALL&(~MODEL_11), // 100%
};
#pragma endregion

#pragma region LED
#define LED_ID 91
#define LED_SIZE 6
#define LED_NAME "LED"
#define LED_AVA MODEL_MISSION_ALL
const static char* LED_STRING[] = {
    "Off",
    "On",
    "All On",
    "All Off",
    "Front Off Only",
    "Back Only",
};
const static int32_t LED_VALUE[] = {
    0, // Off
    2, // On
    3, // All On
    4, // All Off
    5, // Front Off Only
    100, // Back Only
};
const static int32_t LED_SUPPORT[] = {
    MODEL_11, // Off
    MODEL_11, // On
    MODEL_MISSION_ALL&(~MODEL_11), // All On
    MODEL_MISSION_ALL&(~(MODEL_11|MODEL_13)), // All Off
    MODEL_MISSION_ALL&(~(MODEL_11|MODEL_13)), // Front Off Only
    MODEL_13, // Back Only
};
#pragma endregion

#pragma region Video Aspect Ratio
#define VIDEO_ASPECT_RATIO_ID 108
#define VIDEO_ASPECT_RATIO_SIZE 6
#define VIDEO_ASPECT_RATIO_NAME "Video Aspect Ratio"
#define VIDEO_ASPECT_RATIO_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12
const static char* VIDEO_ASPECT_RATIO_STRING[] = {
    "4:3",
    "16:9",
    "8:7",
    "9:16",
    "21:9",
    "1:1",
};
const static int32_t VIDEO_ASPECT_RATIO_VALUE[] = {
    0, // 4:3
    1, // 16:9
    3, // 8:7
    4, // 9:16
    5, // 21:9
    6, // 1:1
};
const static int32_t VIDEO_ASPECT_RATIO_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 4:3
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 16:9
    MODEL_13|MODEL_12, // 8:7
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 9:16
    MODEL_13, // 21:9
    MODEL_13, // 1:1
};
#pragma endregion

#pragma region Video Lens
#define VIDEO_LENS_ID 121
#define VIDEO_LENS_SIZE 13
#define VIDEO_LENS_NAME "Video Lens"
#define VIDEO_LENS_AVA MODEL_MISSION_ALL
const static char* VIDEO_LENS_STRING[] = {
    "Wide",
    "Narrow",
    "Superview",
    "Linear",
    "Max Superview",
    "Linear + Horizon Leveling",
    "HyperView",
    "Linear + Horizon Lock",
    "Max HyperView",
    "Ultra SuperView",
    "Ultra Wide",
    "Ultra Linear",
    "Ultra HyperView",
};
const static int32_t VIDEO_LENS_VALUE[] = {
    0, // Wide",
    2, // Narrow",
    3, // Superview",
    4, // Linear",
    7, // Max Superview",
    8, // Linear + Horizon Leveling",
    9, // HyperView",
    10, // Linear + Horizon Lock",
    11, // Max HyperView",
    12, // Ultra SuperView",
    13, // Ultra Wide",
    14, // Ultra Linear",
    104, // Ultra HyperView",
};
const static int32_t VIDEO_LENS_SUPPORT[] = {
    MODEL_MISSION_ALL, // Wide",
    MODEL_13|MODEL_10_ALL, // Narrow",
    MODEL_13_ALL, // Superview",
    MODEL_MISSION_ALL&(~MODEL_13), // Linear",
    MODEL_MISSION_ALL, // Max Superview",
    MODEL_13_ALL, // Linear + Horizon Leveling",
    MODEL_13|MODEL_12|MODEL_11S, // HyperView",
    MODEL_13|MODEL_12|MODEL_11S, // Linear + Horizon Lock",
    MODEL_MISSION|MODEL_MAX2|MODEL_12, // Max HyperView",
    MODEL_13, // Ultra SuperView",
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Ultra Wide",
    MODEL_13, // Ultra Linear",
    MODEL_13, // Ultra HyperView",
};
#pragma endregion

#pragma region Photo Lens
#define PHOTO_LENS_ID 122
#define PHOTO_LENS_SIZE 17
#define PHOTO_LENS_NAME "Photo Lens"
#define PHOTO_LENS_AVA MODEL_MISSION_ALL&(~MODEL_11)
const static char* PHOTO_LENS_STRING[] = {
    "Wide 12 MP",
    "Linear 12 MP",
    "9MP Wide",
    "Narrow",
    "Wide 23 MP",
    "Linear 23 MP",
    "Wide 27 MP",
    "Linear 27 MP",
    "9MP Linear",
    "13MP Linear",
    "13MP Wide",
    "13MP Ultra Wide",
    "Ultra Wide 12 MP",
    "13MP Ultra Linear",
    "Max SuperView",
    "Wide",
    "Linear",
};
const static int32_t PHOTO_LENS_VALUE[] = {
    0, // Wide 12 MP
    10, // Linear 12 MP
    15, // 9MP Wide
    19, // Narrow
    27, // Wide 23 MP
    28, // Linear 23 MP
    31, // Wide 27 MP
    32, // Linear 27 MP
    37, // 9MP Linear
    38, // 13MP Linear
    39, // 13MP Wide
    40, // 13MP Ultra Wide
    41, // Ultra Wide 12 MP
    44, // 13MP Ultra Linear
    100, // Max SuperView
    101, // Wide
    102, // Linear
};
const static int32_t PHOTO_LENS_SUPPORT[] = {
    MODEL_13, // Wide 12 MP
    MODEL_13, // Linear 12 MP
    MODEL_MISSION|MODEL_MAX2, // 9MP Wide
    MODEL_10_ALL, // Narrow
    MODEL_13, // Wide 23 MP
    MODEL_13, // Linear 23 MP
    MODEL_13, // Wide 27 MP
    MODEL_13, // Linear 27 MP
    MODEL_MISSION|MODEL_MAX2, // 9MP Linear
    MODEL_13, // 13MP Linear
    MODEL_13, // 13MP Wide
    MODEL_13, // 13MP Ultra Wide
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Ultra Wide 12 MP
    MODEL_13, // 13MP Ultra Linear
    MODEL_12_ALL&(~MODEL_11), // Max SuperView
    MODEL_12_ALL&(~MODEL_11), // Wide
    MODEL_12_ALL&(~MODEL_11), // Linear
};
#pragma endregion

#pragma region Time Lapse Digital Lenses
#define TIME_LAPSE_DIGITAL_LENSES_ID 123
#define TIME_LAPSE_DIGITAL_LENSES_SIZE 6
#define TIME_LAPSE_DIGITAL_LENSES_NAME "Time Lapse Digital Lenses"
#define TIME_LAPSE_DIGITAL_LENSES_AVA MODEL_13_ALL&(~MODEL_11)
const static char* TIME_LAPSE_DIGITAL_LENSES_STRING[] = {
    "Narrow",
    "Wide 27 MP",
    "Linear 27 MP",
    "Max SuperView",
    "Wide",
    "Linear",
};
const static int32_t TIME_LAPSE_DIGITAL_LENSES_VALUE[] = {
    19, // Narrow
    31, // Wide 27 MP
    32, // Linear 27 MP
    100, // Max SuperView
    101, // Wide
    102, // Linear
};
const static int32_t TIME_LAPSE_DIGITAL_LENSES_SUPPORT[] = {
    MODEL_10_ALL, // Narrow
    MODEL_13, // Wide 27 MP
    MODEL_13, // Linear 27 MP
    MODEL_10, // Max SuperView
    MODEL_12_ALL&(~MODEL_11), // Wide
    MODEL_12_ALL&(~MODEL_11), // Linear
};
#pragma endregion

#pragma region Photo Output
#define PHOTO_OUTPUT_ID 125
#define PHOTO_OUTPUT_SIZE 4
#define PHOTO_OUTPUT_NAME "Photo Output"
#define PHOTO_OUTPUT_AVA MODEL_MISSION_ALL&(~MODEL_11)
const static char* PHOTO_OUTPUT_STRING[] = {
    "Standard",
    "RAW",
    "HDR",
    "SuperPhoto",
};
const static int32_t PHOTO_OUTPUT_VALUE[] = {
    0, // Standard 
    1, // RAW 
    2, // HDR 
    3, // SuperPhoto
};
const static int32_t PHOTO_OUTPUT_SUPPORT[] = {
    MODEL_MISSION_ALL&(~MODEL_11), // Standard 
    MODEL_MISSION_ALL&(~MODEL_11), // RAW 
    MODEL_13_ALL&(~MODEL_11), // HDR 
    MODEL_13_ALL&(~MODEL_11), // SuperPhoto
};
#pragma endregion

#pragma region Burst Output
#define BURST_OUTPUT_ID 126
#define BURST_OUTPUT_SIZE 2
#define BURST_OUTPUT_NAME "Burst Output"
#define BURST_OUTPUT_AVA MODEL_MISSION_ALL&(~MODEL_11)
const static char* BURST_OUTPUT_STRING[] = {
    "Standard",
    "RAW",
};
const static int32_t BURST_OUTPUT_VALUE[] = {
    0, // Standard 
    1, // RAW 
};
const static int32_t BURST_OUTPUT_SUPPORT[] = {
    MODEL_MISSION_ALL&(~MODEL_11), // Standard 
    MODEL_MISSION_ALL&(~MODEL_11), // RAW 
};
#pragma endregion

#pragma region Media Format
#define MEDIA_FORMAT_ID 128
#define MEDIA_FORMAT_SIZE 4
#define MEDIA_FORMAT_NAME "Media Format"
#define MEDIA_FORMAT_AVA MODEL_MISSION_ALL&(~MODEL_11)
const static char* MEDIA_FORMAT_STRING[] = {
    "Time Lapse Video",
    "Time Lapse Photo",
    "Night Lapse Photo",
    "Night Lapse Video"
};
const static int32_t MEDIA_FORMAT_VALUE[] = {
    13, // Time Lapse Video 
    20, // Time Lapse Photo 
    21, // Night Lapse Photo 
    26, // Night Lapse Video
};
const static int32_t MEDIA_FORMAT_SUPPORT[] = {
    MODEL_MISSION_ALL&(~MODEL_11), // Time Lapse Video 
    MODEL_MISSION_ALL&(~MODEL_11), // Time Lapse Photo 
    MODEL_MISSION_ALL&(~MODEL_11), // Night Lapse Photo 
    MODEL_MISSION_ALL&(~MODEL_11), // Night Lapse Video
};
#pragma endregion

#pragma region Anti Flicker
#define ANTI_FLICKER_ID 134
#define ANTI_FLICKER_SIZE 4
#define ANTI_FLICKER_NAME "Anti-Flicker"
#define ANTI_FLICKER_AVA MODEL_11_ALL
const static char* ANTI_FLICKER_STRING[] = {
    "NTSC",
    "PAL",
    "60Hz",
    "50Hz",
};
const static int32_t ANTI_FLICKER_VALUE[] = {
    0, // NTSC 
    1, // PAL 
    2, // 60Hz 
    3, // 50Hz
};
const static int32_t ANTI_FLICKER_SUPPORT[] = {
    MODEL_13, // NTSC 
    MODEL_13, // PAL 
    MODEL_12_ALL, // 60Hz 
    MODEL_12_ALL, // 50Hz
};
#pragma endregion

#pragma region Anti Flicker
#define ANTI_FLICKER_V2_ID 213
#define ANTI_FLICKER_V2_SIZE 4
#define ANTI_FLICKER_V2_NAME "Anti-Flicker v2"
#define ANTI_FLICKER_V2_AVA MODEL_13|MODEL_12
const static char* ANTI_FLICKER_V2_STRING[] = {
    "Off",
    "On",
};
const static int32_t ANTI_FLICKER_V2_VALUE[] = {
    0, // Off
    1, // On
};
const static int32_t ANTI_FLICKER_V2_SUPPORT[] = {
    MODEL_13|MODEL_12, // Off
    MODEL_13|MODEL_12, // On
};
#pragma endregion

#pragma region HyperSmooth
#define HYPERSMOOTH_ID 135
#define HYPERSMOOTH_SIZE 6
#define HYPERSMOOTH_NAME "Hypersmooth"
#define HYPERSMOOTH_AVA MODEL_MISSION_ALL
const static char* HYPERSMOOTH_STRING[] = {
    "Off",
    "Low",
    "High",
    "Boost",
    "Auto Boost",
    "Standard",
};
const static int32_t HYPERSMOOTH_VALUE[] = {
    0, // Off
    1, // Low
    2, // High
    3, // Boost
    4, // Auto Boost
    100, // Standard
};
const static int32_t HYPERSMOOTH_SUPPORT[] = {
    MODEL_MISSION_ALL, // Off
    MODEL_MISSION_ALL&(~MODEL_10), // Low
    MODEL_10_ALL, // High
    MODEL_11_ALL, // Boost
    MODEL_MISSION_ALL&(~MODEL_10_ALL), // Auto Boost
    MODEL_10, // Standard
};
#pragma endregion

#pragma region Video Horizon leveling
#define VIDEO_HORIZON_LEVELING_ID 150
#define VIDEO_HORIZON_LEVELING_SIZE 3
#define VIDEO_HORIZON_LEVELING_NAME "Video Horizon Leveling"
#define VIDEO_HORIZON_LEVELING_AVA MODEL_11_BLACK
const static char* VIDEO_HORIZON_LEVELING_STRING[] = {
    "Off",
    "On",
    "Locked",
};
const static int32_t VIDEO_HORIZON_LEVELING_VALUE[] = {
    0, // Off
    1, // On
    2, // Locked
};
const static int32_t VIDEO_HORIZON_LEVELING_SUPPORT[] = {
    MODEL_11_BLACK, // Off
    MODEL_11_BLACK, // On
    MODEL_11_BLACK, // Locked
};
#pragma endregion

#pragma region Photo Horizon leveling
#define PHOTO_HORIZON_LEVELING_ID 151
#define PHOTO_HORIZON_LEVELING_SIZE 3
#define PHOTO_HORIZON_LEVELING_NAME "Photo Horizon Leveling"
#define PHOTO_HORIZON_LEVELING_AVA MODEL_11_BLACK
const static char* PHOTO_HORIZON_LEVELING_STRING[] = {
    "Off",
    "On",
    "Locked",
};
const static int32_t PHOTO_HORIZON_LEVELING_VALUE[] = {
    0, // Off
    1, // On
    2, // Locked
};
const static int32_t PHOTO_HORIZON_LEVELING_SUPPORT[] = {
    MODEL_11_BLACK, // Off
    MODEL_11_BLACK, // On
    MODEL_11_BLACK, // Locked
};
#pragma endregion

#pragma region Video Duration
#define VIDEO_DURATION_ID 156
#define VIDEO_DURATION_SIZE 11
#define VIDEO_DURATION_NAME "Video Duration"
#define VIDEO_DURATION_AVA MODEL_MISSION_ALL&(~MODEL_11)
const static char* VIDEO_DURATION_STRING[] = {
    "15 Sec",
    "30 Sec",
    "1 Min",
    "5 Min",
    "15 Min",
    "30 Min",
    "1 Hour",
    "2 Hour",
    "3 Hour",
    "5 Sec",
    "No Limit",
};
const static int32_t VIDEO_DURATION_VALUE[] = {
    1, // 15 Sec
    2, // 30 Sec
    3, // 1 Min
    4, // 5 Min
    5, // 15 Min
    6, // 30 Min
    7, // 1 Hour
    8, // 2 Hour
    9, // 3 Hour
    10,// 5 Sec
    100, // No Limit
};
const static int32_t VIDEO_DURATION_SUPPORT[] = {
    MODEL_MISSION_ALL&(~MODEL_11), // 15 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 30 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 1 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 5 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 15 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 30 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 1 Hour
    MODEL_MISSION_ALL&(~MODEL_11), // 2 Hour
    MODEL_MISSION_ALL&(~MODEL_11), // 3 Hour
    MODEL_13,// 5 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // No Limit
};
#pragma endregion

#pragma region Multi Shot Duration
#define MULTISHOT_DURATION_ID 157
#define MULTISHOT_DURATION_SIZE 11
#define MULTISHOT_DURATION_NAME "Multi Shot Duration"
#define MULTISHOT_DURATION_AVA MODEL_MISSION_ALL&(~MODEL_11)
const static char* MULTISHOT_DURATION_STRING[] = {
    "Off",
    "15 Sec",
    "30 Sec",
    "1 Min",
    "5 Min",
    "15 Min",
    "30 Min",
    "1 Hour",
    "2 Hour",
    "3 Hour",
    "No Limit",
};
const static int32_t MULTISHOT_DURATION_VALUE[] = {
    0, // Off
    1, // 15 Sec
    2, // 30 Sec
    3, // 1 Min
    4, // 5 Min
    5, // 15 Min
    6, // 30 Min
    7, // 1 Hour
    8, // 2 Hour
    9, // 3 Hour
    100, // No Limit
};
const static int32_t MULTISHOT_DURATION_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2, // Off
    MODEL_MISSION_ALL&(~MODEL_11), // 15 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 30 Sec
    MODEL_MISSION_ALL&(~MODEL_11), // 1 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 5 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 15 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 30 Min
    MODEL_MISSION_ALL&(~MODEL_11), // 1 Hour
    MODEL_MISSION_ALL&(~MODEL_11), // 2 Hour
    MODEL_MISSION_ALL&(~MODEL_11), // 3 Hour
    MODEL_13_ALL&(~MODEL_11), // No Limit
};
#pragma endregion

#pragma region Max Lens
#define MAX_LENS_ID 162
#define MAX_LENS_SIZE 2
#define MAX_LENS_NAME "Max Lens"
#define MAX_LENS_AVA MODEL_11_BLACK|MODEL_10|MODEL_9
const static char* MAX_LENS_STRING[] = {
    "Off",
    "On", 
};
const static int32_t MAX_LENS_VALUE[] = {
    0, // Off
    1, // On"
};
const static int32_t MAX_LENS_SUPPORT[] = {
    MODEL_11_BLACK|MODEL_10|MODEL_9, // Off
    MODEL_11_BLACK|MODEL_10|MODEL_9, // On"
};
#pragma endregion

#pragma region Hind Sight
#define HINDSIGHT_ID 167
#define HINDSIGHT_SIZE 3
#define HINDSIGHT_NAME "HindSight"
#define HINDSIGHT_AVA MODEL_13_ALL&(~MODEL_11)
const static char* HINDSIGHT_STRING[] = {
    "15 Sec",
    "30 Sec",
    "Off",
};
const static int32_t HINDSIGHT_VALUE[] = {
    2, // 15 Sec
    3, // 30 Sec
    4, // Off
};
const static int32_t HINDSIGHT_SUPPORT[] = {
    MODEL_13_ALL&(~MODEL_11), // 15 Sec
    MODEL_13_ALL&(~MODEL_11), // 30 Sec
    MODEL_13_ALL&(~MODEL_11), // Off
};
#pragma endregion

#pragma region Photo Single Interval
#define PHOTO_SINGLE_INTERVAL_ID 171
#define PHOTO_SINGLE_INTERVAL_SIZE 10
#define PHOTO_SINGLE_INTERVAL_NAME "Photo Single Interval"
#define PHOTO_SINGLE_INTERVAL_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12
const static char* PHOTO_SINGLE_INTERVAL_STRING[] = {
    "Off",
    "0.5s",
    "1s",
    "2s",
    "5s",
    "10s",
    "30s",
    "60s",
    "120s",
    "3s",
};
const static int32_t PHOTO_SINGLE_INTERVAL_VALUE[] = {
    0, // Off
    2, // 0.5s
    3, // 1s
    4, // 2s
    5, // 5s
    6, // 10s
    7, // 30s
    8, // 60s
    9, // 120s
    10, // 3s
};
const static int32_t PHOTO_SINGLE_INTERVAL_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // Off
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 0.5s
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 1s
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 2s
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 5s
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 10s
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 30s
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 60s
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 120s
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 3s
};
#pragma endregion

#pragma region Photo single duration
#define PHOTO_SINGLE_DURATION_ID 172
#define PHOTO_SINGLE_DURATION_SIZE 10
#define PHOTO_SINGLE_DURATION_NAME "Photo Single Duration"
#define PHOTO_SINGLE_DURATION_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12
const static char* PHOTO_SINGLE_DURATION_STRING[] = {
    "Off",
    "15 Sec",
    "30 Sec",
    "1 Min",
    "5 Min",
    "15 Min",
    "30 Min",
    "1 Hour",
    "2 Hour",
    "3 Hour",
};
const static int32_t PHOTO_SINGLE_DURATION_VALUE[] = {
    0, // Off
    1, // 15 Sec
    2, // 30 Sec
    3, // 1 Min
    4, // 5 Min
    5, // 15 Min
    6, // 30 Min
    7, // 1 Hour
    8, // 2 Hour
    9, // 3 Hour
};
const static int32_t PHOTO_SINGLE_DURATION_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // Off
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 15 Sec
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 30 Sec
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 1 Min
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 5 Min
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 15 Min
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 30 Min
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 1 Hour
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 2 Hour
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 3 Hour
};
#pragma endregion

#pragma region Video Performance Mode
#define VIDEO_PERFORMANCE_MODE_ID 173
#define VIDEO_PERFORMANCE_MODE_SIZE 3
#define VIDEO_PERFORMANCE_MODE_NAME "Video Performance Mode"
#define VIDEO_PERFORMANCE_MODE_AVA MODEL_10
const static char* VIDEO_PERFORMANCE_MODE_STRING[] = {
    "Maximum Video Performance",
    "Extended Battery",
    "Tripod / Stationary Video",
};
const static int32_t VIDEO_PERFORMANCE_MODE_VALUE[] = {
    0, // Maximum Video Performance",
    1, // Extended Battery",
    2, // Tripod / Stationary Video",
};
const static int32_t VIDEO_PERFORMANCE_MODE_SUPPORT[] = {
    MODEL_10, // Maximum Video Performance",
    MODEL_10, // Extended Battery",
    MODEL_10, // Tripod / Stationary Video",
};
#pragma endregion

#pragma region Control Mode
#define CONTROL_MODE_ID 175
#define CONTROL_MODE_SIZE 2
#define CONTROL_MODE_NAME "Control Mode"
#define CONTROL_MODE_AVA MODEL_13|MODEL_12|MODEL_11_BLACK
const static char* CONTROL_MODE_STRING[] = {
    "Easy",
    "Pro", 
};
const static int32_t CONTROL_MODE_VALUE[] = {
    0, // Easy
    1, // Pro"
};
const static int32_t CONTROL_MODE_SUPPORT[] = {
    MODEL_13|MODEL_12|MODEL_11_BLACK, // Easy
    MODEL_13|MODEL_12|MODEL_11_BLACK, // Pro"
};
#pragma endregion

#pragma region Easy Mode Speed
#define EASY_MODE_SPEED_ID 176
#define EASY_MODE_SPEED_SIZE 88
#define EASY_MODE_SPEED_NAME "Easy Mode Speed"
#define EASY_MODE_SPEED_AVA MODEL_13|MODEL_12|MODEL_11_BLACK
const static char* EASY_MODE_SPEED_STRING[] = {
    "8X Ultra Slo-Mo",
    "4X Super Slo-Mo",
    "2X Slo-Mo",
    "1X Speed (Low Light)",
    "4X Super Slo-Mo (Ext. Batt.)",
    "2X Slo-Mo (Ext. Batt.)",
    "1X Speed (Ext. Batt.) (Low Light)",
    "8X Ultra Slo-Mo (50Hz)",
    "4X Super Slo-Mo (50Hz)",
    "2X Slo-Mo (50Hz)",
    "1X Speed (50Hz) (Low Light)",
    "4X Super Slo-Mo (50Hz) (Ext. Batt.)",
    "2X Slo-Mo (50Hz) (Ext. Batt.)",
    "1X Speed (50Hz) (Ext. Batt.) (Low Light)",
    "8X Ultra Slo-Mo (Ext. Batt.)",
    "8X Ultra Slo-Mo (50Hz) (Ext. Batt.)",
    "8X Ultra Slo-Mo (Long. Batt.)",
    "4X Super Slo-Mo (Long. Batt.)",
    "2X Slo-Mo (Long. Batt.)",
    "1X Speed (Long. Batt.) (Low Light)",
    "8X Ultra Slo-Mo (50Hz) (Long. Batt.)",
    "4X Super Slo-Mo (50Hz) (Long. Batt.)",
    "2X Slo-Mo (50Hz) (Long. Batt.)",
    "1X Speed (50Hz) (Long. Batt.) (Low Light)",
    "2X Slo-Mo (4K)",
    "4X Super Slo-Mo (2.7K)",
    "2X Slo-Mo (4K) (50Hz)",
    "4X Super Slo-Mo (2.7K) (50Hz)",
    "8X Ultra Slo-Mo (V2)",
    "4X Super Slo-Mo (V2)",
    "2X Slo-Mo (V2)",
    "1X Speed (Low Light) (V2)",
    "8X Ultra Slo-Mo (50Hz) (V2)",
    "4X Super Slo-Mo (50Hz) (V2)",
    "2X Slo-Mo (50Hz) (V2)",
    "1X Speed (50Hz) (Low Light) (V2)",
    "8X Ultra Slo-Mo (Long. Batt.) (V2)",
    "4X Super Slo-Mo (Long. Batt.) (V2)",
    "2X Slo-Mo (Long. Batt.) (V2)",
    "1X Speed (Long. Batt.) (Low Light) (V2)",
    "8X Ultra Slo-Mo (50Hz) (Long. Batt.) (V2)",
    "4X Super Slo-Mo (50Hz) (Long. Batt.) (V2)",
    "2X Slo-Mo (50Hz) (Long. Batt.) (V2)",
    "1X Speed (50Hz) (Long. Batt.) (Low Light) (V2)",
    "2X Slo-Mo (4K) (V2)",
    "2X Slo-Mo (4K) (50Hz) (V2)",
    "1X Speed (Low Light) (V2) (Vertical)",
    "1X Speed (50Hz) (Low Light) (V2) (Vertical)",
    "2X Slo-Mo (V2) (Vertical)",
    "2X Slo-Mo (50Hz) (V2) (Vertical)",
    "1X Speed (Full Frame) (Low Light) (V2)",
    "1X Speed (50Hz) (Full Frame) (Low Light) (V2)",
    "2X Slo-Mo (Full Frame) (V2)",
    "2X Slo-Mo (50Hz) (Full Frame) (V2)",
    "1X Speed (4K) (Low Light) (V2)",
    "1X Speed (4K) (50Hz) (Low Light) (V2)",
    "1X Speed (2.7K) (Low Light) (V2)",
    "1X Speed (2.7K) (50Hz) (Low Light) (V2)",
    "2X Slo-Mo (2.7K) (V2)",
    "2X Slo-Mo (2.7K) (50Hz) (V2)",
    "2X Slo-Mo (Long. Batt.) (V2) (Vertical)",
    "2X Slo-Mo (50Hz) (Long. Batt.) (V2) (Vertical)",
    "1X Speed (Long. Batt.) (Low Light) (V2) (Vertical)",
    "1X Speed (50Hz) (Long. Batt.) (Low Light) (V2) (Vertical)",
    "1X Speed (4K) (Full Frame) (Low Light) (V2)",
    "1X Speed (4K) (50Hz) (Full Frame) (Low Light) (V2)",
    "1X Normal Speed (1:1) (30 Fps) (4K) (V2)",
    "1X Normal Speed (1:1) (25 Fps) (4K) (V2)",
    "2X Slo-Mo Speed (1:1) (4K) (60 Fps) (V2)",
    "2X Slo-Mo Speed (1:1) (4K) (50 Fps) (V2)",
    "1X Normal Speed (21:9) (30 Fps) (5.3K) (V2)",
    "1X Normal Speed (21:9) (25 Fps) (5.3K) (V2)",
    "2X Slo-Mo Speed (21:9) (5.3K) (60 Fps) (V2)",
    "2X Slo-Mo Speed (21:9) (5.3K) (50 Fps) (V2)",
    "1X Normal Speed (21:9) (30 Fps) (4K) (V2)",
    "1X Normal Speed (21:9) (25 Fps) (4K) (V2)",
    "2X Slo-Mo Speed (21:9) (4K) (60 Fps) (V2)",
    "2X Slo-Mo Speed (21:9) (4K) (50 Fps) (V2)",
    "120 4X Super Slo-Mo Speed (21:9) (4K) (V2)",
    "100 4X Super Slo-Mo Speed (21:9) (4K) (V2)",
    "1X Normal Speed (30 Fps) (4:3) (5.3K) (V2)",
    "1X Normal Speed (25 Fps) (4:3) (5.3K) (V2)",
    "1X Normal Speed (30 Fps) (4:3) (4K) (V2)",
    "1X Normal Speed (25 Fps) (4:3) (4K) (V2)",
    "2X Slo-Mo Speed (4:3) (4K) (60 Fps) (V2)",
    "2X Slo-Mo Speed (4:3) (4K) (50 Fps) (V2)",
    "120 4X Super Slo-Mo Speed (2.7K) (4:3) (V2)",
    "100 4X Super Slo-Mo Speed (2.7K) (4:3) (V2)",
};
const static int32_t EASY_MODE_SPEED_VALUE[] = {
    0, // 8X Ultra Slo-Mo
    1, // 4X Super Slo-Mo
    2, // 2X Slo-Mo
    3, // 1X Speed (Low Light)
    4, // 4X Super Slo-Mo (Ext. Batt.)
    5, // 2X Slo-Mo (Ext. Batt.)
    6, // 1X Speed (Ext. Batt.) (Low Light)
    7, // 8X Ultra Slo-Mo (50Hz)
    8, // 4X Super Slo-Mo (50Hz)
    9, // 2X Slo-Mo (50Hz)
    10, // 1X Speed (50Hz) (Low Light)
    11, // 4X Super Slo-Mo (50Hz) (Ext. Batt.)
    12, // 2X Slo-Mo (50Hz) (Ext. Batt.)
    13, // 1X Speed (50Hz) (Ext. Batt.) (Low Light)
    14, // 8X Ultra Slo-Mo (Ext. Batt.)
    15, // 8X Ultra Slo-Mo (50Hz) (Ext. Batt.)
    16, // 8X Ultra Slo-Mo (Long. Batt.)
    17, // 4X Super Slo-Mo (Long. Batt.)
    18, // 2X Slo-Mo (Long. Batt.)
    19, // 1X Speed (Long. Batt.) (Low Light)
    20, // 8X Ultra Slo-Mo (50Hz) (Long. Batt.)
    21,// 4X Super Slo-Mo (50Hz) (Long. Batt.)
    22, // 2X Slo-Mo (50Hz) (Long. Batt.)
    23, // 1X Speed (50Hz) (Long. Batt.) (Low Light)
    24, // 2X Slo-Mo (4K)
    25, // 4X Super Slo-Mo (2.7K)
    26, // 2X Slo-Mo (4K) (50Hz)
    27, // 4X Super Slo-Mo (2.7K) (50Hz)
    100, // 8X Ultra Slo-Mo (V2)
    101, // 4X Super Slo-Mo (V2)
    102, // 2X Slo-Mo (V2)
    103, // 1X Speed (Low Light) (V2)
    104, // 8X Ultra Slo-Mo (50Hz) (V2)
    105, // 4X Super Slo-Mo (50Hz) (V2)
    106, // 2X Slo-Mo (50Hz) (V2)
    107, // 1X Speed (50Hz) (Low Light) (V2)
    108, // 8X Ultra Slo-Mo (Long. Batt.) (V2)
    109, // 4X Super Slo-Mo (Long. Batt.) (V2)
    110, // 2X Slo-Mo (Long. Batt.) (V2)
    111,// 1X Speed (Long. Batt.) (Low Light) (V2)
    112, // 8X Ultra Slo-Mo (50Hz) (Long. Batt.) (V2)
    113, // 4X Super Slo-Mo (50Hz) (Long. Batt.) (V2)
    114, // 2X Slo-Mo (50Hz) (Long. Batt.) (V2)
    115, // 1X Speed (50Hz) (Long. Batt.) (Low Light) (V2)
    116, // 2X Slo-Mo (4K) (V2)
    117, // 2X Slo-Mo (4K) (50Hz) (V2)
    118, // 1X Speed (Low Light) (V2) (Vertical)
    119, // 1X Speed (50Hz) (Low Light) (V2) (Vertical)
    120, // 2X Slo-Mo (V2) (Vertical)
    121, // 2X Slo-Mo (50Hz) (V2) (Vertical)
    122, // 1X Speed (Full Frame) (Low Light) (V2)
    123, // 1X Speed (50Hz) (Full Frame) (Low Light) (V2)
    124, // 2X Slo-Mo (Full Frame) (V2)
    125, // 2X Slo-Mo (50Hz) (Full Frame) (V2)
    126, // 1X Speed (4K) (Low Light) (V2)
    127, // 1X Speed (4K) (50Hz) (Low Light) (V2)
    128,// 1X Speed (2.7K) (Low Light) (V2)
    129, // 1X Speed (2.7K) (50Hz) (Low Light) (V2)
    130, // 2X Slo-Mo (2.7K) (V2)
    131, // 2X Slo-Mo (2.7K) (50Hz) (V2)
    132, // 2X Slo-Mo (Long. Batt.) (V2) (Vertical)
    133, // 2X Slo-Mo (50Hz) (Long. Batt.) (V2) (Vertical)
    134, // 1X Speed (Long. Batt.) (Low Light) (V2) (Vertical)
    135, // 1X Speed (50Hz) (Long. Batt.) (Low Light) (V2) (Vertical)
    136, // 1X Speed (4K) (Full Frame) (Low Light) (V2)
    137, // 1X Speed (4K) (50Hz) (Full Frame) (Low Light) (V2)
    138, // 1X Normal Speed (1:1) (30 Fps) (4K) (V2)
    139, // 1X Normal Speed (1:1) (25 Fps) (4K) (V2)
    140, // 2X Slo-Mo Speed (1:1) (4K) (60 Fps) (V2)
    141, // 2X Slo-Mo Speed (1:1) (4K) (50 Fps) (V2)
    142, // 1X Normal Speed (21:9) (30 Fps) (5.3K) (V2)
    143, // 1X Normal Speed (21:9) (25 Fps) (5.3K) (V2)
    144, // 2X Slo-Mo Speed (21:9) (5.3K) (60 Fps) (V2)
    145, // 2X Slo-Mo Speed (21:9) (5.3K) (50 Fps) (V2)
    146, // 1X Normal Speed (21:9) (30 Fps) (4K) (V2)
    147, // 1X Normal Speed (21:9) (25 Fps) (4K) (V2)
    148, // 2X Slo-Mo Speed (21:9) (4K) (60 Fps) (V2)
    149, // 2X Slo-Mo Speed (21:9) (4K) (50 Fps) (V2)
    150, // 120 4X Super Slo-Mo Speed (21:9) (4K) (V2)
    151, // 100 4X Super Slo-Mo Speed (21:9) (4K) (V2)
    152, // 1X Normal Speed (30 Fps) (4:3) (5.3K) (V2)
    153, // 1X Normal Speed (25 Fps) (4:3) (5.3K) (V2)
    154, // 1X Normal Speed (30 Fps) (4:3) (4K) (V2)
    155, // 1X Normal Speed (25 Fps) (4:3) (4K) (V2)
    156, // 2X Slo-Mo Speed (4:3) (4K) (60 Fps) (V2)
    157, // 2X Slo-Mo Speed (4:3) (4K) (50 Fps) (V2)
    158, // 120 4X Super Slo-Mo Speed (2.7K) (4:3) (V2)
    159, // 100 4X Super Slo-Mo Speed (2.7K) (4:3) (V2)
};
const static int32_t EASY_MODE_SPEED_SUPPORT[] = {
    MODEL_11_BLACK, // 8X Ultra Slo-Mo
    MODEL_11_BLACK, // 4X Super Slo-Mo
    MODEL_11_BLACK, // 2X Slo-Mo
    MODEL_11_BLACK, // 1X Speed (Low Light)
    MODEL_11_BLACK, // 4X Super Slo-Mo (Ext. Batt.)
    MODEL_11_BLACK, // 2X Slo-Mo (Ext. Batt.)
    MODEL_11_BLACK, // 1X Speed (Ext. Batt.) (Low Light)
    MODEL_11_BLACK, // 8X Ultra Slo-Mo (50Hz)
    MODEL_11_BLACK, // 4X Super Slo-Mo (50Hz)
    MODEL_11_BLACK, // 2X Slo-Mo (50Hz)
    MODEL_11_BLACK, // 1X Speed (50Hz) (Low Light)
    MODEL_11_BLACK, // 4X Super Slo-Mo (50Hz) (Ext. Batt.)
    MODEL_11_BLACK, // 2X Slo-Mo (50Hz) (Ext. Batt.)
    MODEL_11_BLACK, // 1X Speed (50Hz) (Ext. Batt.) (Low Light)
    MODEL_11_BLACK, // 8X Ultra Slo-Mo (Ext. Batt.)
    MODEL_11_BLACK, // 8X Ultra Slo-Mo (50Hz) (Ext. Batt.)
    MODEL_11_BLACK, // 8X Ultra Slo-Mo (Long. Batt.)
    MODEL_11_BLACK, // 4X Super Slo-Mo (Long. Batt.)
    MODEL_11_BLACK, // 2X Slo-Mo (Long. Batt.)
    MODEL_11_BLACK, // 1X Speed (Long. Batt.) (Low Light)
    MODEL_11_BLACK, // 8X Ultra Slo-Mo (50Hz) (Long. Batt.)
    MODEL_11_BLACK,// 4X Super Slo-Mo (50Hz) (Long. Batt.)
    MODEL_11_BLACK, // 2X Slo-Mo (50Hz) (Long. Batt.)
    MODEL_11_BLACK, // 1X Speed (50Hz) (Long. Batt.) (Low Light)
    MODEL_11_BLACK, // 2X Slo-Mo (4K)
    MODEL_11_BLACK, // 4X Super Slo-Mo (2.7K)
    MODEL_11_BLACK, // 2X Slo-Mo (4K) (50Hz)
    MODEL_11_BLACK, // 4X Super Slo-Mo (2.7K) (50Hz)
    MODEL_13|MODEL_12, // 8X Ultra Slo-Mo (V2)
    MODEL_13|MODEL_12, // 4X Super Slo-Mo (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (V2)
    MODEL_13|MODEL_12, // 1X Speed (Low Light) (V2)
    MODEL_13|MODEL_12, // 8X Ultra Slo-Mo (50Hz) (V2)
    MODEL_13|MODEL_12, // 4X Super Slo-Mo (50Hz) (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (50Hz) (V2)
    MODEL_13|MODEL_12, // 1X Speed (50Hz) (Low Light) (V2)
    MODEL_13|MODEL_12, // 8X Ultra Slo-Mo (Long. Batt.) (V2)
    MODEL_13|MODEL_12, // 4X Super Slo-Mo (Long. Batt.) (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (Long. Batt.) (V2)
    MODEL_13|MODEL_12,// 1X Speed (Long. Batt.) (Low Light) (V2)
    MODEL_13|MODEL_12, // 8X Ultra Slo-Mo (50Hz) (Long. Batt.) (V2)
    MODEL_13|MODEL_12, // 4X Super Slo-Mo (50Hz) (Long. Batt.) (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (50Hz) (Long. Batt.) (V2)
    MODEL_13|MODEL_12, // 1X Speed (50Hz) (Long. Batt.) (Low Light) (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (4K) (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (4K) (50Hz) (V2)
    MODEL_13|MODEL_12, // 1X Speed (Low Light) (V2) (Vertical)
    MODEL_13|MODEL_12, // 1X Speed (50Hz) (Low Light) (V2) (Vertical)
    MODEL_13|MODEL_12, // 2X Slo-Mo (V2) (Vertical)
    MODEL_13|MODEL_12, // 2X Slo-Mo (50Hz) (V2) (Vertical)
    MODEL_13|MODEL_12, // 1X Speed (Full Frame) (Low Light) (V2)
    MODEL_13|MODEL_12, // 1X Speed (50Hz) (Full Frame) (Low Light) (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (Full Frame) (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (50Hz) (Full Frame) (V2)
    MODEL_13|MODEL_12, // 1X Speed (4K) (Low Light) (V2)
    MODEL_13|MODEL_12, // 1X Speed (4K) (50Hz) (Low Light) (V2)
    MODEL_12,// 1X Speed (2.7K) (Low Light) (V2)
    MODEL_12, // 1X Speed (2.7K) (50Hz) (Low Light) (V2)
    MODEL_12, // 2X Slo-Mo (2.7K) (V2)
    MODEL_12, // 2X Slo-Mo (2.7K) (50Hz) (V2)
    MODEL_13|MODEL_12, // 2X Slo-Mo (Long. Batt.) (V2) (Vertical)
    MODEL_13|MODEL_12, // 2X Slo-Mo (50Hz) (Long. Batt.) (V2) (Vertical)
    MODEL_13|MODEL_12, // 1X Speed (Long. Batt.) (Low Light) (V2) (Vertical)
    MODEL_13|MODEL_12, // 1X Speed (50Hz) (Long. Batt.) (Low Light) (V2) (Vertical)
    MODEL_13|MODEL_12, // 1X Speed (4K) (Full Frame) (Low Light) (V2)
    MODEL_13|MODEL_12, // 1X Speed (4K) (50Hz) (Full Frame) (Low Light) (V2)
    MODEL_13, // 1X Normal Speed (1:1) (30 Fps) (4K) (V2)
    MODEL_13, // 1X Normal Speed (1:1) (25 Fps) (4K) (V2)
    MODEL_13, // 2X Slo-Mo Speed (1:1) (4K) (60 Fps) (V2)
    MODEL_13, // 2X Slo-Mo Speed (1:1) (4K) (50 Fps) (V2)
    MODEL_13, // 1X Normal Speed (21:9) (30 Fps) (5.3K) (V2)
    MODEL_13, // 1X Normal Speed (21:9) (25 Fps) (5.3K) (V2)
    MODEL_13, // 2X Slo-Mo Speed (21:9) (5.3K) (60 Fps) (V2)
    MODEL_13, // 2X Slo-Mo Speed (21:9) (5.3K) (50 Fps) (V2)
    MODEL_13, // 1X Normal Speed (21:9) (30 Fps) (4K) (V2)
    MODEL_13, // 1X Normal Speed (21:9) (25 Fps) (4K) (V2)
    MODEL_13, // 2X Slo-Mo Speed (21:9) (4K) (60 Fps) (V2)
    MODEL_13, // 2X Slo-Mo Speed (21:9) (4K) (50 Fps) (V2)
    MODEL_13, // 120 4X Super Slo-Mo Speed (21:9) (4K) (V2)
    MODEL_13, // 100 4X Super Slo-Mo Speed (21:9) (4K) (V2)
    MODEL_13, // 1X Normal Speed (30 Fps) (4:3) (5.3K) (V2)
    MODEL_13, // 1X Normal Speed (25 Fps) (4:3) (5.3K) (V2)
    MODEL_13, // 1X Normal Speed (30 Fps) (4:3) (4K) (V2)
    MODEL_13, // 1X Normal Speed (25 Fps) (4:3) (4K) (V2)
    MODEL_13, // 2X Slo-Mo Speed (4:3) (4K) (60 Fps) (V2)
    MODEL_13, // 2X Slo-Mo Speed (4:3) (4K) (50 Fps) (V2)
    MODEL_13, // 120 4X Super Slo-Mo Speed (2.7K) (4:3) (V2)
    MODEL_13, // 100 4X Super Slo-Mo Speed (2.7K) (4:3) (V2)
};
#pragma endregion

#pragma region Enable Night Photo
#define ENABLE_NIGHT_PHOTO_ID 177
#define ENABLE_NIGHT_PHOTO_SIZE 2
#define ENABLE_NIGHT_PHOTO_NAME "Enable Night Photo"
#define ENABLE_NIGHT_PHOTO_AVA MODEL_11_BLACK
const static char* ENABLE_NIGHT_PHOTO_STRING[] = {
    "Off",
    "On",
};
const static int32_t ENABLE_NIGHT_PHOTO_VALUE[] = {
    0, // Off
    1, // On
};
const static int32_t ENABLE_NIGHT_PHOTO_SUPPORT[] = {
    MODEL_11_BLACK, // Off
    MODEL_11_BLACK, // On
};
#pragma endregion

#pragma region Wireless Band
#define WIRELESS_BAND_ID 178
#define WIRELESS_BAND_SIZE 2
#define WIRELESS_BAND_NAME "Wireless Band"
#define WIRELESS_BAND_AVA MODEL_MISSION_ALL&(~(MODEL_10|MODEL_9))
const static char* WIRELESS_BAND_STRING[] = {
    "2.4 GHz",
    "5 GHz"
};
const static int32_t WIRELESS_BAND_VALUE[] = {
    0, // 2.4 GHz
    1, // 5 GH
};
const static int32_t WIRELESS_BAND_SUPPORT[] = {
    MODEL_MISSION_ALL&(~(MODEL_10|MODEL_9)), // 2.4 GHz
    MODEL_MISSION_ALL&(~(MODEL_10|MODEL_9)), // 5 GH
};
#pragma endregion

#pragma region Star Trails Length
#define STAR_TRAILS_LENGTH_ID 179
#define STAR_TRAILS_LENGTH_SIZE 3
#define STAR_TRAILS_LENGTH_NAME "Star Trails Length"
#define STAR_TRAILS_LENGTH_AVA MODEL_MISSION_ALL&(~(MODEL_10|MODEL_9))
const static char* STAR_TRAILS_LENGTH_STRING[] = {
    "Short",
    "Long",
    "Max", 
};
const static int32_t STAR_TRAILS_LENGTH_VALUE[] = {
    1, // Short",
    2, // Long",
    3, // Max", 
};
const static int32_t STAR_TRAILS_LENGTH_SUPPORT[] = {
    MODEL_MISSION_ALL&(~(MODEL_10|MODEL_9)), // Short",
    MODEL_MISSION_ALL&(~(MODEL_10|MODEL_9)), // Long",
    MODEL_MISSION_ALL&(~(MODEL_10|MODEL_9)), // Max", 
};
#pragma endregion

#pragma region System Video Mode
#define SYSTEM_VIDEO_MODE_ID 180
#define SYSTEM_VIDEO_MODE_SIZE 5
#define SYSTEM_VIDEO_MODE_NAME "System Video Mode"
#define SYSTEM_VIDEO_MODE_AVA MODEL_13|MODEL_11_BLACK
const static char* SYSTEM_VIDEO_MODE_STRING[] = {
    "Highest Quality",
    "Extended Battery",
    "Longest Battery",
    "Standard Quality",
    "Basic Quality",
};
const static int32_t SYSTEM_VIDEO_MODE_VALUE[] = {
    0, // Highest Quality
    101, // Extended Battery
    102, // Longest Battery
    111, // Standard Quality
    112, // Basic Quality
};
const static int32_t SYSTEM_VIDEO_MODE_SUPPORT[] = {
    MODEL_13|MODEL_11_BLACK, // Highest Quality
    MODEL_11_BLACK, // Extended Battery
    MODEL_11_BLACK, // Longest Battery
    MODEL_13, // Standard Quality
    MODEL_13, // Basic Quality
};
#pragma endregion

#pragma region Video Bit Rate
#define VIDEO_BIT_RATE_ID 182
#define VIDEO_BIT_RATE_SIZE 2
#define VIDEO_BIT_RATE_NAME "Video Bit Rate"
#define VIDEO_BIT_RATE_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12
const static char* VIDEO_BIT_RATE_STRING[] = {
    "Standard",
    "High",
};
const static int32_t VIDEO_BIT_RATE_VALUE[] = {
    0, // Standard
    1, // High
};
const static int32_t VIDEO_BIT_RATE_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // Standard
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // High
};
#pragma endregion

#pragma region Bit Depth
#define BIT_DEPTH_ID 183
#define BIT_DEPTH_SIZE 2
#define BIT_DEPTH_NAME "Bit Depth"
#define BIT_DEPTH_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12
const static char* BIT_DEPTH_STRING[] = {
    "8-bit",
    "10-bit",
};
const static int32_t BIT_DEPTH_VALUE[] = {
    0, // 8-bit
    2, // 10-bit
};
const static int32_t BIT_DEPTH_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 8-bit
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // 10-bit
};
#pragma endregion

#pragma region Profiles
#define PROFILES_ID 184
#define PROFILES_SIZE 4
#define PROFILES_NAME "Profiles"
#define PROFILES_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12
const static char* PROFILES_STRING[] = {
    "Standard",
    "HDR",
    "HLG HDR",
    "Log",
};
const static int32_t PROFILES_VALUE[] = {
    0, // Standard
    1, // HDR
    101, // HLG HD
    2, // Log
};
const static int32_t PROFILES_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // Standard
    MODEL_13|MODEL_12, // HDR
    MODEL_13, // HLG HD
    MODEL_MISSION|MODEL_MAX2|MODEL_13|MODEL_12, // Log
};
#pragma endregion

#pragma region Video Easy Mode
#define VIDEO_EASY_MODE_ID 186
#define VIDEO_EASY_MODE_SIZE 5
#define VIDEO_EASY_MODE_NAME "Video Easy Mode"
#define VIDEO_EASY_MODE_AVA MODEL_13|MODEL_12
const static char* VIDEO_EASY_MODE_STRING[] = {
    "Highest Quality",
    "Standard Quality",
    "Basic Quality",
    "Standard Video",
    "HDR Video",
};
const static int32_t VIDEO_EASY_MODE_VALUE[] = {
    0, // Highest Quality
    1, // Standard Quality
    2, // Basic Quality
    3, // Standard Video
    4, // HDR Video
};
const static int32_t VIDEO_EASY_MODE_SUPPORT[] = {
    MODEL_12, // Highest Quality
    MODEL_12, // Standard Quality
    MODEL_12, // Basic Quality
    MODEL_13, // Standard Video
    MODEL_13, // HDR Video
};
#pragma endregion

#pragma region Lapse Mode
#define LAPSE_MODE_ID 187
#define LAPSE_MODE_SIZE 5
#define LAPSE_MODE_NAME "Lapse Mode"
#define LAPSE_MODE_AVA MODEL_13|MODEL_12
const static char* LAPSE_MODE_STRING[] = {
    "TimeWarp",
    "Star Trails",
    "Light Painting",
    "Vehicle Lights",
    "Max TimeWarp",
    "Max Star Trails",
    "Max Light Painting",
    "Max Vehicle Lights",
    "Time Lapse Video",
    "Night Lapse Video",
};
const static int32_t LAPSE_MODE_VALUE[] = {
    0, // TimeWarp
    1, // Star Trails
    2, // Light Painting
    3, // Vehicle Lights
    4, // Max TimeWarp
    5, // Max Star Trails
    6, // Max Light Painting
    7, // Max Vehicle Lights
    8, // Time Lapse Video
    9, // Night Lapse Video
};
const static int32_t LAPSE_MODE_SUPPORT[] = {
    MODEL_13|MODEL_12, // TimeWarp
    MODEL_13|MODEL_12, // Star Trails
    MODEL_13|MODEL_12, // Light Painting
    MODEL_13|MODEL_12, // Vehicle Lights
    MODEL_12, // Max TimeWarp
    MODEL_12, // Max Star Trails
    MODEL_12, // Max Light Painting
    MODEL_12, // Max Vehicle Lights
    MODEL_13, // Time Lapse Video
    MODEL_13, // Night Lapse Video
};
#pragma endregion

#pragma region Max Lens Mod
#define MAX_LENS_MOD_ID 189
#define MAX_LENS_MOD_SIZE 12
#define MAX_LENS_MOD_NAME "Max Lens Mod"
#define MAX_LENS_MOD_AVA MODEL_13|MODEL_12
const static char* MAX_LENS_MOD_STRING[] = {
    "None",
    "Max Lens 1.0",
    "Max Lens 2.0",
    "Max Lens 2.5",
    "Macro",
    "Anamorphic",
    "ND 4",
    "ND 8",
    "ND 16",
    "ND 32",
    "Standard Lens",
    "Auto Detect",
};
const static int32_t MAX_LENS_MOD_VALUE[] = {
    0, // None
    1, // Max Lens 1.0
    2, // Max Lens 2.0
    3, // Max Lens 2.5
    4, // Macro
    5, // Anamorphic
    6, // ND 4
    7, // ND 8
    8, // ND 16
    9, // ND 32
    10, // Standard Lens
    100, // Auto Detect
};
const static int32_t MAX_LENS_MOD_SUPPORT[] = {
    MODEL_12, // None
    MODEL_12, // Max Lens 1.0
    MODEL_13|MODEL_12, // Max Lens 2.0
    MODEL_13, // Max Lens 2.5
    MODEL_13, // Macro
    MODEL_13, // Anamorphic
    MODEL_13, // ND 4
    MODEL_13, // ND 8
    MODEL_13, // ND 16
    MODEL_13, // ND 32
    MODEL_13, // Standard Lens
    MODEL_13, // Auto Detect
};
#pragma endregion

#pragma region Max Lens Mod Enable
#define MAX_LENS_MOD_ENABLE_ID 190
#define MAX_LENS_MOD_ENABLE_SIZE 2
#define MAX_LENS_MOD_ENABLE_NAME "Max Lens Mod Enable"
#define MAX_LENS_MOD_ENABLE_AVA MODEL_12
const static char* MAX_LENS_MOD_ENABLE_STRING[] = {
    "Off",
    "On",
};
const static int32_t MAX_LENS_MOD_ENABLE_VALUE[] = {
    0, // Off
    1, // On
};
const static int32_t MAX_LENS_MOD_ENABLE_SUPPORT[] = {
    MODEL_12, // Off
    MODEL_12, // On
};
#pragma endregion

#pragma region Easy Night Photo
#define EASY_NIGHT_PHOTO_ID 191
#define EASY_NIGHT_PHOTO_SIZE 3
#define EASY_NIGHT_PHOTO_NAME "Easy Night Photo"
#define EASY_NIGHT_PHOTO_AVA MODEL_13|MODEL_12
const static char* EASY_NIGHT_PHOTO_STRING[] = {
    "Single Photo",
    "Night Photo",
    "Burst",
};
const static int32_t EASY_NIGHT_PHOTO_VALUE[] = {
    0, // Single Photo
    1, // Night Photo
    2, // Burst
};
const static int32_t EASY_NIGHT_PHOTO_SUPPORT[] = {
    MODEL_13|MODEL_12, // Single Photo
    MODEL_13|MODEL_12, // Night Photo
    MODEL_13, // Burst
};
#pragma endregion

#pragma region Multi Shot Aspect Ratio
#define MULTI_SHOT_ASPECT_RATIO_ID 192
#define MULTI_SHOT_ASPECT_RATIO_SIZE 4
#define MULTI_SHOT_ASPECT_RATIO_NAME "Multi Shot Aspect Ratio"
#define MULTI_SHOT_ASPECT_RATIO_AVA MODEL_13|MODEL_12
const static char* MULTI_SHOT_ASPECT_RATIO_STRING[] = {
    "4:3",
    "16:9",
    "8:7",
    "9:16",
};
const static int32_t MULTI_SHOT_ASPECT_RATIO_VALUE[] = {
    0, // 4:3
    1, // 16:9
    3, // 8:7
    4, // 9:16
};
const static int32_t MULTI_SHOT_ASPECT_RATIO_SUPPORT[] = {
    MODEL_13|MODEL_12, // 4:3
    MODEL_13|MODEL_12, // 16:9
    MODEL_13|MODEL_12, // 8:7
    MODEL_13, // 9:16
};
#pragma endregion

#pragma region Framing
#define FRAMING_ID 193
#define FRAMING_SIZE 9
#define FRAMING_NAME "Framing"
#define FRAMING_AVA MODEL_13|MODEL_12
const static char* FRAMING_STRING[] = {
    "Widescreen",
    "Vertical",
    "Full Frame",
    "Traditional 4:3 v2",
    "Widescreen 16:9 v2",
    "Full Frame 8:7 v2",
    "Vertical 9:16 v2",
    "Ultra Widescreen 21:9 v2",
    "Full Frame 1:1 v2",
};
const static int32_t FRAMING_VALUE[] = {
    0, // Widescreen
    1, // Vertical
    2, // Full Frame
    100, // Traditional 4:3 v2
    101, // Widescreen 16:9 v2
    103, // Full Frame 8:7 v2
    104, // Vertical 9:16 v2
    105, // Ultra Widescreen 21:9 v2
    106, // Full Frame 1:1 v2
};
const static int32_t FRAMING_SUPPORT[] = {
    MODEL_12, // Widescreen
    MODEL_12, // Vertical
    MODEL_12, // Full Frame
    MODEL_13, // Traditional 4:3 v2
    MODEL_13, // Widescreen 16:9 v2
    MODEL_13, // Full Frame 8:7 v2
    MODEL_13, // Vertical 9:16 v2
    MODEL_13, // Ultra Widescreen 21:9 v2
    MODEL_13, // Full Frame 1:1 v2
};
#pragma endregion

#pragma region Camera Mode
#define CAMERA_MODE_ID 194
#define CAMERA_MODE_SIZE 2
#define CAMERA_MODE_NAME "Camera Mode"
#define CAMERA_MODE_AVA MODEL_MISSION|MODEL_MAX2
const static char* CAMERA_MODE_STRING[] = {
    "Single Lens",
    "360", 
};
const static int32_t CAMERA_MODE_VALUE[] = {
    0, // Single Lens
    1, // 360"
};
const static int32_t CAMERA_MODE_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2, // Single Lens
    MODEL_MISSION|MODEL_MAX2, // 360"
};
#pragma endregion

#pragma region _360 Photo files extension
#define _360_PHOTO_FILES_EXTENSION_ID 196
#define _360_PHOTO_FILES_EXTENSION_SIZE 2
#define _360_PHOTO_FILES_EXTENSION_NAME "360 Photo Files Extension"
#define _360_PHOTO_FILES_EXTENSION_AVA MODEL_MISSION|MODEL_MAX2
const static char* _360_PHOTO_FILES_EXTENSION_STRING[] = {
    ".360",
    ".jpg",
};
const static int32_t _360_PHOTO_FILES_EXTENSION_VALUE[] = {
    0, // .360
    1, // .jpg
};
const static int32_t _360_PHOTO_FILES_EXTENSION_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2, // .360
    MODEL_MISSION|MODEL_MAX2, // .jpg
};
#pragma endregion

#pragma region Beep Volume
#define BEEP_VOLUME_ID 216
#define BEEP_VOLUME_SIZE 3
#define BEEP_VOLUME_NAME "Beep Volume"
#define BEEP_VOLUME_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13
const static char* BEEP_VOLUME_STRING[] = {
    "Low",
    "Medium",
    "High",
};
const static int32_t BEEP_VOLUME_VALUE[] = {
    70, // Low
    85, // Medium
    100, // High
};
const static int32_t BEEP_VOLUME_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Low
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Medium
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // High
};
#pragma endregion

#pragma region Setup Screen Saver
#define SETUP_SCREEN_SAVER_ID 219
#define SETUP_SCREEN_SAVER_SIZE 5
#define SETUP_SCREEN_SAVER_NAME "Setup Screen Saver"
#define SETUP_SCREEN_SAVER_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13
const static char* SETUP_SCREEN_SAVER_STRING[] = {
    "Never",
    "1 Min",
    "2 Min",
    "3 Min",
    "5 Min",
};
const static int32_t SETUP_SCREEN_SAVER_VALUE[] = {
    0, // Never
    1, // 1 Min
    2, // 2 Min
    3, // 3 Min
    4, // 5 Min
};
const static int32_t SETUP_SCREEN_SAVER_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2, // Never
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 1 Min
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 2 Min
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 3 Min
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 5 Min
};
#pragma endregion

#pragma region Setup Language
#define SETUP_LANGUAGE_ID 223
#define SETUP_LANGUAGE_SIZE 15
#define SETUP_LANGUAGE_NAME "Setup Language"
#define SETUP_LANGUAGE_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13
const static char* SETUP_LANGUAGE_STRING[] = {
    "English - US",
    "English - UK",
    "English - AUS",
    "German",
    "French",
    "Italian",
    "Spanish",
    "Spanish - NA",
    "Chinese",
    "Japanese",
    "Korean",
    "Portuguese",
    "Russian",
    "English - IND",
    "Swedish",
};
const static int32_t SETUP_LANGUAGE_VALUE[] = {
    0, // English - US
    1, // English - UK
    2, // English - AUS
    3, // German
    4, // French
    5, // Italian
    6, // Spanish
    7, // Spanish - NA
    8, // Chinese
    9, // Japanese
    10, // Korean
    11, // Portuguese
    12, // Russian
    13, // English - IND
    14, // Swedish
};
const static int32_t SETUP_LANGUAGE_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // English - US
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // English - UK
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // English - AUS
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // German
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // French
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Italian
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Spanish
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Spanish - NA
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Chinese
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Japanese
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Korean
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Portuguese
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Russian
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // English - IND
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Swedish
};
#pragma endregion

#pragma region Photo Mode
#define PHOTO_MODE_ID 227
#define PHOTO_MODE_SIZE 3
#define PHOTO_MODE_NAME "Photo Mode"
#define PHOTO_MODE_AVA MODEL_13
const static char* PHOTO_MODE_STRING[] = {
    "Super Photo",
    "Night Photo",
    "Burst",
};
const static int32_t PHOTO_MODE_VALUE[] = {
    0, // Super Photo
    1, // Night Photo
    2, // Burst
};
const static int32_t PHOTO_MODE_SUPPORT[] = {
    MODEL_13, // Super Photo
    MODEL_13, // Night Photo
    MODEL_13, // Burst
};
#pragma endregion

#pragma region Video Framing
#define VIDEO_FRAMING_ID 232
#define VIDEO_FRAMING_SIZE 6
#define VIDEO_FRAMING_NAME "Video Framing"
#define VIDEO_FRAMING_AVA MODEL_13
const static char* VIDEO_FRAMING_STRING[] = {
    "4:3",
    "16:9",
    "8:7",
    "9:16",
    "21:9",
    "1:1",
};
const static int32_t VIDEO_FRAMING_VALUE[] = {
    0, // 4:3
    1, // 16:9
    3, // 8:7
    4, // 9:16
    5, // 21:9
    6, // 1:1
};
const static int32_t VIDEO_FRAMING_SUPPORT[] = {
    MODEL_13, // 4:3
    MODEL_13, // 16:9
    MODEL_13, // 8:7
    MODEL_13, // 9:16
    MODEL_13, // 21:9
    MODEL_13, // 1:1
};
#pragma endregion

#pragma region Multi Shot Framing
#define MULTISHOT_FRAMING_ID 233
#define MULTISHOT_FRAMING_SIZE 4
#define MULTISHOT_FRAMING_NAME "Multi Shot Framing"
#define MULTISHOT_FRAMING_AVA MODEL_13
const static char* MULTISHOT_FRAMING_STRING[] = {
    "4:3",
    "16:9",
    "8:7",
    "9:16",
};
const static int32_t MULTISHOT_FRAMING_VALUE[] = {
    0, // 4:3
    1, // 16:9
    3, // 8:7
    4, // 9:16
};
const static int32_t MULTISHOT_FRAMING_SUPPORT[] = {
    MODEL_13, // 4:3
    MODEL_13, // 16:9
    MODEL_13, // 8:7
    MODEL_13, // 9:16
};
#pragma endregion

#pragma region Frame Rate
#define FRAMERATE_ID 234
#define FRAMERATE_SIZE 6
#define FRAMERATE_NAME "Frame Rate"
#define FRAMERATE_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13
const static char* FRAMERATE_STRING[] = {
 	"240.0",
 	"120.0",
 	"100.0",
 	"90.0",
 	"60.0",
 	"50.0",
 	"30.0",
 	"25.0",
 	"24.0",
 	"200.0",
 	"400.0",
 	"360.0",
 	"300.0",
};
const static int32_t FRAMERATE_VALUE[] = {
    0, // 240.0
    1, // 120.0
    2, // 100.0
    3, // 90.0
    5, // 60.0
    6, // 50.0
    8, // 30.0
    9, // 25.0
    10, // 24.0
    13, // 200.0
    15, // 400.0
    16, // 360.0
    17, // 300.0
};
const static int32_t FRAMERATE_SUPPORT[] = {
    MODEL_13, // 240.0
    MODEL_13, // 120.0
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 100.0
    MODEL_MISSION|MODEL_MAX2, // 90.0
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 60.0
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 50.0
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 30.0
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 25.0
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // 24.0
    MODEL_13, // 200.0
    MODEL_13, // 400.0
    MODEL_13, // 360.0
    MODEL_13, // 300.0
};
#pragma endregion

#pragma region Automatic Wifi Access Point
#define AUTOMATIC_WI_FI_ACCESS_POINT_ID 236
#define AUTOMATIC_WI_FI_ACCESS_POINT_SIZE 2
#define AUTOMATIC_WI_FI_ACCESS_POINT_NAME "Automatic Wi-Fi Access Point"
#define AUTOMATIC_WI_FI_ACCESS_POINT_AVA MODEL_MISSION|MODEL_MAX2
const static char* AUTOMATIC_WI_FI_ACCESS_POINT_STRING[] = {
    "Off",
    "On",
};
const static int32_t AUTOMATIC_WI_FI_ACCESS_POINT_VALUE[] = {
    0,  // Off
    1, // On
};
const static int32_t AUTOMATIC_WI_FI_ACCESS_POINT_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2,  // Off
    MODEL_MISSION|MODEL_MAX2, // On
};
#pragma endregion

// Another Reference: https://github.com/KonradIT/goprowifihack/blob/master/HERO11/HERO11-Commands.md

#pragma region White Balance
#define WHITE_BALANCE_ID 115
#define WHITE_BALANCE_SIZE 11
#define WHITE_BALANCE_NAME "White Balance"
#define WHITE_BALANCE_AVA MODEL_MISSION_ALL
const static char* WHITE_BALANCE_STRING[] = {
    "Auto",
    "5500K",
    "6500K",
    "Native",
    "4000K",
    "6000K",
    "2300K",
    "2800K",
    "3200K",
    "4500K",
    "5000K",
};
const static int32_t WHITE_BALANCE_VALUE[] = {
    0, // Auto
    2, // 5500K
    3, // 6500K
    4, // Native
    5, // 4000K
    7, // 6000K
    8, // 2300K
    9, // 2800K
    10, // 3200K
    11, // 4500K
    12, // 5000K
};
const static int32_t WHITE_BALANCE_SUPPORT[] = {
    MODEL_MISSION_ALL, // Auto
    MODEL_MISSION_ALL, // 5500K
    MODEL_MISSION_ALL, // 6500K
    MODEL_MISSION_ALL, // Native
    MODEL_MISSION_ALL, // 4000K
    MODEL_MISSION_ALL, // 6000K
    MODEL_MISSION_ALL, // 2300K
    MODEL_MISSION_ALL, // 2800K
    MODEL_MISSION_ALL, // 3200K
    MODEL_MISSION_ALL, // 4500K
    MODEL_MISSION_ALL, // 5000K
};
#pragma endregion

#pragma region Sharpness
#define SHARPNESS_ID 117
#define SHARPNESS_SIZE 3
#define SHARPNESS_NAME "Sharpness"
#define SHARPNESS_AVA MODEL_MISSION_ALL
const static char* SHARPNESS_STRING[] = {
    "High",
    "Midium",
    "Low"
};
const static int32_t SHARPNESS_VALUE[] = {
    0, // High
    1, // Midium
    2, // Lo
};
const static int32_t SHARPNESS_SUPPORT[] = {
    MODEL_MISSION_ALL, // High
    MODEL_MISSION_ALL, // Midium
    MODEL_MISSION_ALL, // Lo
};
#pragma endregion

#pragma region Denoise
#define DENOISE_ID 198
#define DENOISE_SIZE 3
#define DENOISE_NAME "Denoise"
#define DENOISE_AVA MODEL_MISSION|MODEL_MAX2|MODEL_13
const static char* DENOISE_STRING[] = {
    "High",
    "Midium",
    "Low",
};
const static int32_t DENOISE_VALUE[] = {
    2, // High
    1, // Midium
    0, // Low
};
const static int32_t DENOISE_SUPPORT[] = {
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // High
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Midium
    MODEL_MISSION|MODEL_MAX2|MODEL_13, // Low
};
#pragma endregio

#pragma region Exposure
#define EXPOSURE_ID 118
#define EXPOSURE_SIZE 9
#define EXPOSURE_NAME "EV Comp"
#define EXPOSURE_AVA MODEL_MISSION_ALL
const static char* EXPOSURE_STRING[] = {
    "-2.0",
    "-1.5",
    "-1.0",
    "-0.5",
    "0.0",
    "0.5",
    "1.0",
    "1.5",
    "2.0",
};
const static int32_t EXPOSURE_VALUE[] = {
    8, // -2.0
    7, // -1.5
    6, // -1.0
    5, // -0.5
    4, // 0.0
    3, // 0.5
    2, // 1.0
    1, // 1.5
    0, // 2.0
};
const static int32_t EXPOSURE_SUPPORT[] = {
    MODEL_MISSION_ALL, // -2.0
    MODEL_MISSION_ALL, // -1.5
    MODEL_MISSION_ALL, // -1.0
    MODEL_MISSION_ALL, // -0.5
    MODEL_MISSION_ALL, // 0.0
    MODEL_MISSION_ALL, // 0.5
    MODEL_MISSION_ALL, // 1.0
    MODEL_MISSION_ALL, // 1.5
    MODEL_MISSION_ALL, // 2.0
};
#pragma endregion

#pragma region Color
#define COLOR_ID 116
#define COLOR_SIZE 4
#define COLOR_NAME "Color"
#define COLOR_AVA MODEL_MISSION_ALL
const static char* COLOR_STRING[] = {
    "GP-LOG",
    "Vibrant",
    "Natural",
    "Flat",
};
const static int32_t COLOR_VALUE[] = {
    101, // GP-LOP
    100, // Vibrant
    2, // Natural
    1, // Flat
};
const static int32_t COLOR_SUPPORT[] = {
    MODEL_MISSION_ALL, // GP-LOP
    MODEL_MISSION_ALL, // Vibrant
    MODEL_MISSION_ALL, // Natural
    MODEL_MISSION_ALL, // Flat
};
#pragma endregion

#pragma region ISO Min Video
#define ISO_MIN_VIDEO_ID 102
#define ISO_MIN_VIDEO_SIZE 8
#define ISO_MIN_VIDEO_NAME "ISO Minimum"
#define ISO_MIN_VIDEO_AVA MODEL_MISSION_ALL
const static char* ISO_MIN_VIDEO_STRING[] = {
    "6400",
    "1600",
    "400",
    "3200",
    "800",
    "200",
    "100",
    "Auto",
};
const static int32_t ISO_MIN_VIDEO_VALUE[] = {
    0, // 6400
    1, // 1600
    2, // 400
    3, // 3200
    4, // 800
    7, // 200
    8, // 100
    9, // Auto
};
const static int32_t ISO_MIN_VIDEO_SUPPORT[] = {
    MODEL_MISSION_ALL, // 6400
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 3200
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // Auto
};
#pragma endregion

#pragma region ISO Max Video
#define ISO_MAX_VIDEO_ID 13
#define ISO_MAX_VIDEO_SIZE 15
#define ISO_MAX_VIDEO_NAME "ISO Maximum"
#define ISO_MAX_VIDEO_AVA MODEL_MISSION_ALL
const static char* ISO_MAX_VIDEO_STRING[] = {
    "6400",
    "1600",
    "400",
    "3200",
    "800",
    "200",
    "100",
    "Auto",
    "25-6400",
    "25-3200",
    "25-1600",
    "25-800",
    "25-400",
    "25-200",
    "25-100",
};
const static int32_t ISO_MAX_VIDEO_VALUE[] = {
    0, // 6400
    1, // 1600
    2, // 400
    3, // 3200
    4, // 800
    7, // 200
    8, // 100
    9, // Auto
    101, // 25-6400
    102, // 25-3200
    103, // 25-1600
    104, // 25-800
    105, // 25-400
    106, // 25-200
    107, // 25-100
};
const static int32_t ISO_MAX_VIDEO_SUPPORT[] = {
    MODEL_MISSION_ALL, // 6400
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 3200
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // Auto
    MODEL_MISSION, // 25-6400
    MODEL_MISSION, // 25-3200
    MODEL_MISSION, // 25-1600
    MODEL_MISSION, // 25-800
    MODEL_MISSION, // 25-400
    MODEL_MISSION, // 25-200
    MODEL_MISSION, // 25-100
};
#pragma endregion

#pragma region ISO Min Photo
#define ISO_MIN_PHOTO_ID 75
#define ISO_MIN_PHOTO_SIZE 6
#define ISO_MIN_PHOTO_NAME "ISO Minimum"
#define ISO_MIN_PHOTO_AVA MODEL_MISSION_ALL
const static char* ISO_MIN_PHOTO_STRING[] = {
    "800",
    "400",
    "200",
    "100",
    "1600",
    "3200",
};
const static int32_t ISO_MIN_PHOTO_VALUE[] = {
    0, // 800
    1, // 400
    2, // 200
    3, // 100
    4, // 1600
    5, // 3200
};
const static int32_t ISO_MIN_PHOTO_SUPPORT[] = {
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 3200
};
#pragma endregion

#pragma region ISO Max Photo
#define ISO_MAX_PHOTO_ID 24
#define ISO_MAX_PHOTO_SIZE 6
#define ISO_MAX_PHOTO_NAME "ISO Maximum"
#define ISO_MAX_PHOTO_AVA MODEL_MISSION_ALL
const static char* ISO_MAX_PHOTO_STRING[] = {
    "800",
    "400",
    "200",
    "100",
    "1600",
    "3200",
};
const static int32_t ISO_MAX_PHOTO_VALUE[] = {
    0, // 800
    1, // 400
    2, // 200
    3, // 100
    4, // 1600
    5, // 3200
};
const static int32_t ISO_MAX_PHOTO_SUPPORT[] = {
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 3200
};
#pragma endregion

#pragma region ISO Min Brust
#define ISO_MIN_BURST_ID 76
#define ISO_MIN_BURST_SIZE 6
#define ISO_MIN_BURST_NAME "ISO Minimum"
#define ISO_MIN_BURST_AVA MODEL_MISSION_ALL
const static char* ISO_MIN_BURST_STRING[] = {
    "800",
    "400",
    "200",
    "100",
    "1600",
    "3200",
};
const static int32_t ISO_MIN_BURST_VALUE[] = {
    0, // 800
    1, // 400
    2, // 200
    3, // 100
    4, // 1600
    5, // 3200
};
const static int32_t ISO_MIN_BURST_SUPPORT[] = {
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 3200
};
#pragma endregion

#pragma region ISO Max Burst
#define ISO_MAX_BURST_ID 37
#define ISO_MAX_BURST_SIZE 6
#define ISO_MAX_BURST_NAME "ISO Maximum"
#define ISO_MAX_BURST_AVA MODEL_MISSION_ALL
const static char* ISO_MAX_BURST_STRING[] = {
    "800",
    "400",
    "200",
    "100",
    "1600",
    "3200",
};
const static int32_t ISO_MAX_BURST_VALUE[] = {
    0, // 800
    1, // 400
    2, // 200
    3, // 100
    4, // 1600
    5, // 3200
};
const static int32_t ISO_MAX_BURST_SUPPORT[] = {
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 3200
};
#pragma endregion

#pragma region Shutter Speed Video
#define SHUTTER_SPEED_VIDEO_ID 145
#define SHUTTER_SPEED_VIDEO_SIZE 62
#define SHUTTER_SPEED_VIDEO_NAME "Shutter Speed"
#define SHUTTER_SPEED_VIDEO_AVA MODEL_MISSION_ALL
const static char* SHUTTER_SPEED_VIDEO_STRING[] = {
    "Auto",
    "Auto Cinematic",
    "1/8640",
    "1/7680",
    "1/7200",
    "1/6400",
    "1/6144",
    "1/5760",
    "1/4800",
    "1/4608",
    "1/4320",
    "1/3840",
    "1/3600",
    "1/3200",
    "1/3072",
    "1/2880",
    "1/2400",
    "1/2304",
    "1/2160",
    "1/1920",
    "1/1800",
    "1/1600",
    "1/1536",
    "1/1440",
    "1/1200",
    "1/1152",
    "1/1080",
    "1/960",
    "1/900",
    "1/800",
    "1/768",
    "1/720",
    "1/600",
    "1/576",
    "1/540",
    "1/480",
    "1/450",
    "1/400",
    "1/384",
    "1/360",
    "1/300",
    "1/288",
    "1/240",
    "1/200",
    "1/192",
    "1/180",
    "1/150",
    "1/144",
    "1/120",
    "1/100",
    "1/96",
    "1/90",
    "1/75",
    "1/72",
    "1/60",
    "1/50",
    "1/48",
    "1/45",
    "1/36",
    "1/30",
    "1/25",
    "1/24",
};
const static int32_t SHUTTER_SPEED_VIDEO_VALUE[] = {
    0, // "Auto
    57, // "Auto Cinematic
    67, // 1/8640
    56, // 1/7680
    66, // 1/7200
    51, // 1/6400
    43, // 1/6144
    55, // 1/5760
    50, // 1/4800
    42, // 1/4608
    65, // 1/4320
    31, // 1/3840
    64, // 1/3600
    30, // 1/3200
    34, // 1/3072
    54, // 1/2880
    49, // 1/2400
    41, // 1/2304
    63, // 1/2160
    24, // 1/1920
    62, // 1/1800
    29, // 1/1600
    33, // 1/1536
    53, // 1/1440
    48, // 1/1200
    40, // 1/1152
    61, // 1/1080
    23, // 1/960
    60, // 1/900
    28, // 1/800
    32, // 1/768
    27, // 1/720
    47, // 1/600
    39, // 1/576
    59, // 1/540
    22, // 1/480
    58, // 1/450
    21, // 1/400
    25, // 1/384
    20, // 1/360
    46, // 1/300
    38, // 1/288
    18, // 1/240
    17, // 1/200
    16, // 1/192
    15, // 1/180
    45, // 1/150
    37, // 1/144
    13, // 1/120
    12, // 1/100
    11, // 1/96
    10, // 1/90
    44, // 1/75
    36, // 1/72
    8, // 1/60
    7, // 1/50
    6, // 1/48
    52, // 1/45
    35, // 1/36
    5, // 1/30
    4, // 1/25
    3, // 1/24
};
const static int32_t SHUTTER_SPEED_VIDEO_SUPPORT[] = {
    MODEL_MISSION_ALL, // "Auto
    MODEL_MISSION_ALL, // "Auto Cinematic
    MODEL_MISSION_ALL, // 1/8640
    MODEL_MISSION_ALL, // 1/7680
    MODEL_MISSION_ALL, // 1/7200
    MODEL_MISSION_ALL, // 1/6400
    MODEL_MISSION_ALL, // 1/6144
    MODEL_MISSION_ALL, // 1/5760
    MODEL_MISSION_ALL, // 1/4800
    MODEL_MISSION_ALL, // 1/4608
    MODEL_MISSION_ALL, // 1/4320
    MODEL_MISSION_ALL, // 1/3840
    MODEL_MISSION_ALL, // 1/3600
    MODEL_MISSION_ALL, // 1/3200
    MODEL_MISSION_ALL, // 1/3072
    MODEL_MISSION_ALL, // 1/2880
    MODEL_MISSION_ALL, // 1/2400
    MODEL_MISSION_ALL, // 1/2304
    MODEL_MISSION_ALL, // 1/2160
    MODEL_MISSION_ALL, // 1/1920
    MODEL_MISSION_ALL, // 1/1800
    MODEL_MISSION_ALL, // 1/1600
    MODEL_MISSION_ALL, // 1/1536
    MODEL_MISSION_ALL, // 1/1440
    MODEL_MISSION_ALL, // 1/1200
    MODEL_MISSION_ALL, // 1/1152
    MODEL_MISSION_ALL, // 1/1080
    MODEL_MISSION_ALL, // 1/960
    MODEL_MISSION_ALL, // 1/900
    MODEL_MISSION_ALL, // 1/800
    MODEL_MISSION_ALL, // 1/768
    MODEL_MISSION_ALL, // 1/720
    MODEL_MISSION_ALL, // 1/600
    MODEL_MISSION_ALL, // 1/576
    MODEL_MISSION_ALL, // 1/540
    MODEL_MISSION_ALL, // 1/480
    MODEL_MISSION_ALL, // 1/450
    MODEL_MISSION_ALL, // 1/400
    MODEL_MISSION_ALL, // 1/384
    MODEL_MISSION_ALL, // 1/360
    MODEL_MISSION_ALL, // 1/300
    MODEL_MISSION_ALL, // 1/288
    MODEL_MISSION_ALL, // 1/240
    MODEL_MISSION_ALL, // 1/200
    MODEL_MISSION_ALL, // 1/192
    MODEL_MISSION_ALL, // 1/180
    MODEL_MISSION_ALL, // 1/150
    MODEL_MISSION_ALL, // 1/144
    MODEL_MISSION_ALL, // 1/120
    MODEL_MISSION_ALL, // 1/100
    MODEL_MISSION_ALL, // 1/96
    MODEL_MISSION_ALL, // 1/90
    MODEL_MISSION_ALL, // 1/75
    MODEL_MISSION_ALL, // 1/72
    MODEL_MISSION_ALL, // 1/60
    MODEL_MISSION_ALL, // 1/50
    MODEL_MISSION_ALL, // 1/48
    MODEL_MISSION_ALL, // 1/45
    MODEL_MISSION_ALL, // 1/36
    MODEL_MISSION_ALL, // 1/30
    MODEL_MISSION_ALL, // 1/25
    MODEL_MISSION_ALL, // 1/24
};
#pragma endregion

#pragma region Shutter Speed Photo
#define SHUTTER_SPEED_PHOTO_ID 146
#define SHUTTER_SPEED_PHOTO_SIZE 7
#define SHUTTER_SPEED_PHOTO_NAME "Shutter Speed"
#define SHUTTER_SPEED_PHOTO_AVA MODEL_MISSION_ALL
const static char* SHUTTER_SPEED_PHOTO_STRING[] = {
    "Auto",
    "Auto Cinematic",
    "1/125",
    "1/250",
    "1/500",
    "1/1000",
    "1/2000",
};
const static int32_t SHUTTER_SPEED_PHOTO_VALUE[] = {
    0, // Auto
    6, // Auto Cinematic
    1, // 1/125
    2, // 1/250
    3, // 1/500
    4, // 1/1000
    5, // 1/2000
};
const static int32_t SHUTTER_SPEED_PHOTO_SUPPORT[] = {
    MODEL_MISSION_ALL, // Auto
    MODEL_MISSION_ALL, // Auto Cinematic
    MODEL_MISSION_ALL, // 1/125
    MODEL_MISSION_ALL, // 1/250
    MODEL_MISSION_ALL, // 1/500
    MODEL_MISSION_ALL, // 1/1000
    MODEL_MISSION_ALL, // 1/2000
};
#pragma endregion

#pragma region Photo Burst Rate
#define PHOTO_BURST_RATE_ID 147
#define PHOTO_BURST_RATE_SIZE 10
#define PHOTO_BURST_RATE_NAME "Photo Burst Rate"
#define PHOTO_BURST_RATE_AVA MODEL_MISSION_ALL
const static char* PHOTO_BURST_RATE_STRING[] = {
    "60 Photos / 10 Seconds",
    "60 Photos / 6 Seconds",
    "30 Photos / 6 Seconds",
    "30 Photos / 3 Seconds",
    "30 Photos / 1 Second",
    "10 Photos / 3 Seconds",
    "10 Photos / 1 Second",
    "5 Photos / 1 Second",
    "3 Photos / 1 Second",
    "Auto",
};
const static int32_t PHOTO_BURST_RATE_VALUE[] = {
    13, // 60 Photos / 10 Seconds
    12, // 60 Photos / 6 Seconds
    8, // 30 Photos / 6 Seconds
    7, // 30 Photos / 3 Seconds
    5, // 30 Photos / 1 Second
    4, // 10 Photos / 3 Seconds
    2, // 10 Photos / 1 Second
    1, // 5 Photos / 1 Second
    0, // 3 Photos / 1 Second
    9, // Auto
};
const static int32_t PHOTO_BURST_RATE_SUPPORT[] = {
    MODEL_MISSION_ALL, // 60 Photos / 10 Seconds
    MODEL_MISSION_ALL, // 60 Photos / 6 Seconds
    MODEL_MISSION_ALL, // 30 Photos / 6 Seconds
    MODEL_MISSION_ALL, // 30 Photos / 3 Seconds
    MODEL_MISSION_ALL, // 30 Photos / 1 Second
    MODEL_MISSION_ALL, // 10 Photos / 3 Seconds
    MODEL_MISSION_ALL, // 10 Photos / 1 Second
    MODEL_MISSION_ALL, // 5 Photos / 1 Second
    MODEL_MISSION_ALL, // 3 Photos / 1 Second
    MODEL_MISSION_ALL, // Auto
};
#pragma endregion

#pragma region ISO Auto
#define ISO_AUTO_ID 259
#define ISO_AUTO_SIZE 3
#define ISO_AUTO_NAME "ISO Auto"
#define ISO_AUTO_AVA MODEL_MISSION
const static char* ISO_AUTO_STRING[] = {
    "Auto",
    "Const",
    "Range"
};
const static int32_t ISO_AUTO_VALUE[] = {
    0,
    1,
    2,
};
const static int32_t ISO_AUTO_SUPPORT[] = {
    MODEL_MISSION,
    MODEL_MISSION,
    MODEL_MISSION,
};
#pragma endregion

#pragma region ISO Both Video (Virtual)
#define ISO_BOTH_VIDEO_ID 10000
#define ISO_BOTH_VIDEO_SIZE 8
#define ISO_BOTH_VIDEO_NAME "ISO Both"
#define ISO_BOTH_VIDEO_AVA MODEL_MISSION_ALL
const static char* ISO_BOTH_VIDEO_STRING[] = {
    "6400",
    "1600",
    "400",
    "3200",
    "800",
    "200",
    "100",
    "Auto",
};
const static int32_t ISO_BOTH_VIDEO_VALUE[] = {
    0, // 6400
    1, // 1600
    2, // 400
    3, // 3200
    4, // 800
    7, // 200
    8, // 100
    9, // Auto
};
const static int32_t ISO_BOTH_VIDEO_SUPPORT[] = {
    MODEL_MISSION_ALL, // 6400
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 3200
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // Auto
};
#pragma endregion

#pragma region ISO Both Photo (Virtual)
#define ISO_BOTH_PHOTO_ID 10001
#define ISO_BOTH_PHOTO_SIZE 6
#define ISO_BOTH_PHOTO_NAME "ISO BOTH"
#define ISO_BOTH_PHOTO_AVA MODEL_MISSION_ALL
const static char* ISO_BOTH_PHOTO_STRING[] = {
    "800",
    "400",
    "200",
    "100",
    "1600",
    "3200",
};
const static int32_t ISO_BOTH_PHOTO_VALUE[] = {
    0, // 800
    1, // 400
    2, // 200
    3, // 100
    4, // 1600
    5, // 3200
};
const static int32_t ISO_BOTH_PHOTO_SUPPORT[] = {
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 3200
};
#pragma endregion

#pragma region ISO Both Burst (Virtual)
#define ISO_BOTH_BURST_ID 10002
#define ISO_BOTH_BURST_SIZE 6
#define ISO_BOTH_BURST_NAME "ISO BOTH"
#define ISO_BOTH_BURST_AVA MODEL_MISSION_ALL
const static char* ISO_BOTH_BURST_STRING[] = {
    "800",
    "400",
    "200",
    "100",
    "1600",
    "3200",
};
const static int32_t ISO_BOTH_BURST_VALUE[] = {
    0, // 800
    1, // 400
    2, // 200
    3, // 100
    4, // 1600
    5, // 3200
};
const static int32_t ISO_BOTH_BURST_SUPPORT[] = {
    MODEL_MISSION_ALL, // 800
    MODEL_MISSION_ALL, // 400
    MODEL_MISSION_ALL, // 200
    MODEL_MISSION_ALL, // 100
    MODEL_MISSION_ALL, // 1600
    MODEL_MISSION_ALL, // 3200
};
#pragma endregion

#endif