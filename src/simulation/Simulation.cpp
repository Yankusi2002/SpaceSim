#include "Simulation.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "imgui.h"
#include <cmath>
#include <future>
#include <algorithm>
#include <memory>
#include <vector>

void Simulation::update(double deltaTime) {
  if (m_stars.empty()) {
    return;
  }

  float simulationDeltaTime = static_cast<float>(deltaTime) * SIMULATION_DAYS_PER_SECOND;
  const int substeps = std::max(1, static_cast<int>(std::ceil(simulationDeltaTime / 0.25f)));
  const float substepDeltaTime = simulationDeltaTime / static_cast<float>(substeps);

  for (auto planet : m_planets) {
    auto star = m_stars[0];
    for (int step = 0; step < substeps; ++step) {
      ImVec2 starPosition = star->getPos();
      ImVec2 planetPosition = planet->getPos();
      float deltaX = starPosition.x - planetPosition.x;
      float deltaY = starPosition.y - planetPosition.y;
      float distance = std::max(getDistance(star, planet), 0.0001f);

      float force = calculateGravitationalPull(star, planet, distance);
      planet->setGravitationForce(force);

      float acceleration = force / planet->getMass();
      ImVec2 accelerationVector(acceleration * deltaX / distance,
                               acceleration * deltaY / distance);
      planet->setGravitationAcceleration(accelerationVector);

      ImVec2 velocity = planet->getVelocity();
      planet->setVelocity(ImVec2(velocity.x + accelerationVector.x * substepDeltaTime,
                                 velocity.y + accelerationVector.y * substepDeltaTime));
      planet->update(substepDeltaTime);
    }
  }
}

std::vector<std::shared_ptr<Star>> Simulation::getStars() { return m_stars; }

void Simulation::addPlanet(const std::shared_ptr<Planet> &planet) {
  m_planets.push_back(planet);
  initializeCircularOrbit(planet);
}

bool Simulation::addStar(const std::shared_ptr<Star> &star) {
  /* Only allow one star in the simulation */
  if (m_stars.empty()) {
    m_stars.push_back(star);
    for (const auto &planet : m_planets) {
      initializeCircularOrbit(planet);
    }
    return true;
  }
  return false;
}

std::vector<std::shared_ptr<Planet>> Simulation::getPlanets() {
  return m_planets;
}

float Simulation::getDistance(std::shared_ptr<CelestialBody> body1,
                              std::shared_ptr<CelestialBody> body2) {
  ImVec2 pos1 = body1->getPos();
  ImVec2 pos2 = body2->getPos();

  float deltaX = pos2.x - pos1.x;
  float deltaY = pos2.y - pos1.y;

  return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

float Simulation::calculateGravitationalPull(
    std::shared_ptr<CelestialBody> body1, std::shared_ptr<CelestialBody> body2,
    float distance) {
  float mass1 = body1->getMass();
  float mass2 = body2->getMass();

  return GRAVITATION_CONSTANT * (mass1 * mass2 / (distance * distance));
}

void Simulation::initializeCircularOrbit(const std::shared_ptr<Planet> &planet) {
  if (m_stars.empty() || planet->getMass() <= 0.0f) {
    return;
  }

  auto star = m_stars[0];
  ImVec2 offset(planet->getPos().x - star->getPos().x,
               planet->getPos().y - star->getPos().y);
  float distance = std::max(getDistance(star, planet), 0.0001f);
  float orbitalSpeed = std::sqrt(GRAVITATION_CONSTANT * star->getMass() / distance);

  planet->setVelocity(ImVec2(-offset.y / distance * orbitalSpeed,
                             offset.x / distance * orbitalSpeed));
}