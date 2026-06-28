/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef GCG_IPHELPER_H
#define GCG_IPHELPER_H
#include <ctime>
#include <chrono>
#include <iomanip>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <map>
#include <string>
#include <algorithm>
#include <array>
#include <random>
#include <sstream>
#include <curl/curl.h>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

using json = nlohmann::json;

struct DownloadState {
    std::string url;
    std::string base_path;  // Path without extension
    FILE* fp = nullptr;
    std::string headers;
    std::string extension;
    bool file_opened = false;
};

inline std::string get_extension_from_content_type(const std::string& content_type) {
    // Remove charset and other parameters
    std::string mime = content_type;
    size_t semicolon = mime.find(';');
    if(semicolon != std::string::npos) {
        mime = mime.substr(0, semicolon);
    }
    
    // Trim whitespace
    mime.erase(0, mime.find_first_not_of(" \t\r\n"));
    mime.erase(mime.find_last_not_of(" \t\r\n") + 1);
    
    // Map common MIME types to extensions
    static const std::map<std::string, std::string> mime_map = {
        {"image/jpeg", ".jpg"},
        {"image/jpg", ".jpg"},
        {"image/png", ".png"},
        {"image/gif", ".gif"},
        {"image/webp", ".webp"},
        {"image/bmp", ".bmp"},
        {"image/svg+xml", ".svg"},
        {"video/mp4", ".mp4"},
        {"video/webm", ".webm"},
        {"video/quicktime", ".mov"},
        {"video/x-msvideo", ".avi"},
        {"video/mpeg", ".mpg"},
        {"audio/mpeg", ".mp3"},
        {"audio/wav", ".wav"},
        {"audio/ogg", ".ogg"},
        {"application/pdf", ".pdf"},
        {"application/json", ".json"},
        {"application/xml", ".xml"},
        {"text/html", ".html"},
        {"text/plain", ".txt"},
        {"text/css", ".css"},
        {"application/javascript", ".js"},
        {"application/zip", ".zip"},
        {"application/x-rar-compressed", ".rar"},
        {"application/x-7z-compressed", ".7z"},
    };
    
    auto it = mime_map.find(mime);
    if(it != mime_map.end()) {
        return std::string(it->second);
    }
    
    return ".bin";  // Default extension
}

inline size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata) {
    size_t numbytes = size * nitems;
    DownloadState* state = static_cast<DownloadState*>(userdata);
    
    // Store all headers
    state->headers.append(buffer, numbytes);
    
    // Parse this header line
    std::string line = std::string(buffer, numbytes);
    
    // Convert to lowercase for case-insensitive comparison
    std::string line_lower = line;
    for(char& c : line_lower){
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    
    // Look for Content-Type header
    if(line_lower.find("content-type:") == 0) {
        // Extract content type value
        size_t colon = line.find(':');
        if(colon != std::string::npos) {
            std::string content_type = line.substr(colon + 1);
            
            // Get extension from content type
            state->extension = get_extension_from_content_type(content_type);
            
            std::cout << "Content-Type: " << content_type;
            std::cout << "Extension: " << state->extension.c_str() << std::endl;
            
            // ✅ Open file now that we know the extension
            if(!state->file_opened) {
                std::string filepath = state->base_path + state->extension;
                state->fp = fopen(filepath.c_str(), "wb");
                
                if(state->fp) {
                    state->file_opened = true;
                    std::cout << "✓ Opened file: " << filepath << std::endl;
                } else {
                    std::cerr << "✗ Failed to open file: " << filepath << std::endl;
                }
            }
        }
    }
    
    // Also check for Content-Disposition (for filename hints)
    if(line_lower.find("content-disposition:") == 0) {
        // Example: Content-Disposition: attachment; filename="photo.jpg"
        size_t filename_pos = line_lower.find("filename=");
        if(filename_pos != std::string::npos) {
            std::string filename = line.substr(filename_pos + 9);
            
            // Remove quotes
            filename.erase(std::remove(filename.begin(), filename.end(), '"'), filename.end());
            filename.erase(std::remove(filename.begin(), filename.end(), '\''), filename.end());
            
            // Extract extension from filename
            size_t dot = filename.find_last_of('.');
            if(dot != std::string::npos) {
                state->extension = std::string(filename.substr(dot));
                state->extension.pop_back();
                state->extension.pop_back();
                for(char& c : state->extension){
                    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                }
                std::cout << "Filename from header: " << filename.c_str() << std::endl;
                std::cout << "Result from header: " << state->extension.c_str() << std::endl;
                
                // Re-open with correct extension if needed
                if(state->file_opened) {
                    fclose(state->fp);
                    state->file_opened = false;
                }
                
                std::string filepath = state->base_path + state->extension;
                state->fp = fopen(filepath.c_str(), "wb");
                if(state->fp) {
                    state->file_opened = true;
                    std::cout << "✓ Reopened file with correct name: " << filepath << std::endl;
                }
            }
        }
    }
    
    return numbytes;
}

inline size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    DownloadState* state = static_cast<DownloadState*>(userdata);
    
    // If file isn't open yet (no Content-Type header received), open with default extension
    if(!state->file_opened) {
        std::string filepath = state->base_path + ".bin";  // Fallback
        state->fp = fopen(filepath.c_str(), "wb");
        if(state->fp) {
            state->file_opened = true;
            std::cout << "⚠ Opened file with default extension: " << filepath << std::endl;
        } else {
            std::cerr << "✗ Failed to open fallback file: " << filepath << std::endl;
            return 0;  // Signal error to curl
        }
    }
    
    size_t written = fwrite(ptr, size, nmemb, state->fp);
    size_t expected = size * nmemb;

    if(written != expected) {
        std::cerr << "✗ Write error: expected " << expected << " bytes, wrote " << written << std::endl;
        return 0;  // Signal error
    }

    return written;
}

