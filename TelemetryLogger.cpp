#include "TelemetryLogger.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include "SolarSystem.hpp"

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

void TelemetryLogger::logDetailed(double altitude, double velocity,
                                  const Vec3& position, const Vec3& velocityVec,
                                  double temperature, const Orientation& orientation,
                                  const SolarSystem* system) {
    if (!initialized_) {
        if (!initialize()) {
            return;
        }
    }

    std::ostringstream oss;
    oss.setf(std::ios::fixed);
    oss.precision(2);
    oss << "{";
    oss << "\"altitude\":" << altitude << ",";
    oss << "\"velocity\":" << velocity << ",";
    oss << "\"temperature\":" << temperature << ",";
    oss << "\"pitch\":" << orientation.pitch << ",";
    oss << "\"yaw\":" << orientation.yaw << ",";
    oss << "\"roll\":" << orientation.roll << ",";
    oss << "\"position\":{\"x\":" << position.x
        << ",\"y\":" << position.y
        << ",\"z\":" << position.z << "},";
    oss << "\"velocityVec\":{\"x\":" << velocityVec.x
        << ",\"y\":" << velocityVec.y
        << ",\"z\":" << velocityVec.z << "}";

    if (system && system->size() > 0) {
        oss << ",\"bodies\":[";
        for (std::size_t i = 0; i < system->size(); ++i) {
            const CelestialBody& b = system->getBody(i);
            oss << "{\"name\":\"" << b.getName() << "\",";
            oss << "\"x\":" << b.getPosition().x << ",";
            oss << "\"y\":" << b.getPosition().y << ",";
            oss << "\"z\":" << b.getPosition().z << "}";
            if (i + 1 < system->size()) oss << ",";
        }
        oss << "]";
    }
    oss << "}\n";

    std::string msg = oss.str();
    sendto(sockfd_, msg.c_str(), msg.size(), 0,
           reinterpret_cast<struct sockaddr*>(&serverAddr_), sizeof(serverAddr_));
}
