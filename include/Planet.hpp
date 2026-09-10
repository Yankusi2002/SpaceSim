#pragma once

#include <memory.h>
#include <string>
#include <vector>

#include "CelestialBody.hpp"
#include "imgui.h"

class Planet : public CelestialBody {
public:
  Planet(int id, const std::string &name, bool m_habitable,
         CelestialBody::Position position, float mass, float radius);

  Planet(int id, const std::string &name); // Default constructor
  void update(double deltaTime) override;

  // Setters
  void setMass(const float mass) override;
  void setRadius(const float radius) override;

  // Getters
  float getMass() const override;
  float getRadius() const override;
  float getGravity() const override;

  void setGravitationForce(float force);
  float getGravitationForce();

  bool getGraviationForceSet();
  
  void setGravitationAcceleration(ImVec2 acceleration);
  void setVelocity(ImVec2 velocity);
  ImVec2 getVelocity();

private:
  bool habitable;
  float m_gravitationForce;
  bool m_gravitationForceSet = false;
  ImVec2 m_velocity;
  ImVec2 m_gravitationAcceleration;
};