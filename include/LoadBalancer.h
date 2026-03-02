/**
 * @file LoadBalancer.h
 * @brief Load Balancer class for managing web servers and request distribution
 * @author Kamryn Schock
 * @date March 2026
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <string>
#include "WebServer.h"
#include "RequestQueue.h"
#include "Config.h"

/**
 * @class LoadBalancer
 * @brief Manages web servers and distributes incoming requests with dynamic scaling
 * 
 * The LoadBalancer class handles dynamic server scaling, request dispatching,
 * load monitoring, and firewall protection to maintain optimal performance.
 * It automatically scales servers up/down based on queue size thresholds.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructor for LoadBalancer
     * @param initialServers Number of servers to start with (-1 = use config)
     * @param cooldown Cooldown period between scaling operations (-1 = use config)
     * @param configFile Path to configuration file
     */
    LoadBalancer(int initialServers = -1, int cooldown = -1, const std::string& configFile = "config/settings.conf");
    
    /**
     * @brief Runs the load balancer simulation
     * @param cycles Number of clock cycles to simulate (-1 = use config default)
     */
    void runSimulation(int cycles = -1);
    
    /**
     * @brief Generates random requests and adds them to the queue
     * @param count Number of requests to generate (default: 1)
     */
    void generateRequests(int count = 1);
    
    /**
     * @brief Dispatches requests from queue to available servers
     */
    void dispatchRequests();
    
    /**
     * @brief Scales servers up or down based on queue size thresholds
     */
    void scaleServers();
    
    /**
     * @brief Adds a new server to the server pool
     */
    void addServer();
    
    /**
     * @brief Removes a server from the pool (preferably idle servers)
     */
    void removeServer();
    
    /**
     * @brief Checks if an IP address should be blocked by firewall
     * @param ip IP address to check
     * @return true if IP should be blocked, false otherwise
     */
    bool blockIP(const std::string& ip);
    
    /**
     * @brief Logs an event to the log file with timestamp
     * @param message Event message to log
     */
    void logEvent(const std::string& message);
    
    /**
     * @brief Gets current queue size
     * @return Number of requests in queue
     */
    int getQueueSize() const;
    
    /**
     * @brief Gets current server count
     * @return Number of active servers
     */
    int getServerCount() const;
    
    /**
     * @brief Gets current simulation cycle
     * @return Current clock cycle
     */
    int getCurrentCycle() const;

private:
    std::vector<WebServer> servers;        ///< Pool of web servers
    RequestQueue requestQueue;             ///< Queue of pending requests
    Config config;                         ///< Configuration settings
    int clock;                            ///< Current simulation time
    int cooldown;                         ///< Cooldown between scaling operations
    int lastScaleTime;                    ///< Last time servers were scaled
    
    int minRequestsPerCycle;              ///< Minimum requests generated per cycle
    int maxRequestsPerCycle;              ///< Maximum requests generated per cycle
    int minProcessingTime;                ///< Minimum processing time for requests
    int maxProcessingTime;                ///< Maximum processing time for requests
    int lowerThresholdMultiplier;         ///< Lower scaling threshold (50)
    int upperThresholdMultiplier;         ///< Upper scaling threshold (80)
    int logInterval;                      ///< Interval for status logging
    bool firewallEnabled;                 ///< Whether firewall is enabled
};

#endif