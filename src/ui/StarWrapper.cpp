#include "StarWrapper.hpp"
#include "imgui.h"

#include <memory>

void StarWrapper::render(std::shared_ptr<Star> star) {


  std::string title =
      star->getName() + "###StarWrapper_" + std::to_string(star->getId());

  ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;

  ImGui::Begin(title.c_str());
  ImGui::Text("Name: %s", star->getName().c_str());
  ImGui::Separator();

  if (ImGui::TreeNodeEx("Mass", flag)) {
    float mass = star->getMass();

    ImGui::DragFloat("Mass", &mass);

    star->setMass(mass);
    ImGui::TreePop();
  }

  ImGui::Text("Radius: %.3e", star->getRadius());
  if (ImGui::TreeNodeEx("Radius", flag)) {
    float radius = star->getRadius();

    ImGui::DragFloat("Radius", &radius);

    star->setRadius(radius);
    ImGui::TreePop();
  }

  if (ImGui::TreeNodeEx("Position", flag)) {
    ImVec2 pos = star->getPos();

    ImGui::DragFloat("X", &pos.x);
    ImGui::DragFloat("Y", &pos.y);

    star->updatePos(pos);

    ImGui::TreePop();
  }

  ImGui::End();
}