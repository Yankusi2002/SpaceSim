#include "Star.hpp"
#include <vector>

Star::Star(int id, const std::string& name, double luminosity,
           std::vector<CelestialBody::Position> position, double mass,
           double radius)
    : CelestialBody(id, name,position, mass, radius),
      m_luminosity(luminosity) {
  // Constructor implementation
}

void Star::setLuminosity(double luminosity) { m_luminosity = luminosity; }
double Star::getLuminosity() const { return m_luminosity; }

void Star::setGravitationalPull(double gravitationalPull) {
  m_gravitationalPull = gravitationalPull;
}

double Star::getGravitationalPull() const { return m_gravitationalPull; }

void Star::setMass(double mass) { m_mass = mass; }

double Star::getMass() const { return m_mass; }

void Star::setRadius(double radius) { m_radius = radius; }

double Star::getRadius() const { return m_radius; }

void Star::update(double deltaTime) { /* Static for now */ }

double Star::getGravity() const { return m_gravity; }