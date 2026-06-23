/*
* Copyright (c) [2026] [Elly/Funique]
*
* This software is licensed under the [MIT License].
* See the LICENSE file in the project root for more information.
* 
* AUTO-GENERATED FILE - DO NOT EDIT MANUALLY
* Generated from GoPro OpenGoPro HTTP API Documentation
* Source: gopro_settings.json
*/
#pragma once
#ifndef CAMERACODE_GENERATED_H
#define CAMERACODE_GENERATED_H
#include <cinttypes>
#include "camera_setting.h"
#include "camera_status.h"
#include "camera_other.h"

/**
 * Things must be register here, to the converter works
 */
const static int32_t GOPRO_SETTING_IDS[] = {
    PHOTO_BURST_RATE_ID,
    VIDEO_RESOLUTION_ID,
    FRAMES_PER_SECOND_ID,
    VIDEO_LENS_ID,
    VIDEO_ASPECT_RATIO_ID,
    BIT_DEPTH_ID,
    VIDEO_BIT_RATE_ID,
    PHOTO_LENS_ID,
    PHOTO_OUTPUT_ID,
    VIDEO_TIMELAPSE_RATE_ID,
    PHOTO_TIMELAPSE_RATE_ID,
    NIGHTLAPSE_RATE_ID,
    WEBCAM_DIGITAL_LENSES_ID,
    AUTO_POWER_DOWN_ID,
    GPS_ID,
    HLG_ID,
    LCD_BRIGHTNESS_ID,
    LED_ID,
    TIME_LAPSE_DIGITAL_LENSES_ID,
    MEDIA_FORMAT_ID,
    ANTI_FLICKER_ID,
    ANTI_FLICKER_V2_ID,
    HYPERSMOOTH_ID,
    VIDEO_HORIZON_LEVELING_ID,
    PHOTO_HORIZON_LEVELING_ID,
    VIDEO_DURATION_ID,
    MULTISHOT_DURATION_ID,
    MAX_LENS_ID,
    HINDSIGHT_ID,
    PHOTO_SINGLE_INTERVAL_ID,
    PHOTO_SINGLE_DURATION_ID,
    VIDEO_PERFORMANCE_MODE_ID,
    CONTROL_MODE_ID,
    EASY_MODE_SPEED_ID,
    ENABLE_NIGHT_PHOTO_ID,
    WIRELESS_BAND_ID,
    STAR_TRAILS_LENGTH_ID,
    SYSTEM_VIDEO_MODE_ID,
    PROFILES_ID,
    VIDEO_EASY_MODE_ID,
    LAPSE_MODE_ID,
    MAX_LENS_MOD_ID,
    MAX_LENS_MOD_ENABLE_ID,
    EASY_NIGHT_PHOTO_ID,
    MULTI_SHOT_ASPECT_RATIO_ID,
    FRAMING_ID,
    CAMERA_MODE_ID,
    _360_PHOTO_FILES_EXTENSION_ID,
    BEEP_VOLUME_ID,
    SETUP_SCREEN_SAVER_ID,
    VIDEO_FRAMING_ID,
    AUTOMATIC_WI_FI_ACCESS_POINT_ID,
    WHITE_BALANCE_ID,
    SHARPNESS_ID,
    DENOISE_ID,
    EXPOSURE_ID,
    COLOR_ID,
    ISO_MIN_VIDEO_ID,
    ISO_MAX_VIDEO_ID,
    ISO_MIN_PHOTO_ID,
    ISO_MAX_PHOTO_ID,
    ISO_MIN_BURST_ID,
    ISO_MAX_BURST_ID,
    SHUTTER_SPEED_VIDEO_ID,
    SHUTTER_SPEED_PHOTO_ID,
    SHOT_COUNTDOWN_ID,
    ISO_BOTH_VIDEO_ID,
    ISO_BOTH_PHOTO_ID,
    ISO_BOTH_BURST_ID,
    ISO_AUTO_ID,
};
#define GOPRO_SETTING_SIZE sizeof(GOPRO_SETTING_IDS)/sizeof(int32_t)

const static int32_t GOPRO_SYSTEM_SETTING_IDS[] = {
    CONTROL_MODE_ID,
    AUTO_POWER_DOWN_ID,
    GPS_ID,
    LCD_BRIGHTNESS_ID,
    LED_ID,
    WIRELESS_BAND_ID,
    BEEP_VOLUME_ID,
    ANTI_FLICKER_ID,
    ANTI_FLICKER_V2_ID,
    SETUP_SCREEN_SAVER_ID,
    AUTOMATIC_WI_FI_ACCESS_POINT_ID,
};
#define GOPRO_SYSTEM_SETTING_SIZE sizeof(GOPRO_SYSTEM_SETTING_IDS)/sizeof(int32_t)

const static int32_t GOPRO_VIDEO_SETTING_IDS[] = {
    // Header
    PROFILES_ID,
    HLG_ID,
    VIDEO_ASPECT_RATIO_ID,
    VIDEO_RESOLUTION_ID,
    FRAMES_PER_SECOND_ID,
    VIDEO_LENS_ID,
    HYPERSMOOTH_ID,
    // Detail
    // VIDEO_FRAMING_ID,
    //SYSTEM_VIDEO_MODE_ID,
    VIDEO_PERFORMANCE_MODE_ID,
    VIDEO_EASY_MODE_ID,
};
#define GOPRO_VIDEO_SETTING_SIZE sizeof(GOPRO_VIDEO_SETTING_IDS)/sizeof(int32_t)

const static int32_t GOPRO_VIDEO_PROTUNE_SETTING_IDS[] = {
    //BIT_DEPTH_ID,
    VIDEO_BIT_RATE_ID,
    SHUTTER_SPEED_VIDEO_ID,

    EXPOSURE_ID,
    WHITE_BALANCE_ID,
    ISO_AUTO_ID,
    ISO_MIN_VIDEO_ID,
    ISO_MAX_VIDEO_ID,
    SHARPNESS_ID,
    DENOISE_ID,
    COLOR_ID,
};
#define GOPRO_VIDEO_PROTUNE_SETTING_SIZE sizeof(GOPRO_VIDEO_PROTUNE_SETTING_IDS)/sizeof(int32_t)

const static int32_t GOPRO_PHOTO_SETTING_IDS[] = {
    // Header
    PHOTO_LENS_ID,
    ENABLE_NIGHT_PHOTO_ID,
    // Detail
    PHOTO_OUTPUT_ID,
    SHOT_COUNTDOWN_ID,
    // FRAMING_ID
    PHOTO_HORIZON_LEVELING_ID,
    PHOTO_SINGLE_INTERVAL_ID,
    ENABLE_NIGHT_PHOTO_ID,
};
#define GOPRO_PHOTO_SETTING_SIZE sizeof(GOPRO_PHOTO_SETTING_IDS)/sizeof(int32_t)

const static int32_t GOPRO_PHOTO_PROTUNE_SETTING_IDS[] = {
    SHUTTER_SPEED_PHOTO_ID,
    EXPOSURE_ID,
    WHITE_BALANCE_ID,
    ISO_MIN_PHOTO_ID,
    ISO_MAX_PHOTO_ID,
    SHARPNESS_ID,
    DENOISE_ID,
    COLOR_ID,
};
#define GOPRO_PHOTO_PROTUNE_SETTING_SIZE sizeof(GOPRO_PHOTO_PROTUNE_SETTING_IDS)/sizeof(int32_t)

const static int32_t GOPRO_BURST_SETTING_IDS[] = {
    // Header
    PHOTO_LENS_ID,
    ENABLE_NIGHT_PHOTO_ID,
    // Detail
    BURST_OUTPUT_ID,
    PHOTO_BURST_RATE_ID,
    SHOT_COUNTDOWN_ID,
    // FRAMING_ID
    PHOTO_HORIZON_LEVELING_ID,
    PHOTO_SINGLE_INTERVAL_ID,
    ENABLE_NIGHT_PHOTO_ID,
};
#define GOPRO_BURST_SETTING_SIZE sizeof(GOPRO_BURST_SETTING_IDS)/sizeof(int32_t)

const static int32_t GOPRO_BURST_PROTUNE_SETTING_IDS[] = {
    SHUTTER_SPEED_PHOTO_ID,
    EXPOSURE_ID,
    WHITE_BALANCE_ID,
    ISO_MIN_BURST_ID,
    ISO_MAX_BURST_ID,
    SHARPNESS_ID,
    DENOISE_ID,
    COLOR_ID,
};
#define GOPRO_BURST_PROTUNE_SETTING_SIZE sizeof(GOPRO_BURST_PROTUNE_SETTING_IDS)/sizeof(int32_t)

