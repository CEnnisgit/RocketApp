#include "Rocket.hpp"
#include <iostream>

Rocket::Rocket() {
    fuelLevel = 100.0;
    altitude = 0.0;
    velocity = 0.0;
    currentStage = 1;
    status = "Idle";
    orientation = {0.0, 0.0, 0.0};
}

void Rocket::startLaunch() {
    if (status == "Idle") {
        status = "Launching";
        std::cout << "Launch initiated!\n";
    }
}

void Rocket::update(double deltaTime) {
    if (status == "Launching" || status == "In Flight") {
        if (fuelLevel > 0) {
            fuelLevel -= 0.5 * deltaTime; // basic consumption model
            velocity += 9.8 * deltaTime;  // gravity offset
            altitude += velocity * deltaTime;
            status = "In Flight";

            // Simple attitude control trying to stabilize orientation
            orientation.pitch *= 0.98;
            orientation.yaw   *= 0.98;
            orientation.roll  *= 0.98;
        } else {
            velocity = 0;
            std::cout << "Fuel depleted.\n";
        }
    }
}

void Rocket::stageSeparation() {
    if (currentStage == 1) {
        currentStage = 2;
        std::cout << "Stage 1 separated. Stage 2 ignition!\n";
    }
}

void Rocket::abortMission() {
    status = "Aborted";
    velocity = 0;
    std::cout << "Mission aborted.\n";
}

double Rocket::getFuelLevel() const { return fuelLevel; }
double Rocket::getAltitude() const { return altitude; }
double Rocket::getVelocity() const { return velocity; }
std::string Rocket::getStatus() const { return status; }

void Rocket::setOrientation(const Orientation &ori) {
    orientation = ori;
}

Orientation Rocket::getOrientation() const {
    return orientation;
}
