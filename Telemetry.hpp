#ifndef TELEMETRY_HPP
#define TELEMETRY_HPP

#include "CelestialBody.hpp" // for Vec3
struct Orientation {
    double pitch; // Nose up/down angle
    double yaw;   // Nose left/right
    double roll;  // Barrel roll angle
};

class Rocket; // forward declaration

class SolarSystem; // forward declaration

class Telemetry {
private:
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;
    double temperature;
    Orientation orientation;

public:
    Telemetry();

    void update(double deltaTime, Rocket* rocket = nullptr, const SolarSystem* system = nullptr);

    double getAltitude() const;           // z position
    double getVelocity() const;           // magnitude
    double getAcceleration() const;       // magnitude
    double getTemperature() const;
    Orientation getOrientation() const;
};

#endif
