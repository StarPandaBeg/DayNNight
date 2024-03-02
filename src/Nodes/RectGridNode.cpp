#include "RectGridNode.h"

using namespace DayNNight;

RectGridNode::RectGridNode(sf::Vector2f size, sf::Vector2i gridSize)
{
	auto sizeX = size.x / gridSize.x;
	auto sizeY = size.y / gridSize.y;
	auto cellCount = gridSize.x * gridSize.y;

	for (int i = 0; i < gridSize.y; i++) {
		_nodes.push_back(std::vector<RectNode>());
		for (int j = 0; j < gridSize.x; j++) {
			auto node = RectNode(sf::Vector2f(sizeX, sizeY));
			node.setPosition(sizeX * j, sizeY * i);

			if (j >= (gridSize.x / 2)) node.setType(1);
			_nodes[i].push_back(node);
		}
	}

	for (auto& row : _nodes) {
		for (auto& node : row) {
			node.setCollidable(true);
		}
	}
}

void RectGridNode::render(sf::RenderTarget& target)
{
	for (auto& row : _nodes) {
		for (auto& node : row) {
			node.render(target);
		}
	}
}
