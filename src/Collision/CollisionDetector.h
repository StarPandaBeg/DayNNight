#pragma once

#include "../Base/Node.h"
#include "ExtRect.h"
#include "QuadTree.h"

namespace DayNNight {

	template <class T>
	ExtRect<float> getExtRect(const T& node) {
		return node->getRect();
	}

	class CollisionDetector {
	public:
		static CollisionDetector& instance();

		CollisionDetector(CollisionDetector const&) = delete;
		void operator=(CollisionDetector const&) = delete;

		void add(Node* n);
		void remove(Node* n);

		void update();

		Quadtree<Node*, decltype(&getExtRect<Node*>)>& getTree();
	private:
		Quadtree<Node*, decltype(&getExtRect<Node*>)> nodes;

		CollisionDetector() : nodes(ExtRect<float>(0, 0, 640, 640), getExtRect) {
			
		}
	};
}