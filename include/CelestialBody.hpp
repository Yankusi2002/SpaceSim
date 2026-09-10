#pragma once

#include "imgui.h"
#include <vector>

class CelestialBody {
public:
  struct Position {
    float x;
    float y;
  };

  CelestialBody(int id , const std::string& name, CelestialBody::Position position, float mass, float radius);
  virtual void update(double deltaTime) = 0;

  // Setters
  virtual void setMass(float mass) = 0;
  virtual void setRadius(float radius) = 0;

  // Getters
  virtual float getMass() const = 0;
  virtual float getRadius() const = 0;
  virtual float getGravity() const = 0;
  ImVec2 getPos() const;
  void updatePos(ImVec2 pos); 

  const std::string getName();
  int getId();
  bool* getShowBody();
protected:
  bool showBody = false; 
  std::string m_name;
  int m_id;
  float m_mass;
  float m_radius;
  float m_gravity;
  Position m_position;
};


