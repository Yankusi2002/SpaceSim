#include "StarList.hpp"
#include "Star.hpp"
#include "StarWrapper.hpp"
#include "imgui.h"
#include <memory>


void StarList::render(Simulation &simulation) {
  ImGui::Begin("StarList");
  ImGui::Text("Only one Star can exist at the moment");
  ImGui::Separator();
  if (ImGui::Button("Add Star")) {
    std::shared_ptr<Star> sun = std::make_shared<Star>(1, "Sun");
    if(simulation.addStar(sun))
    {
      auto wrapper = std::make_shared<StarWrapper>();
      this->renderWrapperList.emplace_back(wrapper, sun);

    }

  }

  ImGui::Separator();
  
  /* Only one Start should exits at the same time for now 
  Anyways I include the functionallity to conatin more than one star */

  for(auto pair: renderWrapperList)
  {
    ImGui::Checkbox(pair.second->getName().c_str(), pair.second->getShowBody());
    if(*pair.second->getShowBody())
    {
      pair.first->render(pair.second);
    }
  }

  

  ImGui::End();
}