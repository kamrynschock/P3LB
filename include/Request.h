/**
 * @file Request.h
 * @brief Request class representing a web request with IP addresses and metadata
 * @author Kamryn Schock
 * @date March 2026
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @class Request
 * @brief Represents a web request with source/destination IPs and processing requirements
 * 
 * The Request class encapsulates all information needed for a web request including
 * IP addresses, processing time, job type, and arrival time.
 */
class Request {
public:
    /**
     * @brief Constructor for Request
     * @param ipIn Source IP address of the request
     * @param ipOut Destination IP address for the response
     * @param processingTime Time in clock cycles needed to process this request
     * @param jobType Type of job ('P' for Processing, 'S' for Streaming)
     * @param arrivalTime Clock cycle when request was created
     */
    Request(const std::string& ipIn,
            const std::string& ipOut,
            int processingTime,
            char jobType,
            int arrivalTime);

    /**
     * @brief Gets the source IP address
     * @return Source IP address as string
     */
    std::string getIpIn() const;
    
    /**
     * @brief Gets the destination IP address
     * @return Destination IP address as string
     */
    std::string getIpOut() const;
    
    /**
     * @brief Gets the processing time required
     * @return Processing time in clock cycles
     */
    int getProcessingTime() const;
    
    /**
     * @brief Gets the job type
     * @return Job type character ('P' or 'S')
     */
    char getJobType() const;
    
    /**
     * @brief Gets the arrival time
     * @return Clock cycle when request arrived
     */
    int getArrivalTime() const;

private:
    std::string ipIn;        ///< Source IP address
    std::string ipOut;       ///< Destination IP address
    int processingTime;      ///< Time needed to process request
    char jobType;           ///< Job type: 'P' (Processing) or 'S' (Streaming)
    int arrivalTime;        ///< When request was created
};

#endif