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

  ImGui::Begin("PlanetList");
  if (ImGui::Button("Add Planet")) {
    // Handle adding a new planet
    // This could open a dialog or add a default planet to the simulation
    auto body = simulation.getPlanets();
    int id = body.size() + 1;
    std::string label = "Planet_" + std::to_string(id);
    CelestialBody::Position startPos{200.0f, 0.0f};
    auto newPlanet =
        std::make_shared<Planet>(id, label, /*habitable=*/false, startPos,
                                 /*mass=*/1.0f, /*radius=*/5.0f);
    auto star = simulation.getStars();
    float dx = startPos.x - star[0]->getPos().x;
    float dy = startPos.y - star[0]->getPos().y;
    float r  = std::sqrt(dx*dx + dy*dy);
    float vCirc = std::sqrt(GRAVITATION_CONSTANT * star[0]->getMass() / r);

    // Tangentialrichtung = Radiusvektor um 90° gedreht
    ImVec2 tangent(-dy / r, dx / r);

    newPlanet->setVelocity(ImVec2(tangent.x * vCirc, tangent.y * vCirc));
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