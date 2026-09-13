#include "Simulation.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "imgui.h"
#include <cmath>
#include <future>
#include <memory>
#include <vector>

void Simulation::update(double deltaTime) {
  // Update the simulation state based on the elapsed time
  // This function will handle the physics and interactions of celestial bodies

  // Check & Update Star

  // Update Planet Position based on Gravity
  // For now only include the Gravatiy from a Star

  // Loop through every Planet
  // Get the Gravitation Pull from the Star based on the Distance
  for (auto planet : m_planets) {
    // Calculate distance to star
    if (!m_stars.empty()) {
      auto star = m_stars[0];
      float deltaX = star->getPos().x - planet->getPos().x;
      float deltaY = star->getPos().y - planet->getPos().y;
      float distance = getDistance(star, planet);

      float force = calculateGravitationalPull(star, planet, distance);
      planet->setGravitationForce(force);

      /// a = F / m
      float accelerationTotal = force / planet->getMass();
      float ax = 0;
      float ay = 0;
      if (distance >= 0.1f) {
        /// Acceleration direction
        ax = accelerationTotal * (deltaX / distance);
        ay = accelerationTotal * (deltaY / distance);
      }

      planet->setGravitationAcceleration(ImVec2(ax, ay));

      float newVx = planet->getVelocity().x + (ax * deltaTime);
      float newVy = planet->getVelocity().y + (ay * deltaTime);

      planet->setVelocity(ImVec2(newVx, newVy));
      planet->update(deltaTime);
    }
  }
}

std::vector<std::shared_ptr<Star>> Simulation::getStars() { return m_stars; }

void Simulation::addPlanet(const std::shared_ptr<Planet> &planet) {
  m_planets.push_back(planet);
}

bool Simulation::addStar(const std::shared_ptr<Star> &star) {
  /* Only allow one star in the simulation */
  if (m_stars.empty()) {
    m_stars.push_back(star);
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

  /// Calculate Distance between two points
  /// Simple Pytagoras in 2D Space a^2 + b^2 = c^2

  float deltaX = pos2.x - pos1.x;
  float deltaY = pos2.y - pos1.y;

  float distance = sqrtf(deltaX * deltaX + deltaY * deltaY);

  return distance;
}

float Simulation::calculateGravitationalPull(
    std::shared_ptr<CelestialBody> body1, std::shared_ptr<CelestialBody> body2,
    float distance) {

  if (distance <= 0.1f) {
    return 0.0f;
  }
  float mass1 = body1->getMass();
  float mass2 = body2->getMass();

  float force = GRAVITATION_CONSTANT * (mass1 * mass2 / (distance * distance));

  return force;
}