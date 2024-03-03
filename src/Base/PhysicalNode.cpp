#include "PhysicalNode.h"

using namespace DayNNight;

void PhysicalNode::applyMovement(sf::Vector2f direction, float speed) {
    _movementDirection = direction;
    _speed = speed;
}

void PhysicalNode::update() {
    Node::update();

    auto position = getPosition();
    position += _movementDirection * _speed;
    setPosition(position);
}
