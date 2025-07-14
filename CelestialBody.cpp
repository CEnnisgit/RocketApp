#include "CelestialBody.hpp"
#include <cmath>

static constexpr double G = 6.67430e-11; // gravitational constant

CelestialBody::CelestialBody(const std::string& name, double mass, double radius,
                             const Vec3& position, const Vec3& velocity)
    : name_(name), mass_(mass), radius_(radius),
      position_(position), velocity_(velocity) {
    mu_ = G * mass_;
}

const std::string& CelestialBody::getName() const { return name_; }
double CelestialBody::getMass() const { return mass_; }
double CelestialBody::getRadius() const { return radius_; }
Vec3 CelestialBody::getPosition() const { return position_; }
Vec3 CelestialBody::getVelocity() const { return velocity_; }
double CelestialBody::getGravitationalParameter() const { return mu_; }

void CelestialBody::setPosition(const Vec3& pos) { position_ = pos; }
void CelestialBody::setVelocity(const Vec3& vel) { velocity_ = vel; }

void CelestialBody::applyAcceleration(const Vec3& accel, double dt) {
    velocity_.x += accel.x * dt;
    velocity_.y += accel.y * dt;
    velocity_.z += accel.z * dt;

    position_.x += velocity_.x * dt;
    position_.y += velocity_.y * dt;
    position_.z += velocity_.z * dt;
}
