#pragma once

#include "Planet.hpp"
#include "PlanetWrapper.hpp"
#include "Simulation.hpp"
#include <memory>

class PlanetList {
public:
  void render(Simulation &simulation);
  void addWrapper(std::shared_ptr<PlanetWrapper> wrapper,
                  std::shared_ptr<CelestialBody> body);

private:
  std::vector<std::shared_ptr<Planet>> planets;

  std::vector<
      std::pair<std::shared_ptr<PlanetWrapper>, std::shared_ptr<Planet>>>
      renderWrapperList;
};