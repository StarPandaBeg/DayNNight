#pragma once

#include <vector>

#include "../Base/Node.h"
#include "RectNode.h"
#include "SFML/System/Vector2.hpp"

namespace DayNNight {
    class RectGridNode : public Node {
       public:
        RectGridNode(sf::Vector2f size, sf::Vector2i gridSize);
        virtual void render(sf::RenderTarget& target) override;

       private:
        std::vector<std::vector<RectNode>> _nodes;
    };
}  // namespace DayNNight
