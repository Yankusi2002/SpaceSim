// stb_image.h muss im Include-Pfad liegen (github.com/nothings/stb).
// Die Implementierung wird nur in DIESER Datei erzeugt.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Sprites.hpp"

#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <unordered_map>

namespace {

std::unordered_map<std::string, SpriteTexture> g_cache;

bool loadFromFile(const std::string &path, SpriteTexture &out) {
  int w = 0, h = 0, channels = 0;
  // 4 Kanäle erzwingen (RGBA), damit die Transparenz erhalten bleibt
  unsigned char *data = stbi_load(path.c_str(), &w, &h, &channels, 4);
  if (!data) {
    std::cerr << "Textur konnte nicht geladen werden: " << path << " ("
              << stbi_failure_reason() << ")\n";
    return false;
  }

  GLuint id = 0;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               data);
  stbi_image_free(data);

  out.id = id;
  out.width = w;
  out.height = h;
  return true;
}

} // namespace

namespace Sprites {

const SpriteTexture *get(const std::string &path) {
  auto it = g_cache.find(path);
  if (it == g_cache.end()) {
    SpriteTexture tex;
    if (!loadFromFile(path, tex)) {
      tex = SpriteTexture(); // Fehlschlag merken, nicht jeden Frame neu versuchen
    }
    it = g_cache.emplace(path, tex).first;
  }
  return it->second.id != 0 ? &it->second : nullptr;
}

void clear() {
  for (auto &entry : g_cache) {
    if (entry.second.id != 0) {
      glDeleteTextures(1, &entry.second.id);
    }
  }
  g_cache.clear();
}

void drawSprite(ImDrawList *drawList, const SpriteTexture &tex, ImVec2 center,
                float radius, float angleRad, ImU32 tint) {
  const float halfW = radius;
  const float halfH = radius * static_cast<float>(tex.height) /
                      static_cast<float>(tex.width);
  const float c = std::cos(angleRad);
  const float s = std::sin(angleRad);

  // Ecke relativ zur Mitte um den Winkel drehen
  auto rot = [&](float x, float y) {
    return ImVec2(center.x + x * c - y * s, center.y + x * s + y * c);
  };

  const ImVec2 p1 = rot(-halfW, -halfH); // oben links
  const ImVec2 p2 = rot(halfW, -halfH);  // oben rechts
  const ImVec2 p3 = rot(halfW, halfH);   // unten rechts
  const ImVec2 p4 = rot(-halfW, halfH);  // unten links

  const ImTextureID texId = (ImTextureID)(intptr_t)tex.id;
  drawList->AddImageQuad(texId, p1, p2, p3, p4, ImVec2(0, 0), ImVec2(1, 0),
                         ImVec2(1, 1), ImVec2(0, 1), tint);
}

void drawStarGlow(ImDrawList *drawList, ImVec2 center, float radius,
                  double time, ImU32 color) {
  const ImVec4 col = ImGui::ColorConvertU32ToFloat4(color);
  const float pulse = 1.0f + 0.04f * static_cast<float>(std::sin(time * 1.5));

  // Von außen nach innen: viele schwache Kreise ergeben einen weichen Verlauf
  const int layers = 6;
  for (int i = 0; i < layers; ++i) {
    const float r = radius * (2.4f - 0.3f * static_cast<float>(i)) * pulse;
    drawList->AddCircleFilled(center, r, ImColor(col.x, col.y, col.z, 0.07f),
                              48);
  }
}

} // namespace Sprites