const static int32_t GOPRO_STATUS_IDS[] = {
    BATTERY_PRESENT_ID,
    INTERNAL_BATTERY_BARS_ID,
    OVERHEATING_ID,
    BUSY_ID,
    QUICK_CAPTURE_ID,
    ENCODING_ID,
    LCD_LOCK_ID,
    VIDEO_ENCODING_DURATION_ID,
    WIRELESS_CONNECTIONS_ENABLED_ID,
    PAIRING_STATE_ID,
    LAST_PAIRING_TYPE_ID,
    LAST_PAIRING_SUCESS_ID,
    WIFI_SCAN_STATE_ID,
    LAST_WIFI_SCAN_SUCESS_ID,
    WIFI_PROVISIONING_STATE_ID,
    REMOTE_VERSION_ID,
    REMOTE_CONNECTED_ID,
    CONNECTED_WIFI_SSID_ID,
    ACCESS_POINT_SSID_ID,
    CONNECTED_DEVICE_ID,
    PREVIEW_STREAM_ID,
    PRIMARY_STORAGE_ID,
    REMAINING_PHOTOS_ID,
    REMAINING_VIDEO_TIME_ID,
    PHOTOS_ID,
    VIDEOS_ID,
    OTA_ID,
    PENDING_FW_UPDATE_CANCEL_ID,
    LOCATE_ID,
    TIMELAPSE_INTERVAL_COUNTDOWN_ID,
    SD_CARD_REMAINING_ID,
    PREVIEW_STREAM_AVAILABLE_ID,
    WIFI_BARS_ID,
    ACTIVE_HILIGHTS_ID,
    TIME_SINCE_LAST_HILIGHT_ID,
    MINIMUM_STATUS_POLL_PREIOD_ID,
    LIVEVIEW_EXPOSURE_SELECT_MODE_ID,
    LIVEVIEW_Y_ID,
    LIVEVIEW_X_ID,
    GPS_LOCK_ID,
    AP_MODE_ID,
    INTERNAL_BATTERY_PERCENTAGE_ID,
    MICROPHONE_ACCESSORY_ID,
    ZOOM_LEVEL_ID,
    STATUS_WIRELESS_BAND_ID,
    ZOOM_AVAILABLE_ID,
    MOBILE_FRIENDLY_ID,
    FTU_ID,
    _5GHZ_AVAILABLE_ID,
    READY_ID,
    OTA_CHANGED_ID,
    COLD_ID,
    ROTATION_ID,
    ZOOM_WHILE_ENCODING_ID,
    FLATMODE_ID,
    VIDEO_PRESET_ID,
    PHOTO_PRESET_ID,
    TIMELAPSE_PRESET_ID,
    PRESET_GROUP_ID,
    PRESET_ID,
    PRESET_MODIFIED_ID,
    REMAINING_LIVE_BURSTS_ID,
    LIVE_BURSTS_ID,
    CAPTURE_DELAY_ACTIVE_ID,
    MEDIA_MOD_STATE_ID,
    TIME_WARP_SPEED_ID,
    LINUX_CORE_ID,
    LENS_TYPE_ID,
    STATUS_HINDSIGHT_ID,
    SCHEDULED_CAPTURE_PRESET_ID,
    STATUS_SCHEDULED_CAPTURE_ID,
    SD_CARD_WRITE_SPEED_ERROR_ID,
    SD_CARD_ERRORS_ID,
    STATUS_CAMERA_CONTROL_ID,
    USB_CONNECTED_ID,
    USE_CONTROLLED_ID,
    SD_CARD_CAPACITY_ID,
    CAMERA_NAME_ID,
};
#define GOPRO_STATUS_SIZE sizeof(GOPRO_STATUS_IDS)/sizeof(int32_t)

const static int32_t GOPRO_SOFTWARE_STATUS_IDS[] = {
    PRESET_ID,
    LINUX_CORE_ID,
    LIVE_BURSTS_ID,
    VIDEO_PRESET_ID,
    PHOTO_PRESET_ID,
    TIMELAPSE_PRESET_ID,
    LIVEVIEW_EXPOSURE_SELECT_MODE_ID,
    LIVEVIEW_Y_ID,
    LIVEVIEW_X_ID,
};
#define GOPRO_SOFTWARE_STATUS_SIZE sizeof(GOPRO_SOFTWARE_STATUS_IDS)/sizeof(int32_t)

const static int32_t GOPRO_HARDWARE_STATUS_IDS[] = {
    BATTERY_PRESENT_ID,
    INTERNAL_BATTERY_BARS_ID,
    OVERHEATING_ID,
    QUICK_CAPTURE_ID,
    LCD_LOCK_ID,
    INTERNAL_BATTERY_PERCENTAGE_ID,
    MICROPHONE_ACCESSORY_ID,
    USB_CONNECTED_ID,
    USE_CONTROLLED_ID,
};
#define GOPRO_HARDWARE_STATUS_SIZE sizeof(GOPRO_HARDWARE_STATUS_IDS)/sizeof(int32_t)

const static int32_t GOPRO_NETWORK_STATUS_IDS[] = {
    GPS_LOCK_ID,
    AP_MODE_ID,
};
#define GOPRO_NETWORK_STATUS_SIZE sizeof(GOPRO_NETWORK_STATUS_IDS)/sizeof(int32_t)

const static int32_t GOPRO_ENCODE_STATUS_IDS[] = {
    ENCODING_ID,
    BUSY_ID,
    VIDEO_ENCODING_DURATION_ID,
};
#define GOPRO_ENCODE_STATUS_SIZE sizeof(GOPRO_ENCODE_STATUS_IDS)/sizeof(int32_t)

const static int32_t GOPRO_MEDIA_STATUS_IDS[] = {
    SD_CARD_REMAINING_ID,
    SD_CARD_CAPACITY_ID,
};
#define GOPRO_MEDIA_STATUS_SIZE sizeof(GOPRO_MEDIA_STATUS_IDS)/sizeof(int32_t)

// Lookup functions
inline const int32_t GET_SETTING_SIZE_BY_ID(int32_t x) {
    switch(x) {
        case ISO_AUTO_ID                    : return ISO_AUTO_SIZE;
        case DENOISE_ID                     : return DENOISE_SIZE;
        case BURST_OUTPUT_ID                : return BURST_OUTPUT_SIZE;
        case PHOTO_BURST_RATE_ID            : return PHOTO_BURST_RATE_SIZE;
        case ISO_MIN_BURST_ID               : return ISO_MIN_BURST_SIZE;
        case ISO_MAX_BURST_ID               : return ISO_MAX_BURST_SIZE;
        case SHOT_COUNTDOWN_ID              : return SHOT_COUNTDOWN_SIZE;
        case VIDEO_RESOLUTION_ID            : return VIDEO_RESOLUTION_SIZE;
        case FRAMES_PER_SECOND_ID           : return FRAMES_PER_SECOND_SIZE;
        case VIDEO_LENS_ID                  : return VIDEO_LENS_SIZE;
        case VIDEO_ASPECT_RATIO_ID          : return VIDEO_ASPECT_RATIO_SIZE;
        case BIT_DEPTH_ID                   : return BIT_DEPTH_SIZE;
        case VIDEO_BIT_RATE_ID              : return VIDEO_BIT_RATE_SIZE;
        case PHOTO_LENS_ID                  : return PHOTO_LENS_SIZE;
        case PHOTO_OUTPUT_ID                : return PHOTO_OUTPUT_SIZE;
        case VIDEO_TIMELAPSE_RATE_ID        : return VIDEO_TIMELAPSE_RATE_SIZE;
        case PHOTO_TIMELAPSE_RATE_ID        : return PHOTO_TIMELAPSE_RATE_SIZE;
        case NIGHTLAPSE_RATE_ID             : return NIGHTLAPSE_RATE_SIZE;
        case WEBCAM_DIGITAL_LENSES_ID       : return WEBCAM_DIGITAL_LENSES_SIZE;
        case AUTO_POWER_DOWN_ID             : return AUTO_POWER_DOWN_SIZE;
        case GPS_ID                         : return GPS_SIZE;
        case HLG_ID                         : return HLG_SIZE;
        case LCD_BRIGHTNESS_ID              : return LCD_BRIGHTNESS_SIZE;
        case LED_ID                         : return LED_SIZE;
        case TIME_LAPSE_DIGITAL_LENSES_ID   : return TIME_LAPSE_DIGITAL_LENSES_SIZE;
        case MEDIA_FORMAT_ID                : return MEDIA_FORMAT_SIZE;
        case ANTI_FLICKER_ID                : return ANTI_FLICKER_SIZE;
        case HYPERSMOOTH_ID                 : return HYPERSMOOTH_SIZE;
        case VIDEO_HORIZON_LEVELING_ID      : return VIDEO_HORIZON_LEVELING_SIZE;
        case PHOTO_HORIZON_LEVELING_ID      : return PHOTO_HORIZON_LEVELING_SIZE;
        case VIDEO_DURATION_ID              : return VIDEO_DURATION_SIZE;
        case MULTISHOT_DURATION_ID          : return MULTISHOT_DURATION_SIZE;
        case MAX_LENS_ID                    : return MAX_LENS_SIZE;
        case HINDSIGHT_ID                   : return HINDSIGHT_SIZE;
        case PHOTO_SINGLE_INTERVAL_ID       : return PHOTO_SINGLE_INTERVAL_SIZE;
        case PHOTO_SINGLE_DURATION_ID       : return PHOTO_SINGLE_DURATION_SIZE;
        case VIDEO_PERFORMANCE_MODE_ID      : return VIDEO_PERFORMANCE_MODE_SIZE;
        case CONTROL_MODE_ID                : return CONTROL_MODE_SIZE;
        case EASY_MODE_SPEED_ID             : return EASY_MODE_SPEED_SIZE;
        case ENABLE_NIGHT_PHOTO_ID          : return ENABLE_NIGHT_PHOTO_SIZE;
        case WIRELESS_BAND_ID               : return WIRELESS_BAND_SIZE;
        case STAR_TRAILS_LENGTH_ID          : return STAR_TRAILS_LENGTH_SIZE;
        case SYSTEM_VIDEO_MODE_ID           : return SYSTEM_VIDEO_MODE_SIZE;
        case PROFILES_ID                    : return PROFILES_SIZE;
        case VIDEO_EASY_MODE_ID             : return VIDEO_EASY_MODE_SIZE;
        case LAPSE_MODE_ID                  : return LAPSE_MODE_SIZE;
        case MAX_LENS_MOD_ID                : return MAX_LENS_MOD_SIZE;
        case MAX_LENS_MOD_ENABLE_ID         : return MAX_LENS_MOD_ENABLE_SIZE;
        case EASY_NIGHT_PHOTO_ID            : return EASY_NIGHT_PHOTO_SIZE;
        case MULTI_SHOT_ASPECT_RATIO_ID     : return MULTI_SHOT_ASPECT_RATIO_SIZE;
        case FRAMING_ID                     : return FRAMING_SIZE;
        case CAMERA_MODE_ID                 : return CAMERA_MODE_SIZE;
        case _360_PHOTO_FILES_EXTENSION_ID  : return _360_PHOTO_FILES_EXTENSION_SIZE;
        case BEEP_VOLUME_ID                 : return BEEP_VOLUME_SIZE;
        case SETUP_SCREEN_SAVER_ID          : return SETUP_SCREEN_SAVER_SIZE;
        case VIDEO_FRAMING_ID               : return VIDEO_FRAMING_SIZE;
        case AUTOMATIC_WI_FI_ACCESS_POINT_ID: return AUTOMATIC_WI_FI_ACCESS_POINT_SIZE;
        case WHITE_BALANCE_ID               : return WHITE_BALANCE_SIZE;
        case SHARPNESS_ID                   : return SHARPNESS_SIZE;
        case EXPOSURE_ID                    : return EXPOSURE_SIZE;
        case COLOR_ID                       : return COLOR_SIZE;
        case ISO_MIN_VIDEO_ID               : return ISO_MIN_VIDEO_SIZE;
        case ISO_MAX_VIDEO_ID               : return ISO_MAX_VIDEO_SIZE;
        case ISO_MIN_PHOTO_ID               : return ISO_MIN_PHOTO_SIZE;
        case ISO_MAX_PHOTO_ID               : return ISO_MAX_PHOTO_SIZE;
        case SHUTTER_SPEED_VIDEO_ID         : return SHUTTER_SPEED_VIDEO_SIZE;
        case SHUTTER_SPEED_PHOTO_ID         : return SHUTTER_SPEED_PHOTO_SIZE;
             default                        : return 0;
    }
}

