#ifndef CELESTIALBODY_HPP
#define CELESTIALBODY_HPP

#include <string>

struct Vec3 {
    double x;
    double y;
    double z;
};

class CelestialBody {
public:
    CelestialBody(const std::string& name, double mass, double radius,
                  const Vec3& position = {0,0,0}, const Vec3& velocity = {0,0,0});

    const std::string& getName() const;
    double getMass() const;
    double getRadius() const;
    double getGravitationalParameter() const;
    Vec3 getPosition() const;
    Vec3 getVelocity() const;

    void setPosition(const Vec3& pos);
    void setVelocity(const Vec3& vel);
    void applyAcceleration(const Vec3& accel, double dt);

private:
    std::string name_;
    double mass_;
    double radius_;
    Vec3 position_;
    Vec3 velocity_;
    double mu_; // gravitational parameter
};

#endif // CELESTIALBODY_HPP
