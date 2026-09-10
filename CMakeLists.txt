cmake_minimum_required(VERSION 3.24)

project(SpaceSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 REQUIRED)

add_executable(SpaceSimulation 
    src/main.cpp
    src/simulation/Planet.cpp
    src/simulation/Star.cpp
    src/simulation/CelestialBody.cpp
    src/simulation/Simulation.cpp
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    src/ui/PlanetList.cpp
    src/ui/PlanetWrapper.cpp
    src/ui/StarList.cpp
    src/ui/StarWrapper.cpp
    src/ui/WorldView.cpp

)

target_include_directories(SpaceSimulation
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui
)
target_link_libraries(SpaceSimulation PRIVATE 
    glfw
    "-framework OpenGL"
    )
# Optional: helpful for IDEs and clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