inline const int32_t GET_SETTING_AVA_BY_ID(int32_t x) {
    switch(x) {
        case ISO_AUTO_ID                    : return ISO_AUTO_AVA;
        case DENOISE_ID                     : return DENOISE_AVA;
        case BURST_OUTPUT_ID                : return BURST_OUTPUT_AVA;
        case PHOTO_BURST_RATE_ID            : return PHOTO_BURST_RATE_AVA;
        case ISO_MIN_BURST_ID               : return ISO_MIN_BURST_AVA;
        case ISO_MAX_BURST_ID               : return ISO_MAX_BURST_AVA;
        case SHOT_COUNTDOWN_ID              : return SHOT_COUNTDOWN_AVA;
        case VIDEO_RESOLUTION_ID            : return VIDEO_RESOLUTION_AVA;
        case FRAMES_PER_SECOND_ID           : return FRAMES_PER_SECOND_AVA;
        case VIDEO_LENS_ID                  : return VIDEO_LENS_AVA;
        case VIDEO_ASPECT_RATIO_ID          : return VIDEO_ASPECT_RATIO_AVA;
        case BIT_DEPTH_ID                   : return BIT_DEPTH_AVA;
        case VIDEO_BIT_RATE_ID              : return VIDEO_BIT_RATE_AVA;
        case PHOTO_LENS_ID                  : return PHOTO_LENS_AVA;
        case PHOTO_OUTPUT_ID                : return PHOTO_OUTPUT_AVA;
        case VIDEO_TIMELAPSE_RATE_ID        : return VIDEO_TIMELAPSE_RATE_AVA;
        case PHOTO_TIMELAPSE_RATE_ID        : return PHOTO_TIMELAPSE_RATE_AVA;
        case NIGHTLAPSE_RATE_ID             : return NIGHTLAPSE_RATE_AVA;
        case WEBCAM_DIGITAL_LENSES_ID       : return WEBCAM_DIGITAL_LENSES_AVA;
        case AUTO_POWER_DOWN_ID             : return AUTO_POWER_DOWN_AVA;
        case GPS_ID                         : return GPS_AVA;
        case HLG_ID                         : return HLG_AVA;
        case LCD_BRIGHTNESS_ID              : return LCD_BRIGHTNESS_AVA;
        case LED_ID                         : return LED_AVA;
        case TIME_LAPSE_DIGITAL_LENSES_ID   : return TIME_LAPSE_DIGITAL_LENSES_AVA;
        case MEDIA_FORMAT_ID                : return MEDIA_FORMAT_AVA;
        case ANTI_FLICKER_ID                : return ANTI_FLICKER_AVA;
        case HYPERSMOOTH_ID                 : return HYPERSMOOTH_AVA;
        case VIDEO_HORIZON_LEVELING_ID      : return VIDEO_HORIZON_LEVELING_AVA;
        case PHOTO_HORIZON_LEVELING_ID      : return PHOTO_HORIZON_LEVELING_AVA;
        case VIDEO_DURATION_ID              : return VIDEO_DURATION_AVA;
        case MULTISHOT_DURATION_ID          : return MULTISHOT_DURATION_AVA;
        case MAX_LENS_ID                    : return MAX_LENS_AVA;
        case HINDSIGHT_ID                   : return HINDSIGHT_AVA;
        case PHOTO_SINGLE_INTERVAL_ID       : return PHOTO_SINGLE_INTERVAL_AVA;
        case PHOTO_SINGLE_DURATION_ID       : return PHOTO_SINGLE_DURATION_AVA;
        case VIDEO_PERFORMANCE_MODE_ID      : return VIDEO_PERFORMANCE_MODE_AVA;
        case CONTROL_MODE_ID                : return CONTROL_MODE_AVA;
        case EASY_MODE_SPEED_ID             : return EASY_MODE_SPEED_AVA;
        case ENABLE_NIGHT_PHOTO_ID          : return ENABLE_NIGHT_PHOTO_AVA;
        case WIRELESS_BAND_ID               : return WIRELESS_BAND_AVA;
        case STAR_TRAILS_LENGTH_ID          : return STAR_TRAILS_LENGTH_AVA;
        case SYSTEM_VIDEO_MODE_ID           : return SYSTEM_VIDEO_MODE_AVA;
        case PROFILES_ID                    : return PROFILES_AVA;
        case VIDEO_EASY_MODE_ID             : return VIDEO_EASY_MODE_AVA;
        case LAPSE_MODE_ID                  : return LAPSE_MODE_AVA;
        case MAX_LENS_MOD_ID                : return MAX_LENS_MOD_AVA;
        case MAX_LENS_MOD_ENABLE_ID         : return MAX_LENS_MOD_ENABLE_AVA;
        case EASY_NIGHT_PHOTO_ID            : return EASY_NIGHT_PHOTO_AVA;
        case MULTI_SHOT_ASPECT_RATIO_ID     : return MULTI_SHOT_ASPECT_RATIO_AVA;
        case FRAMING_ID                     : return FRAMING_AVA;
        case CAMERA_MODE_ID                 : return CAMERA_MODE_AVA;
        case _360_PHOTO_FILES_EXTENSION_ID  : return _360_PHOTO_FILES_EXTENSION_AVA;
        case BEEP_VOLUME_ID                 : return BEEP_VOLUME_AVA;
        case SETUP_SCREEN_SAVER_ID          : return SETUP_SCREEN_SAVER_AVA;
        case VIDEO_FRAMING_ID               : return VIDEO_FRAMING_AVA;
        case AUTOMATIC_WI_FI_ACCESS_POINT_ID: return AUTOMATIC_WI_FI_ACCESS_POINT_AVA;
        case WHITE_BALANCE_ID               : return WHITE_BALANCE_AVA;
        case SHARPNESS_ID                   : return SHARPNESS_AVA;
        case EXPOSURE_ID                    : return EXPOSURE_AVA;
        case COLOR_ID                       : return COLOR_AVA;
        case ISO_MIN_VIDEO_ID               : return ISO_MIN_VIDEO_AVA;
        case ISO_MAX_VIDEO_ID               : return ISO_MAX_VIDEO_AVA;
        case ISO_MIN_PHOTO_ID               : return ISO_MIN_PHOTO_AVA;
        case ISO_MAX_PHOTO_ID               : return ISO_MAX_PHOTO_AVA;
        case SHUTTER_SPEED_VIDEO_ID         : return SHUTTER_SPEED_VIDEO_AVA;
        case SHUTTER_SPEED_PHOTO_ID         : return SHUTTER_SPEED_PHOTO_AVA;
             default                        : return 0;
    }
}

inline const char* GET_SETTING_NAME_BY_ID(int32_t x) {
    switch(x) {
        case ISO_AUTO_ID                    : return ISO_AUTO_NAME;
        case DENOISE_ID                     : return DENOISE_NAME;
        case BURST_OUTPUT_ID                : return BURST_OUTPUT_NAME;
        case PHOTO_BURST_RATE_ID            : return PHOTO_BURST_RATE_NAME;
        case ISO_MIN_BURST_ID               : return ISO_MIN_BURST_NAME;
        case ISO_MAX_BURST_ID               : return ISO_MAX_BURST_NAME;
        case SHOT_COUNTDOWN_ID              : return SHOT_COUNTDOWN_NAME;
        case VIDEO_RESOLUTION_ID            : return VIDEO_RESOLUTION_NAME;
        case FRAMES_PER_SECOND_ID           : return FRAMES_PER_SECOND_NAME;
        case VIDEO_LENS_ID                  : return VIDEO_LENS_NAME;
        case VIDEO_ASPECT_RATIO_ID          : return VIDEO_ASPECT_RATIO_NAME;
        case BIT_DEPTH_ID                   : return BIT_DEPTH_NAME;
        case VIDEO_BIT_RATE_ID              : return VIDEO_BIT_RATE_NAME;
        case PHOTO_LENS_ID                  : return PHOTO_LENS_NAME;
        case PHOTO_OUTPUT_ID                : return PHOTO_OUTPUT_NAME;
        case VIDEO_TIMELAPSE_RATE_ID        : return VIDEO_TIMELAPSE_RATE_NAME;
        case PHOTO_TIMELAPSE_RATE_ID        : return PHOTO_TIMELAPSE_RATE_NAME;
        case NIGHTLAPSE_RATE_ID             : return NIGHTLAPSE_RATE_NAME;
        case WEBCAM_DIGITAL_LENSES_ID       : return WEBCAM_DIGITAL_LENSES_NAME;
        case AUTO_POWER_DOWN_ID             : return AUTO_POWER_DOWN_NAME;
        case GPS_ID                         : return GPS_NAME;
        case HLG_ID                         : return HLG_NAME;
        case LCD_BRIGHTNESS_ID              : return LCD_BRIGHTNESS_NAME;
        case LED_ID                         : return LED_NAME;
        case TIME_LAPSE_DIGITAL_LENSES_ID   : return TIME_LAPSE_DIGITAL_LENSES_NAME;
        case MEDIA_FORMAT_ID                : return MEDIA_FORMAT_NAME;
        case ANTI_FLICKER_ID                : return ANTI_FLICKER_NAME;
        case HYPERSMOOTH_ID                 : return HYPERSMOOTH_NAME;
        case VIDEO_HORIZON_LEVELING_ID      : return VIDEO_HORIZON_LEVELING_NAME;
        case PHOTO_HORIZON_LEVELING_ID      : return PHOTO_HORIZON_LEVELING_NAME;
        case VIDEO_DURATION_ID              : return VIDEO_DURATION_NAME;
        case MULTISHOT_DURATION_ID          : return MULTISHOT_DURATION_NAME;
        case MAX_LENS_ID                    : return MAX_LENS_NAME;
        case HINDSIGHT_ID                   : return HINDSIGHT_NAME;
        case PHOTO_SINGLE_INTERVAL_ID       : return PHOTO_SINGLE_INTERVAL_NAME;
        case PHOTO_SINGLE_DURATION_ID       : return PHOTO_SINGLE_DURATION_NAME;
        case VIDEO_PERFORMANCE_MODE_ID      : return VIDEO_PERFORMANCE_MODE_NAME;
        case CONTROL_MODE_ID                : return CONTROL_MODE_NAME;
        case EASY_MODE_SPEED_ID             : return EASY_MODE_SPEED_NAME;
        case ENABLE_NIGHT_PHOTO_ID          : return ENABLE_NIGHT_PHOTO_NAME;
        case WIRELESS_BAND_ID               : return WIRELESS_BAND_NAME;
        case STAR_TRAILS_LENGTH_ID          : return STAR_TRAILS_LENGTH_NAME;
        case SYSTEM_VIDEO_MODE_ID           : return SYSTEM_VIDEO_MODE_NAME;
        case PROFILES_ID                    : return PROFILES_NAME;
        case VIDEO_EASY_MODE_ID             : return VIDEO_EASY_MODE_NAME;
        case LAPSE_MODE_ID                  : return LAPSE_MODE_NAME;
        case MAX_LENS_MOD_ID                : return MAX_LENS_MOD_NAME;
        case MAX_LENS_MOD_ENABLE_ID         : return MAX_LENS_MOD_ENABLE_NAME;
        case EASY_NIGHT_PHOTO_ID            : return EASY_NIGHT_PHOTO_NAME;
        case MULTI_SHOT_ASPECT_RATIO_ID     : return MULTI_SHOT_ASPECT_RATIO_NAME;
        case FRAMING_ID                     : return FRAMING_NAME;
        case CAMERA_MODE_ID                 : return CAMERA_MODE_NAME;
        case _360_PHOTO_FILES_EXTENSION_ID  : return _360_PHOTO_FILES_EXTENSION_NAME;
        case BEEP_VOLUME_ID                 : return BEEP_VOLUME_NAME;
        case SETUP_SCREEN_SAVER_ID          : return SETUP_SCREEN_SAVER_NAME;
        case VIDEO_FRAMING_ID               : return VIDEO_FRAMING_NAME;
        case AUTOMATIC_WI_FI_ACCESS_POINT_ID: return AUTOMATIC_WI_FI_ACCESS_POINT_NAME;
        case WHITE_BALANCE_ID               : return WHITE_BALANCE_NAME;
        case SHARPNESS_ID                   : return SHARPNESS_NAME;
        case EXPOSURE_ID                    : return EXPOSURE_NAME;
        case COLOR_ID                       : return COLOR_NAME;
        case ISO_MIN_VIDEO_ID               : return ISO_MIN_VIDEO_NAME;
        case ISO_MAX_VIDEO_ID               : return ISO_MAX_VIDEO_NAME;
        case ISO_MIN_PHOTO_ID               : return ISO_MIN_PHOTO_NAME;
        case ISO_MAX_PHOTO_ID               : return ISO_MAX_PHOTO_NAME;
        case SHUTTER_SPEED_VIDEO_ID         : return SHUTTER_SPEED_VIDEO_NAME;
        case SHUTTER_SPEED_PHOTO_ID         : return SHUTTER_SPEED_PHOTO_NAME;
     default                        : return "";
    }
}

