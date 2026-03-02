#include "Config.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

Config::Config(const std::string& configFile) {
    loadConfig(configFile);
}

void Config::loadConfig(const std::string& configFile) {
    std::ifstream file(configFile);
    if (!file.is_open()) {
        std::cout << "Warning: Could not open config file '" << configFile 
                  << "'. Using default values." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        
        // skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // parse key=value pairs
        size_t equalPos = line.find('=');
        if (equalPos != std::string::npos) {
            std::string key = trim(line.substr(0, equalPos));
            std::string value = trim(line.substr(equalPos + 1));
            settings[key] = value;
        }
    }
    
    file.close();
    std::cout << "Loaded configuration from: " << configFile << std::endl;
}

int Config::getInt(const std::string& key, int defaultValue) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
        try {
            return std::stoi(it->second);
        } catch (const std::exception&) {
            std::cout << "Warning: Invalid integer value for '" << key 
                      << "'. Using default: " << defaultValue << std::endl;
        }
    }
    return defaultValue;
}

std::string Config::getString(const std::string& key, const std::string& defaultValue) const {
    auto it = settings.find(key);
    return (it != settings.end()) ? it->second : defaultValue;
}

bool Config::getBool(const std::string& key, bool defaultValue) const {
    auto it = settings.find(key);
    if (it != settings.end()) {
        std::string value = it->second;
        return (value == "true" || value == "1" || value == "yes");
    }
    return defaultValue;
}

std::string Config::trim(const std::string& str) const {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

void Config::printConfig() const {
    std::cout << "\n=== Configuration Settings ===" << std::endl;
    for (const auto& pair : settings) {
        std::cout << pair.first << " = " << pair.second << std::endl;
    }
    std::cout << "==============================\n" << std::endl;
}