#include "CelestialBody.hpp"
#include "imgui.h"

CelestialBody::CelestialBody(int id, const std::string& name, CelestialBody::Position position, float mass, float radius)
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

ImVec2 CelestialBody::getPos() const {
    return ImVec2(m_position.x, m_position.y);
}

void CelestialBody::updatePos(ImVec2 pos){
    m_position.x = pos.x;
    m_position.y = pos.y;
}