inline size_t write_callback_file(void *ptr, size_t size, size_t nmemb, FILE* file) {
    size_t memsize = fwrite(ptr, size, nmemb, file);
    return memsize;
}

inline size_t write_callback_pure(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

inline size_t write_callback_char(void* contents, size_t size, size_t nmemb, std::vector<u_char>* userp) {
    userp->insert(userp->end(), static_cast<u_char*>(contents), static_cast<u_char*>(contents) + size * nmemb);
    return size * nmemb;
}

inline std::string GetRemoteIPBySerial(std::string serial){
    if(serial.size() < 3){
        std::cerr << "Serial string must be at least 3" << "\n";
        return "";
    }

    return std::string("172.2") + serial[0] + std::string(".1") + serial[1] + serial[2] + std::string(".51");
}

inline std::string GetRemoteURLBySerial(std::string serial){
    if(serial.size() < 3){
        std::cerr << "Serial string must be at least 3" << "\n";
        return "";
    }

    return std::string("http://172.2") + serial[0] + std::string(".1") + serial[1] + serial[2] + std::string(".51:8080");
}

inline std::string get_remote_URL_by_IP(const std::string IP){
    if(IP.size() < 12){
        std::cerr << "The IP string size must larger than 12" << "\n";
        return "";
    }

    return std::string("http://") + IP + std::string(":8080");
}

inline json exec(std::string cmd, int64_t timeout = 1500L, int64_t connection_timeout = 1000L) {
    CURL* curl = curl_easy_init();
    std::string result = "";

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, cmd.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_pure);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, connection_timeout);
        CURLcode res = curl_easy_perform(curl);
        
        curl_easy_cleanup(curl);
    }else{
        std::cerr << "[Error] iphelper.h, Curl init failed" << std::endl;
    }

    if(json::accept(result)){
        return json::parse(result);
    }else{
        return result;
    }
}

inline std::vector<u_char> exec_byte(std::string cmd, int64_t timeout = 1500L, int64_t connection_timeout = 1000L){
    CURL* curl = curl_easy_init();
    std::vector<u_char> result = std::vector<u_char>();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, cmd.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_char);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT_MS, connection_timeout);
        CURLcode res = curl_easy_perform(curl);
        
        curl_easy_cleanup(curl);
    }else{
        std::cerr << "[Error] iphelper.h, Curl init failed" << std::endl;
    }

    return std::move(result);
}

inline std::vector<std::string> execs(std::vector<std::string> cmds) {
    CURLM* curlm = curl_multi_init();
    CURL* curl = NULL;
    int32_t still_running = 0;
    int32_t msgs_left = 0;
    int32_t http_status_code = 0;
    CURLMcode resm;
    CURLcode res;
    CURLMsg *msg=NULL;
    std::vector<std::string> result = std::vector<std::string>(cmds.size(), "");
     
    if(curlm) {
        curl_multi_setopt(curlm, CURLMOPT_MAX_TOTAL_CONNECTIONS, 64L);
        for(int32_t i = 0; i < cmds.size(); i++){
            CURL* curlb = curl_easy_init();
            curl_easy_setopt(curlb, CURLOPT_URL, cmds[i].c_str());
            curl_easy_setopt(curlb, CURLOPT_WRITEFUNCTION, write_callback_pure);
            curl_easy_setopt(curlb, CURLOPT_WRITEDATA, &result[i]);
            curl_easy_setopt(curlb, CURLOPT_TIMEOUT_MS, 1500L);
            curl_easy_setopt(curlb, CURLOPT_CONNECTTIMEOUT_MS, 1000L);
            curl_multi_add_handle(curlm, curlb);
        }

        curl_multi_perform(curlm, &still_running);

        do {
            int32_t numfds = 0;
            resm = curl_multi_wait(curlm, NULL, 0, 50, &numfds);

            if(res != CURLE_OK) {
                //std::cerr << "GET failed curl_multi_wait: " << numfds << "/" << cmds.size() << std::endl;
            }

            curl_multi_perform(curlm, &still_running);
        } while (still_running);
            
        while((msg = curl_multi_info_read(curlm, &msgs_left))){
            if (msg->msg == CURLMSG_DONE) {
                curl = msg->easy_handle;

                res = msg->data.result;
                if (res != CURLE_OK) {
                    //fprintf(stderr, "CURL error code: %d\n", msg->data.result);
                    continue;
                }

                // Get HTTP status code
                http_status_code=0;
                std::string buffer = "";

                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status_code);
                curl_easy_getinfo(curl, CURLINFO_PRIVATE, buffer);

                curl_multi_remove_handle(curlm, curl);
                curl_easy_cleanup(curl);
            }
            else {
                fprintf(stderr, "error: after curl_multi_info_read(), CURLMsg=%d\n", msg->msg);
            }
        }

        curl_multi_cleanup(curlm);
    }else{
        std::cerr << "Curl init failed" << std::endl;
    }

    return result;
}

