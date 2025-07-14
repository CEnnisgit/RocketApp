#ifndef ROCKET_HPP
#define ROCKET_HPP

#include <string>
#include "Telemetry.hpp" // for Orientation struct

class Rocket {
private:
    double fuelLevel;         // in percentage (0-100)
    double altitude;          // in meters
    double velocity;          // in m/s
    double mass;              // in kilograms
    double thrust;            // in Newtons
    double dragCoefficient;   // simplistic drag coefficient
    int currentStage;         // 1 or 2
    std::string status;       // e.g., "Idle", "Launching", "In Flight"
    Orientation orientation;  // current rocket orientation

public:
    Rocket();
    
    void startLaunch();
    void update(double deltaTime);  // simulate flight each second
    void stageSeparation();
    void abortMission();

    // Orientation accessors
    void setOrientation(const Orientation &ori);
    Orientation getOrientation() const;

    double getFuelLevel() const;
    double getAltitude() const;
    double getVelocity() const;
    std::string getStatus() const;
};

#endif
