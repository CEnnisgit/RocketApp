#include "Telemetry.hpp"
#include "Rocket.hpp"
#include <cmath>
#include <cstdlib> // for rand()
#include <ctime>

Telemetry::Telemetry() {
    altitude = 0.0;
    velocity = 0.0;
    acceleration = 0.0;
    temperature = 25.0; // Earth ambient
    orientation = {0.0, 0.0, 0.0};

    std::srand(std::time(nullptr)); // seed random for small variations
}

void Telemetry::update(double deltaTime, Rocket* rocket) {
    // Simulate basic vertical launch acceleration
    acceleration = 30.0 - (altitude / 1000); // throttle back at altitude
    if (acceleration < 5.0) acceleration = 5.0;

    velocity += acceleration * deltaTime;
    altitude += velocity * deltaTime;

    // Simulate heating from air resistance
    temperature += (acceleration * 0.05) + ((rand() % 100 - 50) * 0.01);

    // Simulate rocket rotation drift
    orientation.pitch += ((rand() % 100 - 50) * 0.01);
    orientation.yaw   += ((rand() % 100 - 50) * 0.01);
    orientation.roll  += ((rand() % 100 - 50) * 0.02);

    // Provide orientation feedback to the rocket if requested
    if (rocket) {
        rocket->setOrientation(orientation);
    }
}

double Telemetry::getAltitude() const { return altitude; }
double Telemetry::getVelocity() const { return velocity; }
double Telemetry::getAcceleration() const { return acceleration; }
double Telemetry::getTemperature() const { return temperature; }
Orientation Telemetry::getOrientation() const { return orientation; }
