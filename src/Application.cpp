#include "Application.h"

#include <iostream>

#include "Collision/CollisionDetector.h"
#include "Nodes/BallNode.h"
#include "Nodes/RectGridNode.h"

using namespace DayNNight;

Application::Application() {
    auto settings = sf::ContextSettings();
    settings.antialiasingLevel = 8;

    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(640, 640), "Day n' Night", sf::Style::Titlebar | sf::Style::Close, settings);
    _window->setVerticalSyncEnabled(true);
    setupScene();
}

void Application::run() {
    while (_window->isOpen()) {
        pollEvents();

        _scene->update();
        CollisionDetector::instance().update();

        _window->clear();
        _scene->render(*_window.get());
        _window->display();
    }
}

void Application::pollEvents() {
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->close();
    }
}

void Application::setupScene() {
    _scene = std::make_unique<Scene>();

    auto grid = std::make_shared<RectGridNode>(sf::Vector2f(640, 640), sf::Vector2i(16, 16));
    _scene->add(grid);

    auto ballA = std::make_shared<BallNode>(12, 0);
    ballA->applyMovement(sf::Vector2f(0.5, -0.5), 12);
    ballA->setPosition(sf::Vector2f(160, 320));
    _scene->add(ballA);

    auto ballB = std::make_shared<BallNode>(12, 1);
    ballB->applyMovement(sf::Vector2f(-0.5, 0.5), 12);
    ballB->setPosition(sf::Vector2f(480, 320));
    _scene->add(ballB);
}
