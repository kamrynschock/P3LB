/**
 * @file Config.h
 * @brief Configuration management class for load balancer settings
 * @author Kamryn Schock
 * @date March 2026
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

/**
 * @class Config
 * @brief Manages configuration settings loaded from file
 *
 * The Config class reads key-value pairs from configuration files
 * and provides type-safe access to settings with default values.
 */
class Config {
public:
    /**
     * @brief Constructor that loads configuration from file
     * @param configFile Path to configuration file (default: config/settings.conf)
     */
    Config(const std::string& configFile = "config/settings.conf");

    /**
     * @brief Gets an integer value from configuration
     * @param key Configuration key name
     * @param defaultValue Value to return if key not found or invalid
     * @return Integer value from config or default
     */
    int getInt(const std::string& key, int defaultValue = 0) const;

    /**
     * @brief Gets a string value from configuration
     * @param key Configuration key name
     * @param defaultValue Value to return if key not found
     * @return String value from config or default
     */
    std::string getString(const std::string& key, const std::string& defaultValue = "") const;

    /**
     * @brief Gets a boolean value from configuration
     * @param key Configuration key name
     * @param defaultValue Value to return if key not found
     * @return Boolean value from config or default (true/1/yes = true)
     */
    bool getBool(const std::string& key, bool defaultValue = false) const;

    /**
     * @brief Loads configuration settings from file
     * @param configFile Path to configuration file to load
     */
    void loadConfig(const std::string& configFile);

    /**
     * @brief Prints all loaded configuration settings to console
     */
    void printConfig() const;

private:
    std::unordered_map<std::string, std::string> settings; ///< Key-value storage for settings

    /**
     * @brief Removes whitespace from beginning and end of string
     * @param str String to trim
     * @return Trimmed string
     */
    std::string trim(const std::string& str) const;
};

#endif