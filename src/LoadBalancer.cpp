#include "LoadBalancer.h"

LoadBalancer::LoadBalancer(int initialServers, int cooldown)
    : clock(0),
      cooldown(cooldown),
      lastScaleTime(0) {
    // TODO create initial servers
}

void LoadBalancer::runSimulation(int cycles) {
    // TODO
}

void LoadBalancer::generateRequests() {
    // TODO
}

void LoadBalancer::dispatchRequests() {
    // TODO
}

void LoadBalancer::scaleServers() {
    // TODO
}

void LoadBalancer::addServer() {
    // TODO
}

void LoadBalancer::removeServer() {
    // TODO
}

bool LoadBalancer::blockIP(const std::string& ip) {
    // TODO
    return false;
}

void LoadBalancer::logEvent(const std::string& message) {
    // TODO
}
