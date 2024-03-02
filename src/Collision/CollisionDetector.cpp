#include "CollisionDetector.h"

using namespace DayNNight;

CollisionDetector& CollisionDetector::instance()
{
	static CollisionDetector instance;
	return instance;
}

void CollisionDetector::add(Node* n)
{
	nodes.add(n);
}

void CollisionDetector::remove(Node* n)
{
	nodes.remove(n);
}

void CollisionDetector::update()
{
}

Quadtree<Node*, decltype(&getExtRect<Node*>)>& DayNNight::CollisionDetector::getTree()
{
	return nodes;
}
