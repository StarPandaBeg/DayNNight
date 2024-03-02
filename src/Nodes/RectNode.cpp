#include "RectNode.h"

using namespace DayNNight;

RectNode::RectNode(sf::Vector2f size)
{
	resize(size);
	setType(0);
}

void RectNode::resize(sf::Vector2f size)
{
	_shape = sf::RectangleShape(size);
}

void RectNode::setType(int type)
{
	_type = type;
	_shape.setFillColor(ColorTable[type % 2]);
}

int RectNode::getType()
{
	return _type;
}

void RectNode::render(sf::RenderTarget& target)
{
	target.draw(_shape, _shape.getTransform() * getTransform());
}

ExtRect<float> RectNode::getRect() const
{
	auto transform = _shape.getTransform() * getTransform();
	auto rect = transform.transformRect(_shape.getLocalBounds());

	return ExtRect<float>(rect.left, rect.top, rect.width, rect.height);
}
