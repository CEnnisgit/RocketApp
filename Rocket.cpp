#include "Rocket.hpp"
#include <iostream>

Rocket::Rocket() {
    fuelLevel = 100.0;
    altitude = 0.0;
    velocity = 0.0;
    mass = 50000.0;       // kilograms
    thrust = 760000.0;    // Newtons
    dragCoefficient = 0.2;
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
            double consumption = (currentStage == 1) ? 1.0 : 0.3;
            fuelLevel -= consumption * deltaTime; // stage-based consumption
            if (fuelLevel < 0) fuelLevel = 0;

            double effectiveThrust = (fuelLevel > 0) ? thrust : 0.0;
            double gravityForce = mass * 9.81;
            double dragForce = dragCoefficient * velocity * velocity;
            double acceleration = (effectiveThrust - gravityForce - dragForce) / mass;

            velocity += acceleration * deltaTime;
            altitude += velocity * deltaTime;
            if (altitude < 0) altitude = 0;
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
