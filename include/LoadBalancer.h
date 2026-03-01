#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <string>
#include "WebServer.h"
#include "RequestQueue.h"
#include "Config.h"

class LoadBalancer {
public:
    LoadBalancer(int initialServers = -1, int cooldown = -1, const std::string& configFile = "config/settings.conf");
    
    void runSimulation(int cycles = -1);  // -1 means use config default
    void generateRequests(int count = 1);
    void dispatchRequests();
    void scaleServers();
    void addServer();
    void removeServer();
    bool blockIP(const std::string& ip);
    void logEvent(const std::string& message);
    
    int getQueueSize() const;
    int getServerCount() const;
    int getCurrentCycle() const;

private:
    std::vector<WebServer> servers;
    RequestQueue requestQueue;
    Config config;
    int clock;
    int cooldown;
    int lastScaleTime;
    
    int minRequestsPerCycle;
    int maxRequestsPerCycle;
    int minProcessingTime;
    int maxProcessingTime;
    int lowerThresholdMultiplier;
    int upperThresholdMultiplier;
    int logInterval;
    bool firewallEnabled;
};

#endif