#include "PlanetList.hpp"
#include "Planet.hpp"
#include "PlanetWrapper.hpp"
#include "imgui.h"
#include <cstddef>
#include <memory>
#include <utility>

void PlanetList::render(Simulation &simulation) {
  // Implementation of the render function
  // This function will handle the rendering of the planet list in the UI

  this->planets =
      simulation.getPlanets(); // Assuming getBodies() returns a vector of
                               // shared_ptr<CelestialBody>

  ImGui::Begin("Objects");
  if (ImGui::Button("Add Planet")) {
    // Handle adding a new planet
    // This could open a dialog or add a default planet to the simulation
    auto body = simulation.getPlanets();
    int id = body.size() + 1;
    std::string label = "Planet_" + std::to_string(id);
    auto newPlanet = std::make_shared<Planet>(id, label);
    simulation.addPlanet(newPlanet);

    auto wrapper = std::make_shared<PlanetWrapper>();

    renderWrapperList.emplace_back(wrapper, newPlanet);
  }
  ImGui::Separator();
  for (auto &body : simulation.getPlanets()) {
    std::string label = body->getName();

    if (label.empty())
      label = "Unnamed Body";
    ImGui::Checkbox(label.c_str(), body->getShowBody());
  }

  ImGui::End();
  for (auto pair : this->renderWrapperList) {
    if (*pair.second->getShowBody()) {
      pair.first->render(pair.second);
    }
  }
}