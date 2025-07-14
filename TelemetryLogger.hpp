#ifndef TELEMETRYLOGGER_HPP
#define TELEMETRYLOGGER_HPP

#include <string>
#include <netinet/in.h>
#include "Telemetry.hpp" // for Orientation struct
#include "CelestialBody.hpp" // for Vec3 and CelestialBody info

class SolarSystem; // forward declaration

class TelemetryLogger {
public:
    TelemetryLogger(const std::string& host = "127.0.0.1", int port = 7000);
    ~TelemetryLogger();

    bool initialize();
    void log(double altitude, double velocity,
             double temperature, const Orientation& orientation);
    void logDetailed(double altitude, double velocity,
                     const Vec3& position, const Vec3& velocityVec,
                     double temperature, const Orientation& orientation,
                     const SolarSystem* system = nullptr);

private:
    std::string host_;
    int port_;
    int sockfd_;
    struct sockaddr_in serverAddr_;
    bool initialized_;
};

#endif // TELEMETRYLOGGER_HPP