inline const char** GET_SETTING_STRING_BY_ID(int32_t x) {
    switch(x) {
        case ISO_AUTO_ID                    : return ISO_AUTO_STRING;
        case DENOISE_ID                     : return DENOISE_STRING;
        case BURST_OUTPUT_ID                : return BURST_OUTPUT_STRING;
        case PHOTO_BURST_RATE_ID            : return PHOTO_BURST_RATE_STRING;
        case ISO_MIN_BURST_ID               : return ISO_MIN_BURST_STRING;
        case ISO_MAX_BURST_ID               : return ISO_MAX_BURST_STRING;
        case SHOT_COUNTDOWN_ID              : return SHOT_COUNTDOWN_STRING;
        case VIDEO_RESOLUTION_ID            : return VIDEO_RESOLUTION_STRING;
        case FRAMES_PER_SECOND_ID           : return FRAMES_PER_SECOND_STRING;
        case VIDEO_LENS_ID                  : return VIDEO_LENS_STRING;
        case VIDEO_ASPECT_RATIO_ID          : return VIDEO_ASPECT_RATIO_STRING;
        case BIT_DEPTH_ID                   : return BIT_DEPTH_STRING;
        case VIDEO_BIT_RATE_ID              : return VIDEO_BIT_RATE_STRING;
        case PHOTO_LENS_ID                  : return PHOTO_LENS_STRING;
        case PHOTO_OUTPUT_ID                : return PHOTO_OUTPUT_STRING;
        case VIDEO_TIMELAPSE_RATE_ID        : return VIDEO_TIMELAPSE_RATE_STRING;
        case PHOTO_TIMELAPSE_RATE_ID        : return PHOTO_TIMELAPSE_RATE_STRING;
        case NIGHTLAPSE_RATE_ID             : return NIGHTLAPSE_RATE_STRING;
        case WEBCAM_DIGITAL_LENSES_ID       : return WEBCAM_DIGITAL_LENSES_STRING;
        case AUTO_POWER_DOWN_ID             : return AUTO_POWER_DOWN_STRING;
        case GPS_ID                         : return GPS_STRING;
        case HLG_ID                         : return HLG_STRING;
        case LCD_BRIGHTNESS_ID              : return LCD_BRIGHTNESS_STRING;
        case LED_ID                         : return LED_STRING;
        case TIME_LAPSE_DIGITAL_LENSES_ID   : return TIME_LAPSE_DIGITAL_LENSES_STRING;
        case MEDIA_FORMAT_ID                : return MEDIA_FORMAT_STRING;
        case ANTI_FLICKER_ID                : return ANTI_FLICKER_STRING;
        case HYPERSMOOTH_ID                 : return HYPERSMOOTH_STRING;
        case VIDEO_HORIZON_LEVELING_ID      : return VIDEO_HORIZON_LEVELING_STRING;
        case PHOTO_HORIZON_LEVELING_ID      : return PHOTO_HORIZON_LEVELING_STRING;
        case VIDEO_DURATION_ID              : return VIDEO_DURATION_STRING;
        case MULTISHOT_DURATION_ID          : return MULTISHOT_DURATION_STRING;
        case MAX_LENS_ID                    : return MAX_LENS_STRING;
        case HINDSIGHT_ID                   : return HINDSIGHT_STRING;
        case PHOTO_SINGLE_INTERVAL_ID       : return PHOTO_SINGLE_INTERVAL_STRING;
        case PHOTO_SINGLE_DURATION_ID       : return PHOTO_SINGLE_DURATION_STRING;
        case VIDEO_PERFORMANCE_MODE_ID      : return VIDEO_PERFORMANCE_MODE_STRING;
        case CONTROL_MODE_ID                : return CONTROL_MODE_STRING;
        case EASY_MODE_SPEED_ID             : return EASY_MODE_SPEED_STRING;
        case ENABLE_NIGHT_PHOTO_ID          : return ENABLE_NIGHT_PHOTO_STRING;
        case WIRELESS_BAND_ID               : return WIRELESS_BAND_STRING;
        case STAR_TRAILS_LENGTH_ID          : return STAR_TRAILS_LENGTH_STRING;
        case SYSTEM_VIDEO_MODE_ID           : return SYSTEM_VIDEO_MODE_STRING;
        case PROFILES_ID                    : return PROFILES_STRING;
        case VIDEO_EASY_MODE_ID             : return VIDEO_EASY_MODE_STRING;
        case LAPSE_MODE_ID                  : return LAPSE_MODE_STRING;
        case MAX_LENS_MOD_ID                : return MAX_LENS_MOD_STRING;
        case MAX_LENS_MOD_ENABLE_ID         : return MAX_LENS_MOD_ENABLE_STRING;
        case EASY_NIGHT_PHOTO_ID            : return EASY_NIGHT_PHOTO_STRING;
        case MULTI_SHOT_ASPECT_RATIO_ID     : return MULTI_SHOT_ASPECT_RATIO_STRING;
        case FRAMING_ID                     : return FRAMING_STRING;
        case CAMERA_MODE_ID                 : return CAMERA_MODE_STRING;
        case _360_PHOTO_FILES_EXTENSION_ID  : return _360_PHOTO_FILES_EXTENSION_STRING;
        case BEEP_VOLUME_ID                 : return BEEP_VOLUME_STRING;
        case SETUP_SCREEN_SAVER_ID          : return SETUP_SCREEN_SAVER_STRING;
        case VIDEO_FRAMING_ID               : return VIDEO_FRAMING_STRING;
        case AUTOMATIC_WI_FI_ACCESS_POINT_ID: return AUTOMATIC_WI_FI_ACCESS_POINT_STRING;
        case WHITE_BALANCE_ID               : return WHITE_BALANCE_STRING;
        case SHARPNESS_ID                   : return SHARPNESS_STRING;
        case EXPOSURE_ID                    : return EXPOSURE_STRING;
        case COLOR_ID                       : return COLOR_STRING;
        case ISO_MIN_VIDEO_ID               : return ISO_MIN_VIDEO_STRING;
        case ISO_MAX_VIDEO_ID               : return ISO_MAX_VIDEO_STRING;
        case ISO_MIN_PHOTO_ID               : return ISO_MIN_PHOTO_STRING;
        case ISO_MAX_PHOTO_ID               : return ISO_MAX_PHOTO_STRING;
        case SHUTTER_SPEED_VIDEO_ID         : return SHUTTER_SPEED_VIDEO_STRING;
        case SHUTTER_SPEED_PHOTO_ID         : return SHUTTER_SPEED_PHOTO_STRING;
             default                        : return nullptr;
    }
}

