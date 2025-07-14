#include "Rocket.hpp"
#include "Telemetry.hpp"
#include "TelemetryLogger.hpp"
#include "SolarSystem.hpp"
#include "CelestialBody.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    SolarSystem system;
    CelestialBody earth("Earth", 5.972e24, 6371e3);
    system.addBody(earth);

    Rocket rocket;
    Telemetry telemetry;
    TelemetryLogger logger;

    rocket.startLaunch();

    for (int i = 0; i < 10; ++i) {
        // Telemetry provides orientation feedback before rocket update
        telemetry.update(1.0, &rocket, &system);
        rocket.update(1.0, &system);

        std::cout << "Time: " << (i + 1) << "s\n";
        std::cout << "Rocket Altitude: " << rocket.getAltitude() << " m\n";
        std::cout << "Rocket Velocity: " << rocket.getVelocity() << " m/s\n";
        Orientation ori = rocket.getOrientation();
        std::cout << "Telemetry Altitude: " << telemetry.getAltitude() << " m\n";
        std::cout << "Temperature: " << telemetry.getTemperature() << " C\n";
        std::cout << "Orientation - Pitch: " << ori.pitch
                  << ", Yaw: " << ori.yaw
                  << ", Roll: " << ori.roll << "\n";
        logger.logDetailed(rocket.getAltitude(), rocket.getVelocity(),
                          rocket.getPosition(), rocket.getVelocityVector(),
                          telemetry.getTemperature(), ori, &system);
        std::cout << "------\n";

        if (i == 4) {
            rocket.stageSeparation();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
