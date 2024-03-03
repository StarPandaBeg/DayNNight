#pragma once

#include "../Collision/ExtRect.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Transformable.hpp"

namespace DayNNight {
    class Node : public sf::Transformable {
       public:
        virtual ~Node();
        virtual void update();
        virtual void render(sf::RenderTarget &target) = 0;
        void setCollidable(bool state);
        bool isCollidable();

        virtual ExtRect<float> getRect() const;

       private:
        bool _is_collidable;
    };
}  // namespace DayNNight
