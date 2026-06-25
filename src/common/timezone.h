/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include <chrono>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
#endif

int32_t get_timezone_offset_minutes() {
#ifdef _WIN32
    // Windows-specific implementation using Win32 API
    TIME_ZONE_INFORMATION tzInfo;
    DWORD result = GetTimeZoneInformation(&tzInfo);
    
    if (result == TIME_ZONE_ID_INVALID) {
        return 0;
    }
    
    // Bias is in minutes
    // Negative bias = east of UTC (e.g., UTC+8 = -480)
    // Positive bias = west of UTC (e.g., UTC-5 = 300)
    // We want positive = east, so negate
    return -tzInfo.Bias;
    
#elif defined(__unix__) || defined(__APPLE__)
    // POSIX systems (Linux, macOS, BSD)
    tzset();  // Initialize timezone global
    
    // timezone = seconds West of UTC
    // Negate to get East, divide by 60 for minutes
    return static_cast<int32_t>(-(timezone) / 60);
    
#else
    // Fallback: Manual calculation for unknown platforms
    time_t now = time(nullptr);
    struct tm local_tm = *localtime(&now);
    struct tm utc_tm = *gmtime(&now);
    
    time_t local_time = mktime(&local_tm);
    time_t utc_time = mktime(&utc_tm);
    
    double diff = difftime(local_time, utc_time);
    return static_cast<int32_t>(diff / 60);
#endif
}