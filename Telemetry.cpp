#include "Telemetry.hpp"
#include "Rocket.hpp"
#include "SolarSystem.hpp"
#include <cmath>
#include <cstdlib> // for rand()
#include <ctime>

Telemetry::Telemetry() {
    position = {0.0, 0.0, 6371000.0};
    velocity = {0.0, 0.0, 0.0};
    acceleration = {0.0, 0.0, 0.0};
    temperature = 25.0; // Earth ambient
    orientation = {0.0, 0.0, 0.0};

    std::srand(std::time(nullptr)); // seed random for small variations
}

void Telemetry::update(double deltaTime, Rocket* rocket, const SolarSystem* system) {
    // Gravitational acceleration based on solar system
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

    acceleration = gravity;

    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;
    velocity.z += acceleration.z * deltaTime;

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.z += velocity.z * deltaTime;

    // Simulate heating from air resistance
    double accelMag = std::sqrt(acceleration.x*acceleration.x + acceleration.y*acceleration.y + acceleration.z*acceleration.z);
    temperature += (accelMag * 0.05) + ((rand() % 100 - 50) * 0.01);

    // Simulate rocket rotation drift
    orientation.pitch += ((rand() % 100 - 50) * 0.01);
    orientation.yaw   += ((rand() % 100 - 50) * 0.01);
    orientation.roll  += ((rand() % 100 - 50) * 0.02);

    // Provide orientation feedback to the rocket if requested
    if (rocket) {
        rocket->setOrientation(orientation);
    }
}

double Telemetry::getAltitude() const { return position.z; }
double Telemetry::getVelocity() const { return std::sqrt(velocity.x*velocity.x + velocity.y*velocity.y + velocity.z*velocity.z); }
double Telemetry::getAcceleration() const { return std::sqrt(acceleration.x*acceleration.x + acceleration.y*acceleration.y + acceleration.z*acceleration.z); }
double Telemetry::getTemperature() const { return temperature; }
Orientation Telemetry::getOrientation() const { return orientation; }
