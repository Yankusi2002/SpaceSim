#include "CelestialBody.hpp"

CelestialBody::CelestialBody(int id, const std::string& name, std::vector<Position> position, double mass, double radius)
    : m_id(id), m_name(name), m_position(position), m_mass(mass), m_radius(radius) {
  // Constructor implementation
}

const std::string CelestialBody::getName() {
    return this->m_name;
}

int CelestialBody::getId() {
    return this->m_id;
}

bool* CelestialBody::getShowBody() {
    return &this->showBody;
}