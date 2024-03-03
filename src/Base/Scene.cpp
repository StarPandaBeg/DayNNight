#include "Scene.h"

using namespace DayNNight;

void Scene::add(std::shared_ptr<Node> node) {
    _nodes.push_back(node);
}

void Scene::update() {
    for (auto& node : _nodes) {
        node->update();
    }
}

void Scene::render(sf::RenderTarget& target) {
    for (auto& node : _nodes) {
        node->render(target);
    }
}
