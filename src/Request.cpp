/**
 * @file Request.cpp
 * @brief Implementation of Request class for web request representation
 * @author Kamryn Schock
 * @date March 2026
 */

#include "Request.h"

Request::Request(const std::string& ipIn, 
                 const std::string& ipOut, 
                 int processingTime, 
                 char jobType, 
                 int arrivalTime)
    : ipIn(ipIn),
      ipOut(ipOut),
      processingTime(processingTime),
      jobType(jobType),
      arrivalTime(arrivalTime) {}

std::string Request::getIpIn() const {
    return ipIn;
}

std::string Request::getIpOut() const {
    return ipOut;
}

int Request::getProcessingTime() const {
    return processingTime;
}

char Request::getJobType() const {
    return jobType;
}

int Request::getArrivalTime() const {
    return arrivalTime;
}