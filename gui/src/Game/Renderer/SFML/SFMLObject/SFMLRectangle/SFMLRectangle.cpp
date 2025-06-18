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

tools::Vector2<float> SFMLRectangle::getPosition() const
{
    auto pos = _rect.getPosition();
    return tools::Vector2<float>{pos.x, pos.y};
}

tools::Vector2<float> SFMLRectangle::getSize() const
{
    auto size = _rect.getSize();
    return tools::Vector2<float>{size.x, size.y};
}

void SFMLRectangle::setSize(const tools::Vector2<float> &size)
{
    _rect.setSize(sf::Vector2f(size.x, size.y));
}

void SFMLRectangle::setPosition(const tools::Vector2<float> &pos)
{
    _rect.setPosition(sf::Vector2f(pos.x, pos.y));
}

void SFMLRectangle::drawObject() const
{
    if (_rWindow && _rWindow->isOpen())
        _rWindow->draw(_rect);
}

bool SFMLRectangle::contains(tools::Vector2<float> position)
{
    return _rect.getGlobalBounds().contains(sf::Vector2f(position.x, position.y));
}

} // namespace sfml
