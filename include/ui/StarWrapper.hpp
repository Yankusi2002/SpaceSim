#pragma once 

#include "Star.hpp"
#include <memory>
class StarWrapper {
    public:
        void render(std::shared_ptr<Star> star);

};