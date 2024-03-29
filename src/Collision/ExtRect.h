#pragma once

#include "SFML/System/Vector2.hpp"

namespace DayNNight {
    template <class T>
    class ExtRect {
       public:
        T left;
        T top;
        T width;
        T height;

        constexpr ExtRect(T Left = 0, T Top = 0, T Width = 0, T Height = 0) noexcept : left(Left), top(Top), width(Width), height(Height) {
        }

        constexpr ExtRect(const sf::Vector2<T>& position, const sf::Vector2<T>& size) noexcept : left(position.x), top(position.y), width(size.x), height(size.y) {
        }

        constexpr T getRight() const noexcept {
            return left + width;
        }

        constexpr T getBottom() const noexcept {
            return top + height;
        }

        constexpr sf::Vector2<T> getTopLeft() const noexcept {
            return sf::Vector2<T>(left, top);
        }

        constexpr sf::Vector2<T> getCenter() const noexcept {
            return sf::Vector2<T>(left + width / 2, top + height / 2);
        }

        constexpr sf::Vector2<T> getSize() const noexcept {
            return sf::Vector2<T>(width, height);
        }

        constexpr bool contains(const ExtRect<T>& box) const noexcept {
            return left <= box.left && box.getRight() <= getRight() &&
                   top <= box.top && box.getBottom() <= getBottom();
        }

        constexpr bool intersects(const ExtRect<T>& box) const noexcept {
            return !(left >= box.getRight() || getRight() <= box.left ||
                     top >= box.getBottom() || getBottom() <= box.top);
        }
    };
}  // namespace DayNNight