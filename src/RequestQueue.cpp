/**
 * @file RequestQueue.cpp
 * @brief Implementation of RequestQueue class for FIFO request management
 * @author Kamryn Schock
 * @date March 2026
 */

#include "RequestQueue.h"

void RequestQueue::enqueue(const Request& request) {
    queue.push(request);
}

Request RequestQueue::dequeue() {
    if (queue.empty()) {
        return Request("", "", 0, 'P', 0); // return default/empty request if queue is empty
    }

    Request request = queue.front();
    queue.pop();
    return request;
}

bool RequestQueue::isEmpty() const {
    return queue.empty();
}

int RequestQueue::size() const {
    return queue.size();
}