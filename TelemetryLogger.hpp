#ifndef TELEMETRYLOGGER_HPP
#define TELEMETRYLOGGER_HPP

#include <string>
#include <netinet/in.h>
#include "Telemetry.hpp" // for Orientation struct

class TelemetryLogger {
public:
    TelemetryLogger(const std::string& host = "127.0.0.1", int port = 7000);
    ~TelemetryLogger();

    bool initialize();
    void log(double altitude, double velocity,
             double temperature, const Orientation& orientation);

private:
    std::string host_;
    int port_;
    int sockfd_;
    struct sockaddr_in serverAddr_;
    bool initialized_;
};

#endif // TELEMETRYLOGGER_HPP
