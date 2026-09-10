#pragma once 


#include "CelestialBody.hpp"
#include "Simulation.hpp"
#include "imgui.h"
#include <memory>
class WorldView {
    public:
        void render(Simulation& simulation);
        
        bool getShow();
        void setShow(const bool show);
    private: 
        ImVec2 WorldToScreen( ImVec2 position, ImVec2 canvasPos ,ImVec2 canvasSize);
        bool drawBodyToWorldView(std::shared_ptr<CelestialBody> body);
        

        bool m_show = true;

};