inline const int32_t* GET_SETTING_VALUE_BY_ID(int32_t x) {
    switch(x) {
        case ISO_AUTO_ID                    : return ISO_AUTO_VALUE;
        case DENOISE_ID                     : return DENOISE_VALUE;
        case BURST_OUTPUT_ID                : return BURST_OUTPUT_VALUE;
        case PHOTO_BURST_RATE_ID            : return PHOTO_BURST_RATE_VALUE;
        case ISO_MIN_BURST_ID               : return ISO_MIN_BURST_VALUE;
        case ISO_MAX_BURST_ID               : return ISO_MAX_BURST_VALUE;
        case SHOT_COUNTDOWN_ID              : return SHOT_COUNTDOWN_VALUE;
        case VIDEO_RESOLUTION_ID            : return VIDEO_RESOLUTION_VALUE;
        case FRAMES_PER_SECOND_ID           : return FRAMES_PER_SECOND_VALUE;
        case VIDEO_LENS_ID                  : return VIDEO_LENS_VALUE;
        case VIDEO_ASPECT_RATIO_ID          : return VIDEO_ASPECT_RATIO_VALUE;
        case BIT_DEPTH_ID                   : return BIT_DEPTH_VALUE;
        case VIDEO_BIT_RATE_ID              : return VIDEO_BIT_RATE_VALUE;
        case PHOTO_LENS_ID                  : return PHOTO_LENS_VALUE;
        case PHOTO_OUTPUT_ID                : return PHOTO_OUTPUT_VALUE;
        case VIDEO_TIMELAPSE_RATE_ID        : return VIDEO_TIMELAPSE_RATE_VALUE;
        case PHOTO_TIMELAPSE_RATE_ID        : return PHOTO_TIMELAPSE_RATE_VALUE;
        case NIGHTLAPSE_RATE_ID             : return NIGHTLAPSE_RATE_VALUE;
        case WEBCAM_DIGITAL_LENSES_ID       : return WEBCAM_DIGITAL_LENSES_VALUE;
        case AUTO_POWER_DOWN_ID             : return AUTO_POWER_DOWN_VALUE;
        case GPS_ID                         : return GPS_VALUE;
        case HLG_ID                         : return HLG_VALUE;
        case LCD_BRIGHTNESS_ID              : return LCD_BRIGHTNESS_VALUE;
        case LED_ID                         : return LED_VALUE;
        case TIME_LAPSE_DIGITAL_LENSES_ID   : return TIME_LAPSE_DIGITAL_LENSES_VALUE;
        case MEDIA_FORMAT_ID                : return MEDIA_FORMAT_VALUE;
        case ANTI_FLICKER_ID                : return ANTI_FLICKER_VALUE;
        case HYPERSMOOTH_ID                 : return HYPERSMOOTH_VALUE;
        case VIDEO_HORIZON_LEVELING_ID      : return VIDEO_HORIZON_LEVELING_VALUE;
        case PHOTO_HORIZON_LEVELING_ID      : return PHOTO_HORIZON_LEVELING_VALUE;
        case VIDEO_DURATION_ID              : return VIDEO_DURATION_VALUE;
        case MULTISHOT_DURATION_ID          : return MULTISHOT_DURATION_VALUE;
        case MAX_LENS_ID                    : return MAX_LENS_VALUE;
        case HINDSIGHT_ID                   : return HINDSIGHT_VALUE;
        case PHOTO_SINGLE_INTERVAL_ID       : return PHOTO_SINGLE_INTERVAL_VALUE;
        case PHOTO_SINGLE_DURATION_ID       : return PHOTO_SINGLE_DURATION_VALUE;
        case VIDEO_PERFORMANCE_MODE_ID      : return VIDEO_PERFORMANCE_MODE_VALUE;
        case CONTROL_MODE_ID                : return CONTROL_MODE_VALUE;
        case EASY_MODE_SPEED_ID             : return EASY_MODE_SPEED_VALUE;
        case ENABLE_NIGHT_PHOTO_ID          : return ENABLE_NIGHT_PHOTO_VALUE;
        case WIRELESS_BAND_ID               : return WIRELESS_BAND_VALUE;
        case STAR_TRAILS_LENGTH_ID          : return STAR_TRAILS_LENGTH_VALUE;
        case SYSTEM_VIDEO_MODE_ID           : return SYSTEM_VIDEO_MODE_VALUE;
        case PROFILES_ID                    : return PROFILES_VALUE;
        case VIDEO_EASY_MODE_ID             : return VIDEO_EASY_MODE_VALUE;
        case LAPSE_MODE_ID                  : return LAPSE_MODE_VALUE;
        case MAX_LENS_MOD_ID                : return MAX_LENS_MOD_VALUE;
        case MAX_LENS_MOD_ENABLE_ID         : return MAX_LENS_MOD_ENABLE_VALUE;
        case EASY_NIGHT_PHOTO_ID            : return EASY_NIGHT_PHOTO_VALUE;
        case MULTI_SHOT_ASPECT_RATIO_ID     : return MULTI_SHOT_ASPECT_RATIO_VALUE;
        case FRAMING_ID                     : return FRAMING_VALUE;
        case CAMERA_MODE_ID                 : return CAMERA_MODE_VALUE;
        case _360_PHOTO_FILES_EXTENSION_ID  : return _360_PHOTO_FILES_EXTENSION_VALUE;
        case BEEP_VOLUME_ID                 : return BEEP_VOLUME_VALUE;
        case SETUP_SCREEN_SAVER_ID          : return SETUP_SCREEN_SAVER_VALUE;
        case VIDEO_FRAMING_ID               : return VIDEO_FRAMING_VALUE;
        case AUTOMATIC_WI_FI_ACCESS_POINT_ID: return AUTOMATIC_WI_FI_ACCESS_POINT_VALUE;
        case WHITE_BALANCE_ID               : return WHITE_BALANCE_VALUE;
        case SHARPNESS_ID                   : return SHARPNESS_VALUE;
        case EXPOSURE_ID                    : return EXPOSURE_VALUE;
        case COLOR_ID                       : return COLOR_VALUE;
        case ISO_MIN_VIDEO_ID               : return ISO_MIN_VIDEO_VALUE;
        case ISO_MAX_VIDEO_ID               : return ISO_MAX_VIDEO_VALUE;
        case ISO_MIN_PHOTO_ID               : return ISO_MIN_PHOTO_VALUE;
        case ISO_MAX_PHOTO_ID               : return ISO_MAX_PHOTO_VALUE;
        case SHUTTER_SPEED_VIDEO_ID         : return SHUTTER_SPEED_VIDEO_VALUE;
        case SHUTTER_SPEED_PHOTO_ID         : return SHUTTER_SPEED_PHOTO_VALUE;
             default                        : return nullptr;
    }
}

inline const int32_t* GET_SETTING_SUPPORT_BY_ID(int32_t x) {
    switch(x) {
        case ISO_AUTO_ID                    : return ISO_AUTO_SUPPORT;
        case DENOISE_ID                     : return DENOISE_SUPPORT;
        case BURST_OUTPUT_ID                : return BURST_OUTPUT_SUPPORT;
        case PHOTO_BURST_RATE_ID            : return PHOTO_BURST_RATE_SUPPORT;
        case ISO_MIN_BURST_ID               : return ISO_MIN_BURST_SUPPORT;
        case ISO_MAX_BURST_ID               : return ISO_MAX_BURST_SUPPORT;
        case SHOT_COUNTDOWN_ID              : return SHOT_COUNTDOWN_SUPPORT;
        case VIDEO_RESOLUTION_ID            : return VIDEO_RESOLUTION_SUPPORT;
        case FRAMES_PER_SECOND_ID           : return FRAMES_PER_SECOND_SUPPORT;
        case VIDEO_LENS_ID                  : return VIDEO_LENS_SUPPORT;
        case VIDEO_ASPECT_RATIO_ID          : return VIDEO_ASPECT_RATIO_SUPPORT;
        case BIT_DEPTH_ID                   : return BIT_DEPTH_SUPPORT;
        case VIDEO_BIT_RATE_ID              : return VIDEO_BIT_RATE_SUPPORT;
        case PHOTO_LENS_ID                  : return PHOTO_LENS_SUPPORT;
        case PHOTO_OUTPUT_ID                : return PHOTO_OUTPUT_SUPPORT;
        case VIDEO_TIMELAPSE_RATE_ID        : return VIDEO_TIMELAPSE_RATE_SUPPORT;
        case PHOTO_TIMELAPSE_RATE_ID        : return PHOTO_TIMELAPSE_RATE_SUPPORT;
        case NIGHTLAPSE_RATE_ID             : return NIGHTLAPSE_RATE_SUPPORT;
        case WEBCAM_DIGITAL_LENSES_ID       : return WEBCAM_DIGITAL_LENSES_SUPPORT;
        case AUTO_POWER_DOWN_ID             : return AUTO_POWER_DOWN_SUPPORT;
        case GPS_ID                         : return GPS_SUPPORT;
        case HLG_ID                         : return HLG_SUPPORT;
        case LCD_BRIGHTNESS_ID              : return LCD_BRIGHTNESS_SUPPORT;
        case LED_ID                         : return LED_SUPPORT;
        case TIME_LAPSE_DIGITAL_LENSES_ID   : return TIME_LAPSE_DIGITAL_LENSES_SUPPORT;
        case MEDIA_FORMAT_ID                : return MEDIA_FORMAT_SUPPORT;
        case ANTI_FLICKER_ID                : return ANTI_FLICKER_SUPPORT;
        case HYPERSMOOTH_ID                 : return HYPERSMOOTH_SUPPORT;
        case VIDEO_HORIZON_LEVELING_ID      : return VIDEO_HORIZON_LEVELING_SUPPORT;
        case PHOTO_HORIZON_LEVELING_ID      : return PHOTO_HORIZON_LEVELING_SUPPORT;
        case VIDEO_DURATION_ID              : return VIDEO_DURATION_SUPPORT;
        case MULTISHOT_DURATION_ID          : return MULTISHOT_DURATION_SUPPORT;
        case MAX_LENS_ID                    : return MAX_LENS_SUPPORT;
        case HINDSIGHT_ID                   : return HINDSIGHT_SUPPORT;
        case PHOTO_SINGLE_INTERVAL_ID       : return PHOTO_SINGLE_INTERVAL_SUPPORT;
        case PHOTO_SINGLE_DURATION_ID       : return PHOTO_SINGLE_DURATION_SUPPORT;
        case VIDEO_PERFORMANCE_MODE_ID      : return VIDEO_PERFORMANCE_MODE_SUPPORT;
        case CONTROL_MODE_ID                : return CONTROL_MODE_SUPPORT;
        case EASY_MODE_SPEED_ID             : return EASY_MODE_SPEED_SUPPORT;
        case ENABLE_NIGHT_PHOTO_ID          : return ENABLE_NIGHT_PHOTO_SUPPORT;
        case WIRELESS_BAND_ID               : return WIRELESS_BAND_SUPPORT;
        case STAR_TRAILS_LENGTH_ID          : return STAR_TRAILS_LENGTH_SUPPORT;
        case SYSTEM_VIDEO_MODE_ID           : return SYSTEM_VIDEO_MODE_SUPPORT;
        case PROFILES_ID                    : return PROFILES_SUPPORT;
        case VIDEO_EASY_MODE_ID             : return VIDEO_EASY_MODE_SUPPORT;
        case LAPSE_MODE_ID                  : return LAPSE_MODE_SUPPORT;
        case MAX_LENS_MOD_ID                : return MAX_LENS_MOD_SUPPORT;
        case MAX_LENS_MOD_ENABLE_ID         : return MAX_LENS_MOD_ENABLE_SUPPORT;
        case EASY_NIGHT_PHOTO_ID            : return EASY_NIGHT_PHOTO_SUPPORT;
        case MULTI_SHOT_ASPECT_RATIO_ID     : return MULTI_SHOT_ASPECT_RATIO_SUPPORT;
        case FRAMING_ID                     : return FRAMING_SUPPORT;
        case CAMERA_MODE_ID                 : return CAMERA_MODE_SUPPORT;
        case _360_PHOTO_FILES_EXTENSION_ID  : return _360_PHOTO_FILES_EXTENSION_SUPPORT;
        case BEEP_VOLUME_ID                 : return BEEP_VOLUME_SUPPORT;
        case SETUP_SCREEN_SAVER_ID          : return SETUP_SCREEN_SAVER_SUPPORT;
        case VIDEO_FRAMING_ID               : return VIDEO_FRAMING_SUPPORT;
        case AUTOMATIC_WI_FI_ACCESS_POINT_ID: return AUTOMATIC_WI_FI_ACCESS_POINT_SUPPORT;
        case WHITE_BALANCE_ID               : return WHITE_BALANCE_SUPPORT;
        case SHARPNESS_ID                   : return SHARPNESS_SUPPORT;
        case EXPOSURE_ID                    : return EXPOSURE_SUPPORT;
        case COLOR_ID                       : return COLOR_SUPPORT;
        case ISO_MIN_VIDEO_ID               : return ISO_MIN_VIDEO_SUPPORT;
        case ISO_MAX_VIDEO_ID               : return ISO_MAX_VIDEO_SUPPORT;
        case ISO_MIN_PHOTO_ID               : return ISO_MIN_PHOTO_SUPPORT;
        case ISO_MAX_PHOTO_ID               : return ISO_MAX_PHOTO_SUPPORT;
        case SHUTTER_SPEED_VIDEO_ID         : return SHUTTER_SPEED_VIDEO_SUPPORT;
        case SHUTTER_SPEED_PHOTO_ID         : return SHUTTER_SPEED_PHOTO_SUPPORT;
             default                        : return nullptr;
    }
}

