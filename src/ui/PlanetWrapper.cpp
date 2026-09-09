#include "PlanetWrapper.hpp"
#include "imgui.h"


#include <memory>

void PlanetWrapper::render(std::shared_ptr<Planet> planet) {

  std::string title =
      planet->getName() + "###PlanetWrapper_" + std::to_string(planet->getId());

  ImGui::Begin(title.c_str());
  ImGui::Text("Name: %s", planet->getName().c_str());
  ImGui::Text("Mass: %.3e", planet->getMass());
  ImGui::Text("Radius: %.3e", planet->getRadius());

  ImGui::End();
}