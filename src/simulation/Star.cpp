#include "Star.hpp"
#include <vector>

Star::Star(int id, const std::string &name, float luminosity,
           CelestialBody::Position position, float mass,
           float radius)
    : CelestialBody(id, name, position, mass, radius),
      m_luminosity(luminosity) {
  // Constructor implementation
}
Star::Star(int id, const std::string &name)
    : CelestialBody(id, name,
                    CelestialBody::Position({{0.0f, 0.0f}}), 0.0,
                    0.0),
      m_luminosity(0) {}

void Star::setLuminosity(float luminosity) { m_luminosity = luminosity; }
float Star::getLuminosity() const { return m_luminosity; }

void Star::setGravitationalPull(float gravitationalPull) {
  m_gravitationalPull = gravitationalPull;
}

float Star::getGravitationalPull() const { return m_gravitationalPull; }

void Star::setMass(float mass) { m_mass = mass; }

float Star::getMass() const { return m_mass; }

void Star::setRadius(float radius) { m_radius = radius; }

float Star::getRadius() const { return m_radius; }

void Star::update(double deltaTime) { /* Static for now */ }

float Star::getGravity() const { return m_gravity; }