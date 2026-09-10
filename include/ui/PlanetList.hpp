#pragma once

#include "Planet.hpp"
#include "PlanetWrapper.hpp"
#include "Simulation.hpp"
#include "Star.hpp"
#include <memory>

class PlanetList {
public:
  void render(Simulation &simulation);

private:
  std::vector<std::shared_ptr<Planet>> planets;

  std::vector<
      std::pair<std::shared_ptr<PlanetWrapper>, std::shared_ptr<Planet>>>
      renderWrapperList;
};