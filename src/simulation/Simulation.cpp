#include "Simulation.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "imgui.h"
#include <algorithm>
#include <cmath>

#include <memory>
#include <vector>

double MAX_FRAME_TIME = 0.25f;


void Simulation::update(double deltaTime)
{
    deltaTime = std::min(deltaTime, MAX_FRAME_TIME);

    m_accumulateor += deltaTime * m_timeScale;

    while (m_accumulateor >= FIXED_DT)
    {
        step(FIXED_DT);
        m_accumulateor -= FIXED_DT;
    }
}


ImVec2 Simulation::calculateAcceleration(std::shared_ptr<Planet> planet, std::shared_ptr<Star> star) {
  float deltaX = star->getPos().x - planet->getPos().x;
  float deltaY = star->getPos().y - planet->getPos().y;

  float distance = getDistance(star, planet);

  float force = calculateGravitationalPull(star, planet, distance);

  planet->setGravitationForce(force);

  float acceleration = force / planet->getMass();

  float ax = acceleration * (deltaX / distance);
  float ay = acceleration * (deltaY / distance);

  ImVec2 newAcceleration = ImVec2(ax, ay);

  return newAcceleration;

}

void Simulation::step(double deltaTime) {

  if (m_stars.empty()) {
    return; 
  }

  const auto &star = m_stars[0];
  for (const auto &planet: m_planets)
  {
    ImVec2 acceleration = calculateAcceleration(planet, star);

    planet->setGravitationAcceleration(acceleration);
    
    ImVec2 velocity = planet->getVelocity();
    float dt = static_cast<float>(deltaTime);

    float newX = planet->getPos().x + velocity.x * dt + 0.5f * acceleration.x * dt * dt;
    float newY = planet->getPos().y + velocity.y * dt + 0.5f * acceleration.y * dt * dt;

    planet->updatePos(ImVec2(newX, newY));

    ImVec2 newAcceleration = calculateAcceleration(planet, star);

    float newVx = velocity.x + 0.5f * (newAcceleration.x + newAcceleration.x) * dt;
    float newVy = velocity.y + 0.5f * (newAcceleration.y + newAcceleration.y) * dt;

    planet->setVelocity(ImVec2(newVx, newVy));
    planet->setGravitationAcceleration(newAcceleration);

    planet->setTrace(ImVec2(newX,newY));


    
    
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