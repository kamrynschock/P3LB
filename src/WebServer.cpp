#include "WebServer.h"

WebServer::WebServer(int id)
    : id(id),
      busy(false),
      remainingTime(0),
      currentRequest("", "", 0, 'P', 0) {}

bool WebServer::isIdle() const {
    return !busy;
}

void WebServer::assignRequest(const Request& request) {
    if (!busy) {
        currentRequest = request;
        remainingTime = request.getProcessingTime();
        busy = true;
    }
}

void WebServer::processCycle() {
    if (busy && remainingTime > 0) {
        remainingTime--;
        if (remainingTime == 0) {
            busy = false;
        }
    }
}

int WebServer::getId() const {
    return id;
}

Request WebServer::getCurrentRequest() const {
    return currentRequest;
}

int WebServer::getRemainingTime() const {
    return remainingTime;
}