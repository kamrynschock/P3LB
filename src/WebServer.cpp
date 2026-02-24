#include "WebServer.h"

WebServer::WebServer(int id)
    : id(id),
      busy(true),
      remainingTime(0),
      currentRequest("", "", 0, 'P', 0) {}

bool WebServer::isIdle() const {
    // TODO
    return true;
}

void WebServer::assignRequest(const Request& request) {
    // iTODO
}

void WebServer::processCycle() {
    // TODO
}