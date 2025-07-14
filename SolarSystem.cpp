#include "SolarSystem.hpp"
#include <cmath>

void SolarSystem::addBody(const CelestialBody& body) {
    bodies_.push_back(body);
}

std::size_t SolarSystem::size() const { return bodies_.size(); }

const CelestialBody& SolarSystem::getBody(std::size_t index) const {
    return bodies_.at(index);
}

std::vector<Vec3> SolarSystem::getPositions() const {
    std::vector<Vec3> positions;
    positions.reserve(bodies_.size());
    for (const auto& b : bodies_) {
        positions.push_back(b.getPosition());
    }
    return positions;
}

void SolarSystem::update(double dt) {
    std::vector<Vec3> accelerations(bodies_.size(), {0,0,0});

    for (std::size_t i = 0; i < bodies_.size(); ++i) {
        for (std::size_t j = 0; j < bodies_.size(); ++j) {
            if (i == j) continue;
            Vec3 ri = bodies_[i].getPosition();
            Vec3 rj = bodies_[j].getPosition();
            double dx = rj.x - ri.x;
            double dy = rj.y - ri.y;
            double dz = rj.z - ri.z;
            double distSq = dx*dx + dy*dy + dz*dz + 1e-6; // avoid divide by zero
            double dist = std::sqrt(distSq);
            double coef = bodies_[j].getGravitationalParameter() / (distSq * dist);
            accelerations[i].x += coef * dx;
            accelerations[i].y += coef * dy;
            accelerations[i].z += coef * dz;
        }
    }

    for (std::size_t i = 0; i < bodies_.size(); ++i) {
        bodies_[i].applyAcceleration(accelerations[i], dt);
    }
}