inline const int32_t GET_STATUS_TYPE_BY_ID(int32_t x){
    switch(x) {
        case BATTERY_PRESENT_ID:                    return (int32_t)BATTERY_PRESENT_TYPE;
        case INTERNAL_BATTERY_BARS_ID:              return (int32_t)INTERNAL_BATTERY_BARS_TYPE;
        case OVERHEATING_ID:                        return (int32_t)OVERHEATING_TYPE;
        case BUSY_ID:                               return (int32_t)BUSY_TYPE;
        case QUICK_CAPTURE_ID:                      return (int32_t)QUICK_CAPTURE_TYPE;
        case ENCODING_ID:                           return (int32_t)ENCODING_TYPE;
        case LCD_LOCK_ID:                           return (int32_t)LCD_LOCK_TYPE;
        case VIDEO_ENCODING_DURATION_ID:            return (int32_t)VIDEO_ENCODING_DURATION_TYPE;
        case WIRELESS_CONNECTIONS_ENABLED_ID:       return (int32_t)WIRELESS_CONNECTIONS_ENABLED_TYPE;
        case PAIRING_STATE_ID:                      return (int32_t)PAIRING_STATE_TYPE;
        case LAST_PAIRING_TYPE_ID:                  return (int32_t)LAST_PAIRING_TYPE_TYPE;
        case LAST_PAIRING_SUCESS_ID:                return (int32_t)LAST_PAIRING_SUCESS_TYPE;
        case WIFI_SCAN_STATE_ID:                    return (int32_t)WIFI_SCAN_STATE_TYPE;
        case LAST_WIFI_SCAN_SUCESS_ID:              return (int32_t)LAST_WIFI_SCAN_SUCESS_TYPE;
        case WIFI_PROVISIONING_STATE_ID:            return (int32_t)WIFI_PROVISIONING_STATE_TYPE;
        case REMOTE_VERSION_ID:                     return (int32_t)REMOTE_VERSION_TYPE;
        case REMOTE_CONNECTED_ID:                   return (int32_t)REMOTE_CONNECTED_TYPE;
        case CONNECTED_WIFI_SSID_ID:                return (int32_t)CONNECTED_WIFI_SSID_TYPE;
        case ACCESS_POINT_SSID_ID:                  return (int32_t)ACCESS_POINT_SSID_TYPE;
        case CONNECTED_DEVICE_ID:                   return (int32_t)CONNECTED_DEVICE_TYPE;
        case PREVIEW_STREAM_ID:                     return (int32_t)PREVIEW_STREAM_TYPE;
        case PRIMARY_STORAGE_ID:                    return (int32_t)PRIMARY_STORAGE_TYPE;
        case REMAINING_PHOTOS_ID:                   return (int32_t)REMAINING_PHOTOS_TYPE;
        case REMAINING_VIDEO_TIME_ID:               return (int32_t)REMAINING_VIDEO_TIME_TYPE;
        case PHOTOS_ID:                             return (int32_t)PHOTOS_TYPE;
        case VIDEOS_ID:                             return (int32_t)VIDEOS_TYPE;
        case OTA_ID:                                return (int32_t)OTA_TYPE;
        case PENDING_FW_UPDATE_CANCEL_ID:           return (int32_t)PENDING_FW_UPDATE_CANCEL_TYPE;
        case LOCATE_ID:                             return (int32_t)LOCATE_TYPE;
        case TIMELAPSE_INTERVAL_COUNTDOWN_ID:       return (int32_t)TIMELAPSE_INTERVAL_COUNTDOWN_TYPE;
        case SD_CARD_REMAINING_ID:                  return (int32_t)SD_CARD_REMAINING_TYPE;
        case PREVIEW_STREAM_AVAILABLE_ID:           return (int32_t)PREVIEW_STREAM_AVAILABLE_TYPE;
        case WIFI_BARS_ID:                          return (int32_t)WIFI_BARS_TYPE;
        case ACTIVE_HILIGHTS_ID:                    return (int32_t)ACTIVE_HILIGHTS_TYPE;
        case TIME_SINCE_LAST_HILIGHT_ID:            return (int32_t)TIME_SINCE_LAST_HILIGHT_TYPE;
        case MINIMUM_STATUS_POLL_PREIOD_ID:         return (int32_t)MINIMUM_STATUS_POLL_PREIOD_TYPE;
        case LIVEVIEW_EXPOSURE_SELECT_MODE_ID:      return (int32_t)LIVEVIEW_EXPOSURE_SELECT_MODE_TYPE;
        case LIVEVIEW_Y_ID:                         return (int32_t)LIVEVIEW_Y_TYPE;
        case LIVEVIEW_X_ID:                         return (int32_t)LIVEVIEW_X_TYPE;
        case GPS_LOCK_ID:                           return (int32_t)GPS_LOCK_TYPE;
        case AP_MODE_ID:                            return (int32_t)AP_MODE_TYPE;
        case INTERNAL_BATTERY_PERCENTAGE_ID:        return (int32_t)INTERNAL_BATTERY_PERCENTAGE_TYPE;
        case MICROPHONE_ACCESSORY_ID:               return (int32_t)MICROPHONE_ACCESSORY_TYPE;
        case ZOOM_LEVEL_ID:                         return (int32_t)ZOOM_LEVEL_TYPE;
        case STATUS_WIRELESS_BAND_ID:               return (int32_t)STATUS_WIRELESS_BAND_TYPE;
        case ZOOM_AVAILABLE_ID:                     return (int32_t)ZOOM_AVAILABLE_TYPE;
        case MOBILE_FRIENDLY_ID:                    return (int32_t)MOBILE_FRIENDLY_TYPE;
        case FTU_ID:                                return (int32_t)FTU_TYPE;
        case _5GHZ_AVAILABLE_ID:                    return (int32_t)_5GHZ_AVAILABLE_TYPE;
        case READY_ID:                              return (int32_t)READY_TYPE;
        case OTA_CHANGED_ID:                        return (int32_t)OTA_CHANGED_TYPE;
        case COLD_ID:                               return (int32_t)COLD_TYPE;
        case ROTATION_ID:                           return (int32_t)ROTATION_TYPE;
        case ZOOM_WHILE_ENCODING_ID:                return (int32_t)ZOOM_WHILE_ENCODING_TYPE;
        case FLATMODE_ID:                           return (int32_t)FLATMODE_TYPE;
        case VIDEO_PRESET_ID:                       return (int32_t)VIDEO_PRESET_TYPE;
        case PHOTO_PRESET_ID:                       return (int32_t)PHOTO_PRESET_TYPE;
        case TIMELAPSE_PRESET_ID:                   return (int32_t)TIMELAPSE_PRESET_TYPE;
        case PRESET_GROUP_ID:                       return (int32_t)PRESET_GROUP_TYPE;
        case PRESET_ID:                             return (int32_t)PRESET_TYPE;
        case PRESET_MODIFIED_ID:                    return (int32_t)PRESET_MODIFIED_TYPE;
        case REMAINING_LIVE_BURSTS_ID:              return (int32_t)REMAINING_LIVE_BURSTS_TYPE;
        case LIVE_BURSTS_ID:                        return (int32_t)LIVE_BURSTS_TYPE;
        case CAPTURE_DELAY_ACTIVE_ID:               return (int32_t)CAPTURE_DELAY_ACTIVE_TYPE;
        case MEDIA_MOD_STATE_ID:                    return (int32_t)MEDIA_MOD_STATE_TYPE;
        case TIME_WARP_SPEED_ID:                    return (int32_t)TIME_WARP_SPEED_TYPE;
        case LENS_TYPE_ID:                          return (int32_t)STATUS_HINDSIGHT_TYPE;
        case LINUX_CORE_ID:                         return (int32_t)LINUX_CORE_TYPE;
        case SCHEDULED_CAPTURE_PRESET_ID:           return (int32_t)SCHEDULED_CAPTURE_PRESET_TYPE;
        case STATUS_SCHEDULED_CAPTURE_ID:           return (int32_t)STATUS_SCHEDULED_CAPTURE_TYPE;
        case SD_CARD_WRITE_SPEED_ERROR_ID:          return (int32_t)SD_CARD_WRITE_SPEED_ERROR_TYPE;
        case SD_CARD_ERRORS_ID:                     return (int32_t)SD_CARD_ERRORS_TYPE;
        case STATUS_CAMERA_CONTROL_ID:              return (int32_t)STATUS_CAMERA_CONTROL_TYPE;
        case USB_CONNECTED_ID:                      return (int32_t)USB_CONNECTED_TYPE;
        case USE_CONTROLLED_ID:                     return (int32_t)USE_CONTROLLED_TYPE;
        case SD_CARD_CAPACITY_ID:                   return (int32_t)SD_CARD_CAPACITY_TYPE;
        case CAMERA_NAME_ID:                        return (int32_t)CAMERA_NAME_TYPE;
        default: return 0;
    }
}

