#pragma once

#include "Node.h"

namespace DayNNight {
	class PhysicalNode : public Node
	{
	public:
		void applyMovement(sf::Vector2f direction, float speed);
		virtual void update() override;
	protected:
		sf::Vector2f _movementDirection;
		float _speed;
	};
}

