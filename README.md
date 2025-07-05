# RocketApp

RocketApp is a small simulation that models a two-stage rocket launch with very simplified physics. The program demonstrates basic flight dynamics and prints telemetry for each simulated second.

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

## Future Enhancements

The current simulation uses extremely basic equations. Potential improvements include:

- More advanced physics for thrust, drag and mass changes.
- Telemetry interfaces for logging and real-time monitoring.
- Additional stages or control algorithms for guidance.

- Fully simulated visualizer showing real-time flight dynamics, similar to Tesla driver visualizations.
- Navigation and mission planning to simulate travel to any body in the solar system.
