#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
#include "../Base/Node.h"
#include "../ColorTable.h"

namespace DayNNight {
	

	class RectNode : public Node
	{
	public:
		RectNode(sf::Vector2f size);
		void resize(sf::Vector2f size);

		void setType(int type);
		int getType();

		virtual void render(sf::RenderTarget& target) override;
		virtual ExtRect<float> getRect() const;
	private:
		int _type;
		sf::RectangleShape _shape;
	};
}
