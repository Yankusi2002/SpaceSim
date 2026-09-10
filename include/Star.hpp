#pragma once

#include "CelestialBody.hpp"
#include <vector>

class Star : public CelestialBody {
public:
  Star(int id, const std::string &name, float luminosity,
       CelestialBody::Position position, float mass,
       float radius);

  Star(int id, const std::string &name);
  float getLuminosity() const;
  void setLuminosity(float luminosity);

  float getGravitationalPull() const;
  void setGravitationalPull(float gravitationalPull);

  void setMass(float mass) override;
  void setRadius(float radius) override;

  float getMass() const override;
  float getRadius() const override;
  float getGravity() const override;

  void update(double deltaTime) override;

private:
  float m_luminosity;
  std::vector<CelestialBody::Position> m_position;
  float m_gravitationalPull;

  void calculateGravitationalPull();
};