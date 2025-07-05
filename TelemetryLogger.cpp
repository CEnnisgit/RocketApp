#include "TelemetryLogger.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

TelemetryLogger::TelemetryLogger(const std::string& host, int port)
    : host_(host), port_(port), sockfd_(-1), initialized_(false) {}

TelemetryLogger::~TelemetryLogger() {
    if (sockfd_ != -1) {
        close(sockfd_);
    }
}

bool TelemetryLogger::initialize() {
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd_ < 0) {
        std::cerr << "Failed to create socket for telemetry" << std::endl;
        return false;
    }

    memset(&serverAddr_, 0, sizeof(serverAddr_));
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(port_);
    if (inet_pton(AF_INET, host_.c_str(), &serverAddr_.sin_addr) <= 0) {
        std::cerr << "Invalid telemetry host address" << std::endl;
        return false;
    }

    initialized_ = true;
    return true;
}

void TelemetryLogger::log(double altitude, double velocity,
                          double temperature, const Orientation& orientation) {
    if (!initialized_) {
        if (!initialize()) {
            return;
        }
    }

    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer),
                       "{\"altitude\":%.2f,\"velocity\":%.2f,\"temperature\":%.2f,"
                       "\"pitch\":%.2f,\"yaw\":%.2f,\"roll\":%.2f}\n",
                       altitude, velocity, temperature,
                       orientation.pitch, orientation.yaw, orientation.roll);
    if (len < 0) return;

    sendto(sockfd_, buffer, len, 0,
           reinterpret_cast<struct sockaddr*>(&serverAddr_), sizeof(serverAddr_));
}
