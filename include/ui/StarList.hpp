#pragma once

#include "Star.hpp"
#include "StarWrapper.hpp"
#include "Simulation.hpp"
#include <memory>
#include <vector>

class StarList {
public:
  void render(Simulation &simulation);

private:
  std::vector<std::pair<std::shared_ptr<StarWrapper>, std::shared_ptr<Star>>> renderWrapperList;
};