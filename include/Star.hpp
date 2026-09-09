#pragma once

#include "CelestialBody.hpp"
#include <vector>

class Star : public CelestialBody {
public:
  Star(int m_id, const std::string& m_name, double luminosity,
       std::vector<CelestialBody::Position> position, double mass, double radius);

  double getLuminosity() const;
  void setLuminosity(double luminosity);

  double getGravitationalPull() const;
  void setGravitationalPull(double gravitationalPull);

  void setMass(double mass) override;
  void setRadius(double radius) override;

  double getMass() const override;
  double getRadius() const override;
  double getGravity() const override;

  void update(double deltaTime) override;

private:
  double m_luminosity;
  std::vector<CelestialBody::Position> m_position;
  double m_gravitationalPull;

  void calculateGravitationalPull();
};