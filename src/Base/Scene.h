#pragma once

#include <memory>
#include <vector>

#include "Node.h"
#include "SFML/Graphics/RenderTarget.hpp"

namespace DayNNight {
    class Scene {
       public:
        void add(std::shared_ptr<Node> node);
        void update();
        void render(sf::RenderTarget& target);

       private:
        std::vector<std::shared_ptr<Node>> _nodes;
    };
}  // namespace DayNNight