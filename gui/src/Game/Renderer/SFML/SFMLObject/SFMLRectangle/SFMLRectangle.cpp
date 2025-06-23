/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLRectangle.cpp
*/

#include "SFMLRectangle.hpp"

namespace sfml
{

SFMLRectangle::SFMLRectangle(std::shared_ptr<sf::RenderWindow> rWindow)
    : _rWindow(std::move(rWindow))
{
    _rect.setFillColor(sf::Color::Blue);
}

/**
 * @brief Gets the current position of the rectangle.
 * 
 * @return Position as a 2D vector.
 */
tools::Vector2<float> SFMLRectangle::getPosition() const
{
    auto pos = _rect.getPosition();
    return tools::Vector2<float>{pos.x, pos.y};
}

/**
 * @brief Gets the current size of the rectangle.
 * 
 * @return Size as a 2D vector.
 */
tools::Vector2<float> SFMLRectangle::getSize() const
{
    auto size = _rect.getSize();
    return tools::Vector2<float>{size.x, size.y};
}


/**
 * @brief Sets the size of the rectangle.
 * 
 * @param size New size.
 */
void SFMLRectangle::setSize(const tools::Vector2<float> &size)
{
    _rect.setSize(sf::Vector2f(size.x, size.y));
}


/**
 * @brief Sets the position of the rectangle.
 * 
 * @param pos New position.
 */
void SFMLRectangle::setPosition(const tools::Vector2<float> &pos)
{
    _rect.setPosition(sf::Vector2f(pos.x, pos.y));
}

/**
 * @brief Draws the rectangle to the window.
 */
void SFMLRectangle::drawObject() const
{
    if (_rWindow && _rWindow->isOpen())
        _rWindow->draw(_rect);
}

/**
 * @brief Checks if a given point is inside the rectangle.
 * 
 * @param position Point to check.
 * @return true if the point is inside.
 */
bool SFMLRectangle::contains(tools::Vector2<float> position)
{
    return _rect.getGlobalBounds().contains(sf::Vector2f(position.x, position.y));
}


/**
 * @brief Sets the fill color of the rectangle.
 * 
 * @param color New color to apply.
 */

void SFMLRectangle::setColor(const tools::Color &color)
{
    _rect.setFillColor({color.r, color.g, color.b, color.a});

}
} // namespace sfml
