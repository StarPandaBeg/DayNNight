#pragma once

#include "../Base/PhysicalNode.h"
#include "SFML/Graphics/CircleShape.hpp"

namespace DayNNight {
    class BallNode : public PhysicalNode {
       public:
        BallNode(float radius, int type = 0);
        virtual void update() override;
        virtual void render(sf::RenderTarget& target) override;

        virtual ExtRect<float> getRect() const;

       private:
        sf::CircleShape _shape;
        int _type = 0;

        void adjustBounds();
    };
}  // namespace DayNNight
