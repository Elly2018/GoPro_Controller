/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller_local.h"
#include "../gopro_controller.h"
#include "../../common/config.h"
#include <fstream>
#include <vector>
#include <string>

void gopro_controller_local_load_record(gopro_controller& controller) {
    std::cout << "Trying load data from: " << SERVER_CLIENT_RECORD_FILENAME << std::endl;
    std::ifstream inFile(SERVER_CLIENT_RECORD_FILENAME);

    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open the file: " << SERVER_CLIENT_RECORD_FILENAME << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inFile, line)) {
        if(!gopro_controller_local_element_have_slot(controller)) break;

        std::vector<std::string> words = std::vector<std::string>();
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) { // Extracts words separated by any whitespace
            words.push_back(word);
        }
        if(words.size() > 0){
            gopro_controller_local_element_add(controller, words[0]);
        }
        if(words.size() > 1){
            int32_t index = gopro_controller_local_element_add(controller, words[0]);
            gopro_controller_rename_cameras(controller, words[0], words[1]);
        }
    }
    inFile.close();
}

void gopro_controller_local_update_record(gopro_controller& controller) {
    std::cout << "Trying export data to: " << SERVER_CLIENT_RECORD_FILENAME << std::endl;
    std::ofstream outFile( SERVER_CLIENT_RECORD_FILENAME );
    
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open the file." << SERVER_CLIENT_RECORD_FILENAME << std::endl;
        return;
    }
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(strlen(e.name) > 0){
            outFile << e.ip << " " << e.name  << "\n";
            std::cout << "  Export " << e.ip << " with name " << e.name << std::endl;
        }else{
            outFile << e.ip << "\n";
            std::cout << "  Export " << e.ip << std::endl;
        }
    }
    outFile.close();
}

SingleResponse gopro_controller_local_get_response(gopro_controller& controller, const std::string target, const std::string suffix){
    std::string url = get_remote_URL_by_IP(target) + suffix;
    std::cout << "CURL: " << url << std::endl;
    return SingleResponse(target, exec(url));
}

std::vector<SingleResponse> gopro_controller_local_get_responses(gopro_controller& controller, const std::vector<std::string> targets, const std::string suffix){
    std::vector<std::string> urls = std::vector<std::string>();
    std::vector<SingleResponse> result = std::vector<SingleResponse>();
    for(int32_t i = 0; i < targets.size(); i++){
        urls.push_back(get_remote_URL_by_IP(targets[i]) + suffix);
    }
    std::vector<std::string> res = execs(urls);
    std::cout << "query all: " << res.size() << "/" << targets.size() << " " << suffix.c_str() << std::endl;;
    for(int32_t i = 0; i < targets.size(); i++){
        if(res[i].size() == 0){
            res[i] = "{}";
        }
        result.push_back(SingleResponse(
            targets[i],
            res[i]
        ));
    }
    return result;
}

std::string gopro_controller_local_base64_encode(gopro_controller& controller, const std::vector<u_char> &data) {
    static const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    std::string out;
    int val = 0, valb = -6;
    for (u_char c : data) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}