#ifndef TELEMETRY_HPP
#define TELEMETRY_HPP

struct Orientation {
    double pitch; // Nose up/down angle
    double yaw;   // Nose left/right
    double roll;  // Barrel roll angle
};

class Telemetry {
private:
    double altitude;
    double velocity;
    double acceleration;
    double temperature;
    Orientation orientation;

public:
    Telemetry();

    void update(double deltaTime);

    double getAltitude() const;
    double getVelocity() const;
    double getAcceleration() const;
    double getTemperature() const;
    Orientation getOrientation() const;
};

#endif
