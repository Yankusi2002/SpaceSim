#pragma once

#include "imgui.h"
#include <string>

struct SpriteTexture {
  unsigned int id = 0; // OpenGL-Textur-ID
  int width = 0;
  int height = 0;
};

namespace Sprites {

// Lädt die Textur beim ersten Aufruf und merkt sie sich (Cache).
// Gibt nullptr zurück, wenn die Datei nicht geladen werden konnte.
// Muss aufgerufen werden, wenn der OpenGL-Kontext existiert (z. B. im render()).
const SpriteTexture *get(const std::string &path);

// Gibt alle geladenen Texturen frei.
// Vor ImGui_ImplOpenGL3_Shutdown() bzw. glfwDestroyWindow() aufrufen.
void clear();

// Zeichnet ein Bild mittig auf `center`. `radius` ist die halbe Breite in Pixeln,
// die Höhe folgt dem Seitenverhältnis des Bildes. `angleRad` dreht das Bild.
void drawSprite(ImDrawList *drawList, const SpriteTexture &tex, ImVec2 center,
                float radius, float angleRad = 0.0f,
                ImU32 tint = IM_COL32_WHITE);

// Weicher, leicht pulsierender Leuchthof (z. B. hinter dem Stern).
// `time` in Sekunden (z. B. ImGui::GetTime()).
void drawStarGlow(ImDrawList *drawList, ImVec2 center, float radius,
                  double time, ImU32 color = IM_COL32(255, 200, 80, 255));

} // namespace Sprites
