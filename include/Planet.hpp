#pragma once

#include <memory.h>
#include <string>
#include <vector>

#include "CelestialBody.hpp"

class Planet : public CelestialBody {
public:
  Planet(int id, const std::string &name, bool m_habitable,
         std::vector<CelestialBody::Position> position, double mass,
         double radius);

  Planet(int id, const std::string &name); // Default constructor
  void update(double deltaTime) override;

  // Setters
  void setMass(const double mass) override;
  void setRadius(const double radius) override;

  // Getters
  double getMass() const override;
  double getRadius() const override;
  double getGravity() const override;

  struct Velocity {
    float vx;
    float vy;
  };

private:
  bool habitable;
  std::vector<Velocity>
      gravitationalPullVec; // Only one gravitational pull for the planet

  std::vector<Velocity> m_velocity;
};