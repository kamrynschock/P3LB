#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"


class WebServer {
public:
    WebServer(int id);
    
    bool isIdle() const;
    void assignRequest(const Request& request);
    void processCycle();
    int getId() const;
    Request getCurrentRequest() const;
    int getRemainingTime() const;

private:
    int id;
    bool busy;
    int remainingTime;
    Request currentRequest;
};

#endif