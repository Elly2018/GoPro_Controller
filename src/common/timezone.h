/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef GCG_TIMEZONE_H
#define GCG_TIMEZONE_H
#include <chrono>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
#endif

int32_t get_timezone_offset_minutes() {
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD result = GetTimeZoneInformation(&tzInfo);
    if (result == TIME_ZONE_ID_INVALID) {
        return 0;
    }
    return -tzInfo.Bias;
#elif defined(__unix__) || defined(__APPLE__)
    tzset();
    return static_cast<int32_t>(-(timezone) / 60);
#else
    time_t now = time(nullptr);
    struct tm local_tm = *localtime(&now);
    struct tm utc_tm = *gmtime(&now);
    
    time_t local_time = mktime(&local_tm);
    time_t utc_time = mktime(&utc_tm);
    
    double diff = difftime(local_time, utc_time);
    return static_cast<int32_t>(diff / 60);
#endif
}

#endif