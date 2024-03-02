#pragma once

#include <memory>
#include <vector>
#include "SFML/Graphics/RenderTarget.hpp"
#include "Node.h"

namespace DayNNight {
	class Scene
	{
	public:
		void add(std::shared_ptr<Node> node);
		void update();
		void render(sf::RenderTarget& target);
	private:
		std::vector<std::shared_ptr<Node>> _nodes;
	};
}