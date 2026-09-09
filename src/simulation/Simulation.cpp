#include "Simulation.hpp"
#include "Planet.hpp"
#include <future>
#include <vector>



void Simulation::update(double deltaTime) {
    // Update the simulation state based on the elapsed time
    // This function will handle the physics and interactions of celestial bodies
}

void Simulation::addPlanet(const std::shared_ptr<Planet> &planet) {
    m_planets.push_back(planet);
}

void Simulation::addStar(const std::shared_ptr<Star> &star) {
    m_stars.push_back(star);
}

std::vector<std::shared_ptr<Planet>> Simulation::getPlanets()  {
    return m_planets;
}
