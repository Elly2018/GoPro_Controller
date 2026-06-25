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
        std::cerr << "Error: Could not open the file: " << homedir << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inFile, line)) {
        std::vector<std::string> words = std::vector<std::string>();
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) { // Extracts words separated by any whitespace
            words.push_back(word);
        }
        if(words.size() > 0){
            camera_ips.push_back(words[0]);
        }
        if(words.size() > 1){
            camera_name.insert_or_assign(words[0], words[1]);
        }
    }
    inFile.close();
}

void gopro_controller_local_update_record(gopro_controller& controller) {
    std::string homedir = "";
    homedir += "record.txt";
    std::cout << "Trying export data to: " << homedir << std::endl;
    std::ofstream outFile( homedir.c_str() );
    
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open the file." << homedir << std::endl;
        return; // Return with an error code
    }
    for(int32_t i = 0; i < camera_ips.size(); i++){
        std::string& c = camera_ips.at(i);
        if(camera_name.count(c)){
            outFile << c << " " << camera_name.at(c)  << "\n";
            std::cout << "  Export " << c << " with name " << camera_name.at(c) << std::endl;
        }else{
            outFile << c << "\n";
            std::cout << "  Export " << c << std::endl;
        }
    }
    outFile.close();
}

SingleResponse GoProController::_getSingleResponse(std::string target, std::string suffix){
    std::string url = GetRemoteURLByIP(target) + suffix;
    std::cout << "CURL: " << url << std::endl;
    return SingleResponse(target, exec(url));
}

std::vector<SingleResponse> GoProController::_getAllResponse(std::vector<std::string> targets, std::string suffix){
    std::vector<std::string> urls = std::vector<std::string>();
    std::vector<SingleResponse> result = std::vector<SingleResponse>();
    for(int32_t i = 0; i < targets.size(); i++){
        urls.push_back(GetRemoteURLByIP(targets[i]) + suffix);
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

std::string GoProController::base64_encode(const std::vector<u_char>& data) {
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