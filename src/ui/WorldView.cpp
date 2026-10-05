#include "WorldView.hpp"
#include "Sprites.hpp"
#include "imgui.h"

bool WorldView::getShow() { return this->m_show; }

void WorldView::setShow(const bool show) { m_show = show; }

void WorldView::render(Simulation &simulation) {
  ImGui::Begin("World View");

  ImVec2 canvasPos = ImGui::GetCursorScreenPos();

  ImVec2 canvasSize =
      ImGui::GetContentRegionAvail(); // Get Avaidable space in Window

  ImDrawList *drawList = ImGui::GetWindowDrawList();

  // Hintergrund
  drawList->AddRectFilled(
      canvasPos,                         // right top corner
      ImVec2(canvasPos.x + canvasSize.x, // left buttom corner
             canvasPos.y + canvasSize.y),
      IM_COL32(5, 5, 10, 255) // black Color
  );

  // Get Planets
  auto planets = simulation.getPlanets();

  for (auto planet : planets) {
    ImVec2 pos = planet->getPos();
    ImVec2 screenPos = WorldToScreen(pos, canvasPos, canvasSize);
    float t = (float)ImGui::GetTime();
    // Draw Planet
    // Planet (Winkel = Zeit * Drehgeschwindigkeit, pro Planet etwas anders)
    if (const SpriteTexture *tex = Sprites::get("./src/assets/planet" + std::to_string(planet->getId()) + ".png")) {
      Sprites::drawSprite(drawList, *tex, screenPos, planet->getRadius(),
                          t * 0.3f);
    }
    std::vector<ImVec2> traces = planet->getTrace();
    ImVec2 lastPosition = ImVec2(0, 0);
    for (auto trace : traces) {
      if (lastPosition.x != 0 && lastPosition.y != 0) {
        drawList->AddLine(lastPosition,
                          WorldToScreen(trace, canvasPos, canvasSize),
                          IM_COL32(255, 255, 255, 255), 3);
      }
      lastPosition = WorldToScreen(trace, canvasPos, canvasSize);
    }
  }
  auto stars = simulation.getStars();
  for (auto star : stars) {
    ImVec2 pos = star->getPos();
    ImVec2 screenPos = WorldToScreen(pos, canvasPos, canvasSize);
    float t = (float)ImGui::GetTime();
    if (const SpriteTexture *tex = Sprites::get("./src/assets/star1.png")) {
      Sprites::drawSprite(drawList, *tex, screenPos, star->getRadius(),
                          t * 0.05f);
    } else {
      // Fallback, falls das Bild fehlt
      drawList->AddCircleFilled(screenPos, star->getRadius(),
                                IM_COL32(255, 200, 0, 255));
    }
  }

  ImGui::Dummy(canvasSize);

  ImGui::End();
}

ImVec2 WorldView::WorldToScreen(ImVec2 position, ImVec2 canvasPos,
                                ImVec2 canvasSize) {
  double scale = 1;
  double x = position.x * scale;
  double y = position.y * scale;

  float screenPosX = (canvasPos.x + canvasSize.x) * 0.5f + x;
  float sceenPosY = (canvasPos.y + canvasSize.y) * 0.5f - y;

  return ImVec2(screenPosX, sceenPosY);
}