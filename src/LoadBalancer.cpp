#include "LoadBalancer.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <filesystem>

const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";
const std::string RESET = "\033[0m";

LoadBalancer::LoadBalancer(int initialServers, int cooldown)
    : clock(0),
      cooldown(cooldown),
      lastScaleTime(0) {
    
    // logs directory
    std::filesystem::create_directories("logs");
    
    // create initial servers
    for (int i = 0; i < initialServers; i++) {
        servers.emplace_back(i);
    }
    
    // generate initial full queue (servers * 100)
    generateRequests(initialServers * 100);
    
    std::cout << "LoadBalancer initialized with " << initialServers << " servers" << std::endl;
    logEvent("LoadBalancer initialized with " + std::to_string(initialServers) + " servers");
}

void LoadBalancer::runSimulation(int cycles) {
    std::cout << "Starting simulation for " << cycles << " clock cycles..." << std::endl;
    logEvent("Starting simulation for " + std::to_string(cycles) + " cycles");
    
    for (int cycle = 0; cycle < cycles; cycle++) {
        clock++;
        
        // generate new requests randomly (5-15 per cycle)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> newRequestDist(5, 15);
        int newRequests = newRequestDist(gen);
        generateRequests(newRequests);
        
        // dispatch requests to available servers
        dispatchRequests();
        
        // process one cycle on all servers
        for (auto& server : servers) {
            server.processCycle();
        }
        
        // scale servers if needed
        if (clock - lastScaleTime >= cooldown) {
            scaleServers();
        }
        
        // log status every 1000 cycles
        if (cycle % 1000 == 0) {
            std::cout << BLUE << "Cycle " << cycle << ": " << RESET 
                      << "Queue: " << MAGENTA << requestQueue.size() << RESET
                      << ", Servers: " << GREEN << servers.size() << RESET << std::endl;
            logEvent("Status - Cycle: " + std::to_string(cycle) + 
                    ", Queue: " + std::to_string(requestQueue.size()) + 
                    ", Servers: " + std::to_string(servers.size()));
        }
    }
    
    // final stats
    std::cout << "Final queue size: " << requestQueue.size() << std::endl;
    std::cout << "Final server count: " << servers.size() << std::endl;
    
    logEvent("Simulation completed - Final queue: " + std::to_string(requestQueue.size()) + 
            ", Final servers: " + std::to_string(servers.size()));
}

void LoadBalancer::generateRequests(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < count; i++) {
        // generate random IP addresses
        std::uniform_int_distribution<> ipDist(1, 254);
        std::string ipIn = std::to_string(ipDist(gen)) + "." + 
                           std::to_string(ipDist(gen)) + "." + 
                           std::to_string(ipDist(gen)) + "." + 
                           std::to_string(ipDist(gen));
        
        std::string ipOut = std::to_string(ipDist(gen)) + "." + 
                            std::to_string(ipDist(gen)) + "." + 
                            std::to_string(ipDist(gen)) + "." + 
                            std::to_string(ipDist(gen));
        
        // generate processing time (1-10 cycles)
        std::uniform_int_distribution<> timeDist(1, 10);
        int processingTime = timeDist(gen);
        
        // generate job type (P or S)
        std::uniform_int_distribution<> typeDist(0, 1);
        char jobType = typeDist(gen) == 0 ? 'P' : 'S';
        
        // check for blocked IPs before adding to queue
        if (!blockIP(ipIn)) {
            Request newRequest(ipIn, ipOut, processingTime, jobType, clock);
            requestQueue.enqueue(newRequest);
        }
    }
}

void LoadBalancer::dispatchRequests() {
    // find available servers and assign requests
    for (auto& server : servers) {
        if (server.isIdle() && !requestQueue.isEmpty()) {
            Request request = requestQueue.dequeue();
            server.assignRequest(request);
        }
    }
}

void LoadBalancer::scaleServers() {
    int queueSize = requestQueue.size();
    int serverCount = servers.size();
    int lowerThreshold = 50 * serverCount;
    int upperThreshold = 80 * serverCount;
    
    if (queueSize < lowerThreshold && serverCount > 1) {
        removeServer();
        lastScaleTime = clock;
        logEvent("Scaled DOWN - Queue: " + std::to_string(queueSize) + 
                ", Servers: " + std::to_string(servers.size()) + 
                ", Threshold: " + std::to_string(lowerThreshold));
    } else if (queueSize > upperThreshold) {
        addServer();
        lastScaleTime = clock;
        logEvent("Scaled UP - Queue: " + std::to_string(queueSize) + 
                ", Servers: " + std::to_string(servers.size()) + 
                ", Threshold: " + std::to_string(upperThreshold));
    }
}

void LoadBalancer::addServer() {
    int newId = servers.size();
    servers.emplace_back(newId);
    std::cout << GREEN << "↑ ADDED " << RESET << "server " << newId 
              << ". Total: " << CYAN << servers.size() << RESET << std::endl;
}

void LoadBalancer::removeServer() {
    if (servers.size() > 1) {
        auto it = std::find_if(servers.begin(), servers.end(),
                              [](const WebServer& server) { return server.isIdle(); });
        
        if (it != servers.end()) {
            int removedId = it->getId();
            servers.erase(it);
            std::cout << RED << "↓ REMOVED " << RESET << "idle server " << removedId 
                      << ". Total: " << CYAN << servers.size() << RESET << std::endl;
        } else {
            int removedId = servers.back().getId();
            servers.pop_back();
            std::cout << YELLOW << "↓ REMOVED " << RESET << "busy server " << removedId 
                      << ". Total: " << CYAN << servers.size() << RESET << std::endl;
        }
    }
}

bool LoadBalancer::blockIP(const std::string& ip) {
    // simple firewall: block suspicious IP ranges
    // block 192.168.1.x (simulating internal/suspicious traffic)
    if (ip.substr(0, 9) == "192.168.1") {
        logEvent("BLOCKED IP: " + ip + " (suspicious range)");
        return true;
    }
    
    // block IPs ending in .666 (simulating malicious pattern)
    if (ip.substr(ip.length() - 4) == ".666") {
        logEvent("BLOCKED IP: " + ip + " (malicious pattern)");
        return true;
    }
    
    return false;
}

void LoadBalancer::logEvent(const std::string& message) {
    std::ofstream logFile("logs/loadbalancer.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << "[Cycle " << std::setw(6) << std::setfill('0') << clock << "] " 
                << message << std::endl;
        logFile.close();
    }
}

int LoadBalancer::getQueueSize() const {
    return requestQueue.size();
}

int LoadBalancer::getServerCount() const {
    return servers.size();
}

int LoadBalancer::getCurrentCycle() const {
    return clock;
}
