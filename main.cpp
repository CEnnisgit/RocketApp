#include "Rocket.hpp"
#include "Telemetry.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    Rocket rocket;
    Telemetry telemetry;

    rocket.startLaunch();

    for (int i = 0; i < 10; ++i) {
        // Telemetry provides orientation feedback before rocket update
        telemetry.update(1.0, &rocket);
        rocket.update(1.0);

        std::cout << "Time: " << (i + 1) << "s\n";
        std::cout << "Rocket Altitude: " << rocket.getAltitude() << " m\n";
        std::cout << "Rocket Velocity: " << rocket.getVelocity() << " m/s\n";
        Orientation ori = rocket.getOrientation();
        std::cout << "Telemetry Altitude: " << telemetry.getAltitude() << " m\n";
        std::cout << "Temperature: " << telemetry.getTemperature() << " C\n";
        std::cout << "Orientation - Pitch: " << ori.pitch
                  << ", Yaw: " << ori.yaw
                  << ", Roll: " << ori.roll << "\n";
        std::cout << "------\n";

        if (i == 4) {
            rocket.stageSeparation();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
