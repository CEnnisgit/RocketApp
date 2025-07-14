# RocketApp

RocketApp is a small simulation that models a two-stage rocket launch with very simplified physics. The program demonstrates basic flight dynamics and prints telemetry for each simulated second.

## Project Goals

The long-term vision is to turn RocketApp into a comprehensive spaceflight simulator. Planned features include a full solar system model and an immersive user interface for mission planning and visualization.

## Building

Use `make` to build the project. The default target produces an executable named `rocket_sim`.

```bash
make
```

This compiles all sources using `g++` with C++11 settings.

## Running

After building, run the simulation:

```bash
./rocket_sim
```

Sample output from a run looks like:

```
Launch initiated!
Time: 1s
Rocket Altitude: 5.39 m
Rocket Velocity: 5.39 m/s
Telemetry Altitude: 30 m
Temperature: 26.89 C
Orientation - Pitch: 0.2646, Yaw: 0.2744, Roll: -0.9016
------
Time: 2s
Rocket Altitude: 16.1699 m
Rocket Velocity: 10.7799 m/s
Telemetry Altitude: 89.97 m
Temperature: 28.5985 C
Orientation - Pitch: 0.245, Yaw: 0.1666, Roll: -1.0192
------
Stage 1 separated. Stage 2 ignition!
```

## Real-time Visualization

`rocket_sim` broadcasts telemetry as JSON UDP packets on port 7000.
Clients that only care about altitude, velocity, temperature and orientation
can continue to parse those fields. More advanced visualizers can also use the
additional position and velocity vectors as well as optional celestial body
data. The following Python snippet demonstrates how to receive the
data and print each packet:

```python
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", 7000))

while True:
    data, _ = sock.recvfrom(1024)
    print(data.decode())
```

Point your visualization software at `udp://localhost:7000` to display
altitude, velocity, temperature, and orientation in real time. If your tool
supports it, you can also render the rocket's position and velocity vectors and
any bodies included in the optional `bodies` array.

### 3D Telemetry Viewer

A small Python script `telemetry_viewer.py` renders the rocket and any celestial bodies in 3D. Build and run `rocket_sim` in one terminal and start the viewer in another:

```bash
make
./rocket_sim
```

In a separate shell run:

```bash
python3 telemetry_viewer.py
```

The viewer listens on UDP port 7000 and updates whenever telemetry is received.

## Future Enhancements

The current simulation uses extremely basic equations. Potential improvements include:

- More advanced physics for thrust, drag and mass changes.
- Telemetry interfaces for logging and real-time monitoring.
- Additional stages or control algorithms for guidance.

- A rich, Tesla-style UI with real-time graphical visualization similar to Tesla's driver display.
- A full solar system model where users can simulate travel to any planet, moon, or location.

## Solar System Placeholder Example

The codebase now includes basic `CelestialBody` and `SolarSystem` classes. The
following snippet demonstrates creating a simple Earth–Moon system and running
a few simulation steps:

```cpp
#include "SolarSystem.hpp"

int main() {
    SolarSystem system;
    CelestialBody earth("Earth", 5.972e24, 6371e3);
    CelestialBody moon("Moon", 7.342e22, 1737e3, {384.4e6, 0, 0}, {0, 1022, 0});

    system.addBody(earth);
    system.addBody(moon);

    // Advance the system by one hour per step
    for (int i = 0; i < 10; ++i) {
        system.update(3600);
        auto positions = system.getPositions();
        // positions[0] is Earth, positions[1] is Moon
    }
}
```
