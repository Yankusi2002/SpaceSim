#include "PlanetWrapper.hpp"
#include "imgui.h"

#include <memory>

void PlanetWrapper::render(std::shared_ptr<Planet> planet) {

  std::string title =
      planet->getName() + "###PlanetWrapper_" + std::to_string(planet->getId());

  ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;

  ImGui::Begin(title.c_str());
  ImGui::Text("Name: %s", planet->getName().c_str());
  ImGui::Separator();

  if (ImGui::TreeNodeEx("Mass", flag)) {
    float mass = planet->getMass();

    ImGui::DragFloat("Mass", &mass);

    planet->setMass(mass);
    ImGui::TreePop();
  }

  if (ImGui::TreeNodeEx("Radius", flag)) {
    float radius = planet->getRadius();

    ImGui::DragFloat("Radius", &radius);

    planet->setRadius(radius);
    ImGui::TreePop();
  }

  if (ImGui::TreeNodeEx("Position", flag)) {
    ImVec2 pos = planet->getPos();

    ImGui::DragFloat("X", &pos.x);
    ImGui::DragFloat("Y", &pos.y);

    planet->updatePos(pos);

    ImGui::TreePop();
  }
  if (ImGui::TreeNodeEx("Velocity", flag)) {
    ImVec2 velocity = planet->getVelocity();
    ImGui::DragFloat("Vx", &velocity.x);
    ImGui::DragFloat("Vy", &velocity.y);

    ImGui::TreePop();
  }

  ImGui::End();
}