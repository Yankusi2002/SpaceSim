#pragma once 

#include "Planet.hpp"
#include "Star.hpp"

#include <memory>
#include <vector>
class Simulation {
public:
   void update(double deltaTime);
   void addPlanet(const std::shared_ptr<Planet> &planet);
   void addStar(const std::shared_ptr<Star> &star);


   void removeBody(int id);


   std::vector<std::shared_ptr<Planet>> getPlanets();

   private:
    std::vector<std::shared_ptr<Planet>> m_planets;
    std::vector<std::shared_ptr<Star>> m_stars;

};