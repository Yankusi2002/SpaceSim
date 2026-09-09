#include "Planet.hpp"

Planet::Planet(int id, const std::string& name, bool habitable,
               std::vector<CelestialBody::Position> position, double mass, double radius)
    : CelestialBody(id, name, position, mass, radius),
      habitable(habitable) {
  // Constructor implementation
}
Planet::Planet(int id, const std::string& name): CelestialBody(id, name, std::vector<CelestialBody::Position>{{0.0f, 0.0f}}, 0.0, 0.0),
           habitable(false) {
  // Default constructor implementation
}

void Planet::setMass(double mass) { m_mass = mass; }
void Planet::setRadius(const double radius) { m_radius = radius; }

double Planet::getMass() const { return m_mass; }

double Planet::getRadius() const { return m_radius; }

double Planet::getGravity() const { return m_gravity; }

void Planet::update(double deltaTime) {
  // Update the planet's state based on deltaTime
  // For example, you could update its position based on its velocity

  this->m_position[0].x +=
      this->m_velocity[0].vx + this->gravitationalPullVec[0].vx * deltaTime;
  this->m_position[1].y +=
      this->m_velocity[0].vy + this->gravitationalPullVec[0].vy * deltaTime;
}

