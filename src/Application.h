#pragma once

#include <memory>

#include "Base/Scene.h"
#include "SFML/Graphics.hpp"

namespace DayNNight {
    class Application {
       public:
        Application();
        void run();

       private:
        void pollEvents();
        void setupScene();

        std::unique_ptr<sf::RenderWindow> _window;
        std::unique_ptr<Scene> _scene;
    };
}  // namespace DayNNight