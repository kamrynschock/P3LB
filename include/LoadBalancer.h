#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <string>
#include "WebServer.h"
#include "RequestQueue.h"

class LoadBalancer {
public:
    LoadBalancer(int initialServers, int cooldown);

    void runSimulation(int cycles);

private:
    void generateRequests();
    void dispatchRequests();
    void scaleServers();
    void addServer();
    void removeServer();
    bool blockIP(const std::string& ip);
    void logEvent(const std::string& message);

    std::vector<WebServer> servers;
    RequestQueue requestQueue;

    int clock;
    int cooldown;
    int lastScaleTime;
};

#endif