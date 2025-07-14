#ifndef ROCKET_HPP
#define ROCKET_HPP

#include <string>
#include "Telemetry.hpp" // for Orientation struct
#include "CelestialBody.hpp" // for Vec3

class SolarSystem; // forward declaration

class Rocket {
private:
    double fuelLevel;         // in percentage (0-100)
    Vec3 position;            // in meters
    Vec3 velocity;            // in m/s
    double mass;              // in kilograms
    double thrust;            // in Newtons
    double dragCoefficient;   // simplistic drag coefficient
    int currentStage;         // 1 or 2
    std::string status;       // e.g., "Idle", "Launching", "In Flight"
    Orientation orientation;  // current rocket orientation

public:
    Rocket();
    
    void startLaunch();
    void update(double deltaTime, const SolarSystem* system = nullptr);  // simulate flight each second
    void stageSeparation();
    void abortMission();

    // Orientation accessors
    void setOrientation(const Orientation &ori);
    Orientation getOrientation() const;

    double getFuelLevel() const;
    Vec3 getPosition() const;
    Vec3 getVelocityVector() const;
    double getAltitude() const;      // z position
    double getVelocity() const;      // magnitude
    std::string getStatus() const;
};

#endif
