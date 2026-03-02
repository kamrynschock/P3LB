# Load Balancer Simulation

## Overview
This project implements a dynamic load balancer simulation that manages web servers and distributes incoming requests with automatic scaling capabilities.

## Features
- **Dynamic Server Scaling**: Automatically adds/removes servers based on queue size
- **Request Management**: FIFO queue for handling web requests
- **Firewall Protection**: Blocks suspicious IP addresses
- **Configuration System**: Settings loaded from config file
- **Comprehensive Logging**: Detailed event logging with timestamps

## Classes
- **LoadBalancer**: Main controller managing servers and requests
- **WebServer**: Individual server that processes requests
- **Request**: Represents a web request with IP addresses and metadata
- **RequestQueue**: FIFO queue for managing incoming requests
- **Config**: Configuration file management system

## Usage
```bash
./loadbalancer
# Follow prompts for server count and simulation time
```

## Configuration
Edit `config/settings.conf` to adjust simulation parameters.
