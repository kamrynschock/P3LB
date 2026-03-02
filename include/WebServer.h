/**
 * @file WebServer.h
 * @brief WebServer class representing an individual server that processes requests
 * @author Kamryn Schock
 * @date March 2026
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief Represents an individual web server that can process requests
 * 
 * The WebServer class manages the state of a single server, including
 * whether it's busy, what request it's processing, and how much time remains.
 */
class WebServer {
public:
    /**
     * @brief Constructor for WebServer
     * @param id Unique identifier for this server
     */
    WebServer(int id);
    
    /**
     * @brief Checks if the server is available for new requests
     * @return true if server is idle, false if busy
     */
    bool isIdle() const;
    
    /**
     * @brief Assigns a request to this server (if idle)
     * @param request The request to be processed
     */
    void assignRequest(const Request& request);
    
    /**
     * @brief Processes one clock cycle of the current request
     * 
     * Decrements remaining processing time and sets server to idle
     * when request is complete.
     */
    void processCycle();
    
    /**
     * @brief Gets the server's unique ID
     * @return Server ID number
     */
    int getId() const;
    
    /**
     * @brief Gets the current request being processed
     * @return Copy of the current request
     */
    Request getCurrentRequest() const;
    
    /**
     * @brief Gets remaining processing time for current request
     * @return Clock cycles remaining (0 if idle)
     */
    int getRemainingTime() const;

private:
    int id;                 ///< Unique server identifier
    bool busy;              ///< Whether server is processing a request
    int remainingTime;      ///< Clock cycles left for current request
    Request currentRequest; ///< Request currently being processed
};

#endif