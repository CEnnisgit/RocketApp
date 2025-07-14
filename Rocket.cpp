#include "Rocket.hpp"
#include "SolarSystem.hpp"
#include <iostream>
#include <cmath>

Rocket::Rocket() {
    fuelLevel = 100.0;
    position = {0.0, 0.0, 6371000.0}; // start at Earth's surface (approx)
    velocity = {0.0, 0.0, 0.0};
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

void Rocket::update(double deltaTime, const SolarSystem* system) {
    if (status == "Launching" || status == "In Flight") {
        if (fuelLevel > 0) {
            double consumption = (currentStage == 1) ? 1.0 : 0.3;
            fuelLevel -= consumption * deltaTime; // stage-based consumption
            if (fuelLevel < 0) fuelLevel = 0;

            double effectiveThrust = (fuelLevel > 0) ? thrust : 0.0;

            // Compute gravitational acceleration from the solar system
            Vec3 gravity{0,0,0};
            if (system) {
                for (std::size_t i = 0; i < system->size(); ++i) {
                    const CelestialBody& b = system->getBody(i);
                    Vec3 diff{b.getPosition().x - position.x,
                              b.getPosition().y - position.y,
                              b.getPosition().z - position.z};
                    double distSq = diff.x*diff.x + diff.y*diff.y + diff.z*diff.z + 1e-6;
                    double dist = std::sqrt(distSq);
                    double coef = b.getGravitationalParameter() / (distSq * dist);
                    gravity.x += coef * diff.x;
                    gravity.y += coef * diff.y;
                    gravity.z += coef * diff.z;
                }
            } else {
                gravity.z = -9.81;
            }

            // Thrust is aligned with +Z for simplicity
            Vec3 thrustAcc{0,0,effectiveThrust / mass};

            // Drag proportional to velocity
            double speed = std::sqrt(velocity.x*velocity.x + velocity.y*velocity.y + velocity.z*velocity.z);
            Vec3 dragAcc{0,0,0};
            if (speed > 1e-6) {
                dragAcc.x = -dragCoefficient * speed * velocity.x / mass;
                dragAcc.y = -dragCoefficient * speed * velocity.y / mass;
                dragAcc.z = -dragCoefficient * speed * velocity.z / mass;
            }

            Vec3 acc{thrustAcc.x + gravity.x + dragAcc.x,
                     thrustAcc.y + gravity.y + dragAcc.y,
                     thrustAcc.z + gravity.z + dragAcc.z};

            velocity.x += acc.x * deltaTime;
            velocity.y += acc.y * deltaTime;
            velocity.z += acc.z * deltaTime;

            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
            position.z += velocity.z * deltaTime;

            if (position.z < 0) position.z = 0;
            status = "In Flight";

            // Simple attitude control trying to stabilize orientation
            orientation.pitch *= 0.98;
            orientation.yaw   *= 0.98;
            orientation.roll  *= 0.98;
        } else {
            velocity = {0,0,0};
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
    velocity = {0,0,0};
    std::cout << "Mission aborted.\n";
}

double Rocket::getFuelLevel() const { return fuelLevel; }
Vec3 Rocket::getPosition() const { return position; }
Vec3 Rocket::getVelocityVector() const { return velocity; }
double Rocket::getAltitude() const { return position.z; }
double Rocket::getVelocity() const { return std::sqrt(velocity.x*velocity.x + velocity.y*velocity.y + velocity.z*velocity.z); }
std::string Rocket::getStatus() const { return status; }

void Rocket::setOrientation(const Orientation &ori) {
    orientation = ori;
}

Orientation Rocket::getOrientation() const {
    return orientation;
}
