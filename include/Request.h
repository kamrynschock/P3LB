#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
public:
    Request(const std::string& ipIn,
            const std::string& ipOut,
            int processingTime,
            char jobType,
            int arrivalTime);

    std::string getIpIn() const;
    std::string getIpOut() const;
    int getProcessingTime() const;
    char getJobType() const;
    int getArrivalTime() const;

private:
    std::string ipIn;
    std::string ipOut;
    int processingTime;
    char jobType; // 'P' or 'S'
    int arrivalTime;
};

#endif