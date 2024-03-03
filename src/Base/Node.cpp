#include "Node.h"

#include "../Collision/CollisionDetector.h"

using namespace DayNNight;

Node::~Node() { setCollidable(false); }

void Node::update() {}

void Node::setCollidable(bool state) {
    if (_is_collidable && !state) {
        CollisionDetector::instance().remove(this);
    }
    if (!_is_collidable && state) {
        CollisionDetector::instance().add(this);
    }
    _is_collidable = state;
}

bool Node::isCollidable() { return _is_collidable; }

ExtRect<float> DayNNight::Node::getRect() const { return ExtRect<float>(); }
