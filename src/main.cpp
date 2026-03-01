#include <iostream>
#include <filesystem>
#include "LoadBalancer.h"

int main() {
    // Create logs directory if it doesn't exist
    std::filesystem::create_directories("logs");
    
    int numServers;
    int simulationTime;

    std::cout << "=== LOAD BALANCER ===" << std::endl;
    std::cout << "Enter number of initial servers (1-100): ";
    std::cin >> numServers;

    std::cout << "Enter number of clock cycles to simulate (100-50000): ";
    std::cin >> simulationTime;

    // input validation
    if (numServers < 1 || numServers > 100 || simulationTime < 1) {
        std::cerr << "Error: Invalid input." << std::endl;
        std::cerr << "Servers: 1-100, Cycles: must be positive" << std::endl;
        return 1;
    }

    std::cout << "\nStarting simulation..." << std::endl;
    std::cout << "Initial servers: " << numServers << std::endl;
    std::cout << "Simulation cycles: " << simulationTime << std::endl;
    std::cout << "Initial queue size: " << numServers * 100 << " requests" << std::endl;
    std::cout << "Scaling thresholds: " << 50 * numServers << "-" << 80 * numServers << " requests" << std::endl;
    std::cout << "=====================================\n" << std::endl;

    LoadBalancer lb(numServers, 10);
    lb.runSimulation(simulationTime);

    std::cout << "\n=====================================\n" << std::endl;
    std::cout << "Simulation complete!" << std::endl;
    std::cout << "Check logs/loadbalancer.log for detailed log." << std::endl;

    return 0;
}