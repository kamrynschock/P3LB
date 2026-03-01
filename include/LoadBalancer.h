#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <string>
#include "WebServer.h"
#include "RequestQueue.h"

class LoadBalancer {
public:
    LoadBalancer(int initialServers, int cooldown = 10);
    
    void runSimulation(int cycles);
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
    int clock;
    int cooldown;
    int lastScaleTime;
};

#endif