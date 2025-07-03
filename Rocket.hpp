#ifndef ROCKET_HPP
#define ROCKET_HPP

#include <string>

class Rocket {
private:
    double fuelLevel;         // in percentage (0-100)
    double altitude;          // in meters
    double velocity;          // in m/s
    int currentStage;         // 1 or 2
    std::string status;       // e.g., "Idle", "Launching", "In Flight"

public:
    Rocket();
    
    void startLaunch();
    void update(double deltaTime);  // simulate flight each second
    void stageSeparation();
    void abortMission();

    double getFuelLevel() const;
    double getAltitude() const;
    double getVelocity() const;
    std::string getStatus() const;
};

#endif
