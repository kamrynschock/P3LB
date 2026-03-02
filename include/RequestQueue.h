/**
 * @file RequestQueue.h
 * @brief RequestQueue class implementing FIFO queue for web requests
 * @author Kamryn Schock
 * @date March 2026
 */

#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

/**
 * @class RequestQueue
 * @brief First-In-First-Out queue for managing incoming web requests
 * 
 * The RequestQueue class provides a thread-safe FIFO queue for storing
 * and retrieving web requests in the load balancer system.
 */
class RequestQueue {
public:
    /**
     * @brief Adds a request to the back of the queue
     * @param request Request object to be queued
     */
    void enqueue(const Request& request);
    
    /**
     * @brief Removes and returns the front request from queue
     * @return Request object from front of queue (empty request if queue is empty)
     */
    Request dequeue();
    
    /**
     * @brief Checks if the queue is empty
     * @return true if queue has no requests, false otherwise
     */
    bool isEmpty() const;
    
    /**
     * @brief Gets the number of requests in the queue
     * @return Number of requests currently queued
     */
    int size() const;

private:
    std::queue<Request> queue; ///< STL queue container for requests
};

#endif