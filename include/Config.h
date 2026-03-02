#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

class Config {
public:
    Config(const std::string& configFile = "config/settings.conf");
    
    int getInt(const std::string& key, int defaultValue = 0) const;
    std::string getString(const std::string& key, const std::string& defaultValue = "") const;
    bool getBool(const std::string& key, bool defaultValue = false) const;
    
    void loadConfig(const std::string& configFile);
    void printConfig() const;

private:
    std::unordered_map<std::string, std::string> settings;
    std::string trim(const std::string& str) const;
};

#endif