inline const char* GET_STATUS_NAME_BY_ID(int32_t x){
    switch(x) {
        case BATTERY_PRESENT_ID:                    return BATTERY_PRESENT_NAME;
        case INTERNAL_BATTERY_BARS_ID:              return INTERNAL_BATTERY_BARS_NAME;
        case OVERHEATING_ID:                        return OVERHEATING_NAME;
        case BUSY_ID:                               return BUSY_NAME;
        case QUICK_CAPTURE_ID:                      return QUICK_CAPTURE_NAME;
        case ENCODING_ID:                           return ENCODING_NAME;
        case LCD_LOCK_ID:                           return LCD_LOCK_NAME;
        case VIDEO_ENCODING_DURATION_ID:            return VIDEO_ENCODING_DURATION_NAME;
        case WIRELESS_CONNECTIONS_ENABLED_ID:       return WIRELESS_CONNECTIONS_ENABLED_NAME;
        case PAIRING_STATE_ID:                      return PAIRING_STATE_NAME;
        case LAST_PAIRING_TYPE_ID:                  return LAST_PAIRING_TYPE_NAME;
        case LAST_PAIRING_SUCESS_ID:                return LAST_PAIRING_SUCESS_NAME;
        case WIFI_SCAN_STATE_ID:                    return WIFI_SCAN_STATE_NAME;
        case LAST_WIFI_SCAN_SUCESS_ID:              return LAST_WIFI_SCAN_SUCESS_NAME;
        case WIFI_PROVISIONING_STATE_ID:            return WIFI_PROVISIONING_STATE_NAME;
        case REMOTE_VERSION_ID:                     return REMOTE_VERSION_NAME;
        case REMOTE_CONNECTED_ID:                   return REMOTE_CONNECTED_NAME;
        case CONNECTED_WIFI_SSID_ID:                return CONNECTED_WIFI_SSID_NAME;
        case ACCESS_POINT_SSID_ID:                  return ACCESS_POINT_SSID_NAME;
        case CONNECTED_DEVICE_ID:                   return CONNECTED_DEVICE_NAME;
        case PREVIEW_STREAM_ID:                     return PREVIEW_STREAM_NAME;
        case PRIMARY_STORAGE_ID:                    return PRIMARY_STORAGE_NAME;
        case REMAINING_PHOTOS_ID:                   return REMAINING_PHOTOS_NAME;
        case REMAINING_VIDEO_TIME_ID:               return REMAINING_VIDEO_TIME_NAME;
        case PHOTOS_ID:                             return PHOTOS_NAME;
        case VIDEOS_ID:                             return VIDEOS_NAME;
        case OTA_ID:                                return OTA_NAME;
        case PENDING_FW_UPDATE_CANCEL_ID:           return PENDING_FW_UPDATE_CANCEL_NAME;
        case LOCATE_ID:                             return LOCATE_NAME;
        case TIMELAPSE_INTERVAL_COUNTDOWN_ID:       return TIMELAPSE_INTERVAL_COUNTDOWN_NAME;
        case SD_CARD_REMAINING_ID:                  return SD_CARD_REMAINING_NAME;
        case PREVIEW_STREAM_AVAILABLE_ID:           return PREVIEW_STREAM_AVAILABLE_NAME;
        case WIFI_BARS_ID:                          return WIFI_BARS_NAME;
        case ACTIVE_HILIGHTS_ID:                    return ACTIVE_HILIGHTS_NAME;
        case TIME_SINCE_LAST_HILIGHT_ID:            return TIME_SINCE_LAST_HILIGHT_NAME;
        case MINIMUM_STATUS_POLL_PREIOD_ID:         return MINIMUM_STATUS_POLL_PREIOD_NAME;
        case LIVEVIEW_EXPOSURE_SELECT_MODE_ID:      return LIVEVIEW_EXPOSURE_SELECT_MODE_NAME;
        case LIVEVIEW_Y_ID:                         return LIVEVIEW_Y_NAME;
        case LIVEVIEW_X_ID:                         return LIVEVIEW_X_NAME;
        case GPS_LOCK_ID:                           return GPS_LOCK_NAME;
        case AP_MODE_ID:                            return AP_MODE_NAME;
        case INTERNAL_BATTERY_PERCENTAGE_ID:        return INTERNAL_BATTERY_PERCENTAGE_NAME;
        case MICROPHONE_ACCESSORY_ID:               return MICROPHONE_ACCESSORY_NAME;
        case ZOOM_LEVEL_ID:                         return ZOOM_LEVEL_NAME;
        case STATUS_WIRELESS_BAND_ID:               return STATUS_WIRELESS_BAND_NAME;
        case ZOOM_AVAILABLE_ID:                     return ZOOM_AVAILABLE_NAME;
        case MOBILE_FRIENDLY_ID:                    return MOBILE_FRIENDLY_NAME;
        case FTU_ID:                                return FTU_NAME;
        case _5GHZ_AVAILABLE_ID:                    return _5GHZ_AVAILABLE_NAME;
        case READY_ID:                              return READY_NAME;
        case OTA_CHANGED_ID:                        return OTA_CHANGED_NAME;
        case COLD_ID:                               return COLD_NAME;
        case ROTATION_ID:                           return ROTATION_NAME;
        case ZOOM_WHILE_ENCODING_ID:                return ZOOM_WHILE_ENCODING_NAME;
        case FLATMODE_ID:                           return FLATMODE_NAME;
        case VIDEO_PRESET_ID:                       return VIDEO_PRESET_NAME;
        case PHOTO_PRESET_ID:                       return PHOTO_PRESET_NAME;
        case TIMELAPSE_PRESET_ID:                   return TIMELAPSE_PRESET_NAME;
        case PRESET_GROUP_ID:                       return PRESET_GROUP_NAME;
        case PRESET_ID:                             return PRESET_NAME;
        case PRESET_MODIFIED_ID:                    return PRESET_MODIFIED_NAME;
        case REMAINING_LIVE_BURSTS_ID:              return REMAINING_LIVE_BURSTS_NAME;
        case LIVE_BURSTS_ID:                        return LIVE_BURSTS_NAME;
        case CAPTURE_DELAY_ACTIVE_ID:               return CAPTURE_DELAY_ACTIVE_NAME;
        case MEDIA_MOD_STATE_ID:                    return MEDIA_MOD_STATE_NAME;
        case TIME_WARP_SPEED_ID:                    return TIME_WARP_SPEED_NAME;
        case LENS_TYPE_ID:                          return LENS_TYPE_NAME;
        case LINUX_CORE_ID:                         return LINUX_CORE_NAME;
        case SCHEDULED_CAPTURE_PRESET_ID:           return SCHEDULED_CAPTURE_PRESET_NAME;
        case STATUS_SCHEDULED_CAPTURE_ID:           return STATUS_SCHEDULED_CAPTURE_NAME;
        case SD_CARD_WRITE_SPEED_ERROR_ID:          return SD_CARD_WRITE_SPEED_ERROR_NAME;
        case SD_CARD_ERRORS_ID:                     return SD_CARD_ERRORS_NAME;
        case STATUS_CAMERA_CONTROL_ID:              return STATUS_CAMERA_CONTROL_NAME;
        case USB_CONNECTED_ID:                      return USB_CONNECTED_NAME;
        case USE_CONTROLLED_ID:                     return USE_CONTROLLED_NAME;
        case SD_CARD_CAPACITY_ID:                   return SD_CARD_CAPACITY_NAME;
        case CAMERA_NAME_ID:                        return CAMERA_NAME_NAME;
        default: return "";
    }
}

