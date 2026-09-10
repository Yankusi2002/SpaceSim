#pragma once

#include "CelestialBody.hpp"
#include "Planet.hpp"
#include "Star.hpp"

#include <memory>
#include <vector>

constexpr float GRAVITATION_CONSTANT = 0.0002959122f;
constexpr float SIMULATION_DAYS_PER_SECOND = 30.0f;

class Simulation {
public:
  void update(double deltaTime);
  void addPlanet(const std::shared_ptr<Planet> &planet);
  bool addStar(const std::shared_ptr<Star> &star);

  void removeBody(int id);

  std::vector<std::shared_ptr<Planet>> getPlanets();
  std::vector<std::shared_ptr<Star>> getStars();

private:
  float getDistance(std::shared_ptr<CelestialBody> body1,
                    std::shared_ptr<CelestialBody> body2);
  float calculateGravitationalPull(std::shared_ptr<CelestialBody> body1,
                                   std::shared_ptr<CelestialBody> body2,
                                   float distance);
  void initializeCircularOrbit(const std::shared_ptr<Planet> &planet);

  std::vector<std::shared_ptr<Planet>> m_planets;
  std::vector<std::shared_ptr<Star>> m_stars;
};