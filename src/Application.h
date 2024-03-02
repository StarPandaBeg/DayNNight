#pragma once

#include <memory>
#include "SFML/Graphics.hpp"
#include "Base/Scene.h"

namespace DayNNight {
	class Application
	{
	public:
		Application();
		void run();

	private:
		void pollEvents();
		void setupScene();

		std::unique_ptr<sf::RenderWindow> _window;
		std::unique_ptr<Scene> _scene;
	};
}