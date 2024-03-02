#pragma once

#include <vector>
#include "SFML/System/Vector2.hpp"
#include "../Base/Node.h"
#include "RectNode.h"

namespace DayNNight {
	class RectGridNode : public Node
	{
	public:
		RectGridNode(sf::Vector2f size, sf::Vector2i gridSize);
		virtual void render(sf::RenderTarget& target) override;
	private:
		std::vector<std::vector<RectNode>> _nodes;
	};
}