inline void execs_download(std::vector<std::string> cmds, std::vector<std::string> ps) {
    CURLM* curlm = curl_multi_init();
    CURL* curl = NULL;
    int32_t still_running = 0;
    int32_t msgs_left = 0;
    int32_t http_status_code = 0;
    std::vector<DownloadState> states = std::vector<DownloadState>(cmds.size());
    std::vector<CURL*> handles = std::vector<CURL*>(cmds.size());
    CURLMcode resm;
    CURLcode res;
    CURLMsg *msg=NULL;

    if(curlm) {
        for(int32_t i = 0; i < cmds.size(); i++){
            CURL* curlb = curl_easy_init();
            handles[i] = curlb;
            states[i].url = cmds[i];
            states[i].base_path = ps[i];
            //curl_easy_setopt(curlb, CURLOPT_MAX_RECV_SPEED_LARGE, 200 * 1024);
            curl_easy_setopt(curlb, CURLOPT_URL, cmds[i].c_str());
            curl_easy_setopt(curlb, CURLOPT_HEADERFUNCTION, header_callback);
            curl_easy_setopt(curlb, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curlb, CURLOPT_HEADERDATA, &states[i]);
            curl_easy_setopt(curlb, CURLOPT_WRITEDATA, &states[i]);
            curl_multi_setopt(curlm, CURLMOPT_MAX_TOTAL_CONNECTIONS, 128L);
            curl_easy_setopt(curlb, CURLOPT_TIMEOUT_MS, 1200000L);
            curl_easy_setopt(curlb, CURLOPT_CONNECTTIMEOUT_MS, 10000L);
            curl_easy_setopt(curlb, CURLOPT_FOLLOWLOCATION, 1L);
            curl_multi_add_handle(curlm, curlb);
        }

        curl_multi_perform(curlm, &still_running);

        do {
            int32_t numfds = 0;
            resm = curl_multi_wait(curlm, NULL, 0, 1000, &numfds);

            if(res != CURLE_OK) {
                //std::cerr << "GET failed curl_multi_wait: " << numfds << "/" << cmds.size() << std::endl;
            }

            curl_multi_perform(curlm, &still_running);
        } while (still_running);

        while((msg = curl_multi_info_read(curlm, &msgs_left))){
            if (msg->msg == CURLMSG_DONE) {
                curl = msg->easy_handle;

                res = msg->data.result;
                if (res != CURLE_OK) {
                    //fprintf(stderr, "CURL error code: %d\n", msg->data.result);
                    continue;
                }

                // Get HTTP status code
                http_status_code=0;
                std::string buffer = "";

                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_status_code);
                curl_easy_getinfo(curl, CURLINFO_PRIVATE, buffer);

                curl_multi_remove_handle(curlm, curl);
                curl_easy_cleanup(curl);
            }
            else {
                fprintf(stderr, "error: after curl_multi_info_read(), CURLMsg=%d\n", msg->msg);
            }
        }

        for(size_t i = 0; i < cmds.size(); i++){
            if(states[i].fp){
                fclose(states[i].fp);
            }
        }

        curl_multi_cleanup(curlm);
    }else{
        std::cerr << "Curl init failed" << std::endl;
    }
}

///
/// Get the environment variable by key
///
inline std::string get_env_var( std::string const & key ) {
    char * val;
    val = getenv( key.c_str() );
    std::string retval = fs::current_path().string();
    if (val != NULL) {
        retval = val;
    }
    return retval;
}

///
/// You will get a string with format of
/// '%Y-%m-%d %H:%M:%S'
///
inline std::string getCurrentDateTimeString() {
    // Get the current time point
    auto now = std::chrono::system_clock::now();
    // Convert to time_t for compatibility with std::tm
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    // Convert to local time (or use std::gmtime for UTC)
    std::tm tm = *std::localtime(&t);

    // Use a stringstream to format the time
    std::ostringstream oss;
    // Format the time using std::put_time and a format specifier
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); 
    // Format specifier "%F %T" is a C++11 shortcut for "%Y-%m-%d %H:%M:%S"

    return oss.str();
}

namespace uuid {
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    inline std::string generate_uuid_v4() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
    }
}
#endif // IPHELPER_H