inline const int32_t GET_STATUS_AVA_BY_ID(int32_t x){
    switch(x) {
        case BATTERY_PRESENT_ID:                    return BATTERY_PRESENT_AVA;
        case INTERNAL_BATTERY_BARS_ID:              return INTERNAL_BATTERY_BARS_AVA;
        case OVERHEATING_ID:                        return OVERHEATING_AVA;
        case BUSY_ID:                               return BUSY_AVA;
        case QUICK_CAPTURE_ID:                      return QUICK_CAPTURE_AVA;
        case ENCODING_ID:                           return ENCODING_AVA;
        case LCD_LOCK_ID:                           return LCD_LOCK_AVA;
        case VIDEO_ENCODING_DURATION_ID:            return VIDEO_ENCODING_DURATION_AVA;
        case WIRELESS_CONNECTIONS_ENABLED_ID:       return WIRELESS_CONNECTIONS_ENABLED_AVA;
        case PAIRING_STATE_ID:                      return PAIRING_STATE_AVA;
        case LAST_PAIRING_TYPE_ID:                  return LAST_PAIRING_TYPE_AVA;
        case LAST_PAIRING_SUCESS_ID:                return LAST_PAIRING_SUCESS_AVA;
        case WIFI_SCAN_STATE_ID:                    return WIFI_SCAN_STATE_AVA;
        case LAST_WIFI_SCAN_SUCESS_ID:              return LAST_WIFI_SCAN_SUCESS_AVA;
        case WIFI_PROVISIONING_STATE_ID:            return WIFI_PROVISIONING_STATE_AVA;
        case REMOTE_VERSION_ID:                     return REMOTE_VERSION_AVA;
        case REMOTE_CONNECTED_ID:                   return REMOTE_CONNECTED_AVA;
        case CONNECTED_WIFI_SSID_ID:                return CONNECTED_WIFI_SSID_AVA;
        case ACCESS_POINT_SSID_ID:                  return ACCESS_POINT_SSID_AVA;
        case CONNECTED_DEVICE_ID:                   return CONNECTED_DEVICE_AVA;
        case PREVIEW_STREAM_ID:                     return PREVIEW_STREAM_AVA;
        case PRIMARY_STORAGE_ID:                    return PRIMARY_STORAGE_AVA;
        case REMAINING_PHOTOS_ID:                   return REMAINING_PHOTOS_AVA;
        case REMAINING_VIDEO_TIME_ID:               return REMAINING_VIDEO_TIME_AVA;
        case PHOTOS_ID:                             return PHOTOS_AVA;
        case VIDEOS_ID:                             return VIDEOS_AVA;
        case OTA_ID:                                return OTA_AVA;
        case PENDING_FW_UPDATE_CANCEL_ID:           return PENDING_FW_UPDATE_CANCEL_AVA;
        case LOCATE_ID:                             return LOCATE_AVA;
        case TIMELAPSE_INTERVAL_COUNTDOWN_ID:       return TIMELAPSE_INTERVAL_COUNTDOWN_AVA;
        case SD_CARD_REMAINING_ID:                  return SD_CARD_REMAINING_AVA;
        case PREVIEW_STREAM_AVAILABLE_ID:           return PREVIEW_STREAM_AVAILABLE_AVA;
        case WIFI_BARS_ID:                          return WIFI_BARS_AVA;
        case ACTIVE_HILIGHTS_ID:                    return ACTIVE_HILIGHTS_AVA;
        case TIME_SINCE_LAST_HILIGHT_ID:            return TIME_SINCE_LAST_HILIGHT_AVA;
        case MINIMUM_STATUS_POLL_PREIOD_ID:         return MINIMUM_STATUS_POLL_PREIOD_AVA;
        case LIVEVIEW_EXPOSURE_SELECT_MODE_ID:      return LIVEVIEW_EXPOSURE_SELECT_MODE_AVA;
        case LIVEVIEW_Y_ID:                         return LIVEVIEW_Y_AVA;
        case LIVEVIEW_X_ID:                         return LIVEVIEW_X_AVA;
        case GPS_LOCK_ID:                           return GPS_LOCK_AVA;
        case AP_MODE_ID:                            return AP_MODE_AVA;
        case INTERNAL_BATTERY_PERCENTAGE_ID:        return INTERNAL_BATTERY_PERCENTAGE_AVA;
        case MICROPHONE_ACCESSORY_ID:               return MICROPHONE_ACCESSORY_AVA;
        case ZOOM_LEVEL_ID:                         return ZOOM_LEVEL_AVA;
        case STATUS_WIRELESS_BAND_ID:               return STATUS_WIRELESS_BAND_AVA;
        case ZOOM_AVAILABLE_ID:                     return ZOOM_AVAILABLE_AVA;
        case MOBILE_FRIENDLY_ID:                    return MOBILE_FRIENDLY_AVA;
        case FTU_ID:                                return FTU_AVA;
        case _5GHZ_AVAILABLE_ID:                    return _5GHZ_AVAILABLE_AVA;
        case READY_ID:                              return READY_AVA;
        case OTA_CHANGED_ID:                        return OTA_CHANGED_AVA;
        case COLD_ID:                               return COLD_AVA;
        case ROTATION_ID:                           return ROTATION_AVA;
        case ZOOM_WHILE_ENCODING_ID:                return ZOOM_WHILE_ENCODING_AVA;
        case FLATMODE_ID:                           return FLATMODE_AVA;
        case VIDEO_PRESET_ID:                       return VIDEO_PRESET_AVA;
        case PHOTO_PRESET_ID:                       return PHOTO_PRESET_AVA;
        case TIMELAPSE_PRESET_ID:                   return TIMELAPSE_PRESET_AVA;
        case PRESET_GROUP_ID:                       return PRESET_GROUP_AVA;
        case PRESET_ID:                             return PRESET_AVA;
        case PRESET_MODIFIED_ID:                    return PRESET_MODIFIED_AVA;
        case REMAINING_LIVE_BURSTS_ID:              return REMAINING_LIVE_BURSTS_AVA;
        case LIVE_BURSTS_ID:                        return LIVE_BURSTS_AVA;
        case CAPTURE_DELAY_ACTIVE_ID:               return CAPTURE_DELAY_ACTIVE_AVA;
        case MEDIA_MOD_STATE_ID:                    return MEDIA_MOD_STATE_AVA;
        case TIME_WARP_SPEED_ID:                    return TIME_WARP_SPEED_AVA;
        case LENS_TYPE_ID:                          return LENS_TYPE_AVA;
        case LINUX_CORE_ID:                         return LINUX_CORE_AVA;
        case SCHEDULED_CAPTURE_PRESET_ID:           return SCHEDULED_CAPTURE_PRESET_AVA;
        case STATUS_SCHEDULED_CAPTURE_ID:           return STATUS_SCHEDULED_CAPTURE_AVA;
        case SD_CARD_WRITE_SPEED_ERROR_ID:          return SD_CARD_WRITE_SPEED_ERROR_AVA;
        case SD_CARD_ERRORS_ID:                     return SD_CARD_ERRORS_AVA;
        case STATUS_CAMERA_CONTROL_ID:              return STATUS_CAMERA_CONTROL_AVA;
        case USB_CONNECTED_ID:                      return USB_CONNECTED_AVA;
        case USE_CONTROLLED_ID:                     return USE_CONTROLLED_AVA;
        case SD_CARD_CAPACITY_ID:                   return SD_CARD_CAPACITY_AVA;
        case CAMERA_NAME_ID:                        return CAMERA_NAME_AVA;
        default: return 0;
    }
}

inline const int32_t GET_STATUS_SIZE_BY_ID(int32_t x ){
    switch(x) {
        case INTERNAL_BATTERY_BARS_ID:              return INTERNAL_BATTERY_BARS_SIZE;
        case PAIRING_STATE_ID:                      return PAIRING_STATE_SIZE;
        case LAST_PAIRING_TYPE_ID:                  return LAST_PAIRING_TYPE_SIZE;
        case WIFI_SCAN_STATE_ID:                    return WIFI_SCAN_STATE_SIZE;
        case WIFI_PROVISIONING_STATE_ID:            return WIFI_PROVISIONING_STATE_SIZE;
        case PRIMARY_STORAGE_ID:                    return PRIMARY_STORAGE_SIZE;
        case OTA_ID:                                return OTA_SIZE;
        case LIVEVIEW_EXPOSURE_SELECT_MODE_ID:      return LIVEVIEW_EXPOSURE_SELECT_MODE_SIZE;
        case MICROPHONE_ACCESSORY_ID:               return MICROPHONE_ACCESSORY_SIZE;
        case STATUS_WIRELESS_BAND_ID:               return STATUS_WIRELESS_BAND_SIZE;
        case ROTATION_ID:                           return ROTATION_SIZE;
        case MEDIA_MOD_STATE_ID:                    return MEDIA_MOD_STATE_SIZE;
        case TIME_WARP_SPEED_ID:                    return TIME_WARP_SPEED_SIZE;
        case STATUS_CAMERA_CONTROL_ID:              return STATUS_CAMERA_CONTROL_SIZE;
        default: return 0;
    }
}

inline const char** GET_STATUS_STRING_BY_ID(int32_t x ){
    switch(x) {
        case INTERNAL_BATTERY_BARS_ID:              return INTERNAL_BATTERY_BARS_STRING;
        case PAIRING_STATE_ID:                      return PAIRING_STATE_STRING;
        case LAST_PAIRING_TYPE_ID:                  return LAST_PAIRING_TYPE_STRING;
        case WIFI_SCAN_STATE_ID:                    return WIFI_SCAN_STATE_STRING;
        case WIFI_PROVISIONING_STATE_ID:            return WIFI_PROVISIONING_STATE_STRING;
        case PRIMARY_STORAGE_ID:                    return PRIMARY_STORAGE_STRING;
        case OTA_ID:                                return OTA_STRING;
        case LIVEVIEW_EXPOSURE_SELECT_MODE_ID:      return LIVEVIEW_EXPOSURE_SELECT_MODE_STRING;
        case MICROPHONE_ACCESSORY_ID:               return MICROPHONE_ACCESSORY_STRING;
        case STATUS_WIRELESS_BAND_ID:               return STATUS_WIRELESS_BAND_STRING;
        case ROTATION_ID:                           return ROTATION_STRING;
        case MEDIA_MOD_STATE_ID:                    return MEDIA_MOD_STATE_STRING;
        case TIME_WARP_SPEED_ID:                    return TIME_WARP_SPEED_STRING;
        case STATUS_CAMERA_CONTROL_ID:              return STATUS_CAMERA_CONTROL_STRING;
        default: return 0;
    }
}

inline const int32_t* GET_STATUS_VALUE_BY_ID(int32_t x ){
    switch(x) {
        case INTERNAL_BATTERY_BARS_ID:              return INTERNAL_BATTERY_BARS_VALUE;
        case PAIRING_STATE_ID:                      return PAIRING_STATE_VALUE;
        case LAST_PAIRING_TYPE_ID:                  return LAST_PAIRING_TYPE_VALUE;
        case WIFI_SCAN_STATE_ID:                    return WIFI_SCAN_STATE_VALUE;
        case WIFI_PROVISIONING_STATE_ID:            return WIFI_PROVISIONING_STATE_VALUE;
        case PRIMARY_STORAGE_ID:                    return PRIMARY_STORAGE_VALUE;
        case OTA_ID:                                return OTA_VALUE;
        case LIVEVIEW_EXPOSURE_SELECT_MODE_ID:      return LIVEVIEW_EXPOSURE_SELECT_MODE_VALUE;
        case MICROPHONE_ACCESSORY_ID:               return MICROPHONE_ACCESSORY_VALUE;
        case STATUS_WIRELESS_BAND_ID:               return STATUS_WIRELESS_BAND_VALUE;
        case ROTATION_ID:                           return ROTATION_VALUE;
        case MEDIA_MOD_STATE_ID:                    return MEDIA_MOD_STATE_VALUE;
        case TIME_WARP_SPEED_ID:                    return TIME_WARP_SPEED_VALUE;
        case STATUS_CAMERA_CONTROL_ID:              return STATUS_CAMERA_CONTROL_VALUE;
        default: return 0;
    }
}


#endif
