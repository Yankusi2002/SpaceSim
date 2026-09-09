#pragma once

#include <vector>

class CelestialBody {
public:
  struct Position {
    float x;
    float y;
  };

  CelestialBody(int id , const std::string& name, std::vector<Position> position, double mass, double radius);
  virtual void update(double deltaTime) = 0;

  // Setters
  virtual void setMass(double mass) = 0;
  virtual void setRadius(double radius) = 0;

  // Getters
  virtual double getMass() const = 0;
  virtual double getRadius() const = 0;
  virtual double getGravity() const = 0;

  const std::string getName();
  int getId();
  bool* getShowBody();
protected:
  bool showBody = false; 
  std::string m_name;
  int m_id;
  double m_mass;
  double m_radius;
  double m_gravity;
  std::vector<Position> m_position;
};


