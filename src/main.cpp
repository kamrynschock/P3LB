#include <iostream>
#include "LoadBalancer.h"

int main() {
    int numServers;
    int simulationTime;

    std::cout << "Enter number of initial servers: ";
    std::cin >> numServers;

    std::cout << "Enter number of clock cycles to simulate: ";
    std::cin >> simulationTime;

    LoadBalancer lb(numServers, 10);
    lb.runSimulation(simulationTime);

    return 0;
}