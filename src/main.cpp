#include <iostream>

#include "CelestialBody.hpp"
#include "Planet.hpp"
#include "PlanetList.hpp"
#include "Star.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <memory>

#include "PlanetList.hpp"
#include "Simulation.hpp"
#include <memory>
#include <vector>

void renderPlanetList();

int main() {

//   CelestialBody::Position sunPosition{0.0f, 0.0f};

//   auto sun = std::make_shared<Star>(1, "Sun", 3.828e26, std::vector<CelestialBody::Position>{sunPosition}, 1.989e30, 6.9634e8);

//   CelestialBody::Position earthPosition{
//     1.496e11,
//     0.0
// };

// auto earth = std::make_shared<Planet>(
//     2,
//     "Earth",
//     true,
//     std::vector<CelestialBody::Position>{earthPosition},
//     5.972e24,
//     6.371e6
// );


  // -------------------------
  // GLFW initialisieren
  // -------------------------
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return 1;
  }

  // OpenGL 3.3 Core
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Wichtig für macOS
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window =
      glfwCreateWindow(1280, 720, "Solar System", nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // VSync

  // -------------------------
  // Dear ImGui initialisieren
  // -------------------------

  IMGUI_CHECKVERSION();

  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  // Standard Dear ImGui Style
  ImGui::StyleColorsDark();

  // GLFW Backend
  ImGui_ImplGlfw_InitForOpenGL(window, true);

  // OpenGL3 Backend
  ImGui_ImplOpenGL3_Init("#version 330");

  // -------------------------
  // Main Loop
  // -------------------------
  Simulation simulation;
  PlanetList planetList;

  // simulation.addStar(sun);
  // simulation.addPlanet(earth);

  while (!glfwWindowShouldClose(window)) {

    glfwPollEvents();

    // Neue ImGui-Frame starten
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // -------------------------
    // Unser erstes Fenster
    // -------------------------

    planetList.render(simulation);

    // -------------------------
    // Rendering
    // -------------------------

    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);

    glViewport(0, 0, display_w, display_h);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // -------------------------
  // Aufräumen
  // -------------------------

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();

  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
