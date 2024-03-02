#include "BallNode.h"

#include <cmath>
#include <iostream>
#include "RectNode.h"
#include "../ColorTable.h"
#include "../Collision/CollisionDetector.h"

using namespace DayNNight;

template<class T>
inline T constrain(T value, T min, T max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

float lerp(float a, float b, float f)
{
	return (a * (1.0 - f)) + (b * f);
}

BallNode::BallNode(float radius, int type)
{
	_type = type;
	setCollidable(true);

	_shape = sf::CircleShape(radius);
	_shape.setFillColor(ColorTable[(_type + 1) % 2]);
}

void BallNode::update()
{
	PhysicalNode::update();
	adjustBounds();

	auto collisions = CollisionDetector::instance().getTree().query(getRect());

	RectNode* lastCollision = nullptr;
	for (auto& c : collisions) {
		auto rect = dynamic_cast<RectNode*>(c);
		if (rect == nullptr) continue;
		if (rect->getType() == _type) continue;

		rect->setType(_type);
		lastCollision = rect;
	}

	if (lastCollision!= nullptr) {
		sf::Vector2f lastNormal;

		auto ballBounds = getRect();
		auto platformBounds = lastCollision->getRect();
		auto ballCenter = ballBounds.getCenter();
		auto platformCenter = platformBounds.getCenter();

		auto delta = ballCenter - platformCenter;

		if (delta.x > delta.y) {
			_movementDirection.x *= -1;
		}
		else {
			_movementDirection.y *= -1;
		}
		/*delta.x = delta.x / (platformBounds.width / 2.0) / 2 + 0.5f;
		delta.y = delta.y / (platformBounds.height / 2.0) / 2 + 0.5f;

		delta.x = constrain(delta.x, 0.0f, 1.0f);
		delta.y = constrain(delta.y, 0.0f, 1.0f);

		auto angle = lerp((float)-3.14 / 3, (float)3.14 / 3, delta.x);

		lastNormal.x = std::sinf(angle + 3.14 / 2);
		lastNormal.y = -std::cosf(angle + 3.14 / 2);

		std::cout << lastNormal.x << " " << lastNormal.y << "\n";

		_movementDirection = lastNormal;*/
	}
	adjustBounds();
}

void BallNode::render(sf::RenderTarget& target)
{
	target.draw(_shape, _shape.getTransform() * getTransform());
}

ExtRect<float> BallNode::getRect() const
{
	auto transform = _shape.getTransform() * getTransform();
	auto rect = transform.transformRect(_shape.getLocalBounds());

	return ExtRect<float>(rect.left, rect.top, rect.width, rect.height);
}

void BallNode::adjustBounds()
{
	auto newDirection = _movementDirection;
	auto position = getRect().getTopLeft();

	if (position.x < 10) {
		position.x = 10;
		newDirection.x = abs(newDirection.x);
	}
	if (position.x >= 630) {
		position.x = 630;
		newDirection.x = -abs(newDirection.x);
	}
	if (position.y < 10) {
		position.y = 10;
		newDirection.y = abs(newDirection.y);
	}
	if (position.y >= 630) {
		position.y = 630;
		newDirection.y = -abs(newDirection.y);
	}

	setPosition(position);
	_movementDirection = newDirection;
}
