#include "Planet.hpp"
#include "imgui.h"

Planet::Planet(int id, const std::string& name, bool habitable,
               CelestialBody::Position position, float mass, float radius)
    : CelestialBody(id, name, position, mass, radius),
      habitable(habitable) {
  // Constructor implementation
}
Planet::Planet(int id, const std::string& name): CelestialBody(id, name, CelestialBody::Position({{0.0f, 0.0f}}), 1.0, 0.0),
           habitable(false) {
  // Default constructor implementation
}

void Planet::setMass(float mass) { m_mass = mass; }
void Planet::setRadius(const float radius) { m_radius = radius; }

float Planet::getMass() const { return m_mass; }

float Planet::getRadius() const { return m_radius; }

float Planet::getGravity() const { return m_gravity; }

void Planet::update(double deltaTime) {

    // Position verändern: Position = alte Position + (Geschwindigkeit * Zeit)
    m_position.x += m_velocity.x * deltaTime;
    m_position.y += m_velocity.y * deltaTime;

}


void Planet::setVelocity(ImVec2 velocity){
  m_velocity.x = velocity.x;
  m_velocity.y = velocity.y;
}

ImVec2 Planet::getVelocity() const {
  return m_velocity;
}

void Planet::setGravitationForce(float force)
{
  m_gravitationForceSet = true;
  m_gravitationForce = force; 
}

float Planet::getGravitationForce()
{
  if(m_gravitationForceSet)
  {
    return m_gravitationForce;
  }
  return 0.0f;
}

bool Planet::getGraviationForceSet(){
  return m_gravitationForceSet;
}

void Planet::setGravitationAcceleration(ImVec2 acceleration){
  m_gravitationAcceleration = acceleration;
}



