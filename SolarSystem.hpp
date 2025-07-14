#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <vector>
#include "CelestialBody.hpp"

class SolarSystem {
public:
    void addBody(const CelestialBody& body);
    std::size_t size() const;
    const CelestialBody& getBody(std::size_t index) const;
    std::vector<Vec3> getPositions() const;

    void update(double dt);

private:
    std::vector<CelestialBody> bodies_;
};

#endif // SOLARSYSTEM_HPP
