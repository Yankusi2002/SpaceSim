#pragma once
#include "Planet.hpp"

#include <memory>

class PlanetWrapper {
public:
  void render(std::shared_ptr<Planet> planet);

private:
  std::shared_ptr<CelestialBody> body;
};