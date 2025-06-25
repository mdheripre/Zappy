/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLRoundedRectangle.cpp
*/

#include "SFMLRoundedRectangle.hpp"

namespace sfml
{

SFMLRoundedRectangle::SFMLRoundedRectangle(std::shared_ptr<sf::RenderWindow> rWindow, int radius)
    : _radius(radius), _rWindow(std::move(rWindow))
{
    _topLeft.setPointCount(20);
    _topRight.setPointCount(20);
    _bottomLeft.setPointCount(20);
    _bottomRight.setPointCount(20);
    _topLeft.setRadius(_radius);
    _topRight.setRadius(_radius);
    _bottomLeft.setRadius(_radius);
    _bottomRight.setRadius(_radius);
}

tools::Vector2<float> SFMLRoundedRectangle::getPosition() const
{
    return _pos;
}

tools::Vector2<float> SFMLRoundedRectangle::getSize() const
{
    auto centerSize = _center.getSize();
    return tools::Vector2<float>{centerSize.x + 2 * _radius, centerSize.y + 2 * _radius};
}

void SFMLRoundedRectangle::setPosition(const tools::Vector2<float>& pos)
{
    _pos = pos;
    setSize(getSize());
}

void SFMLRoundedRectangle::setSize(const tools::Vector2<float>& size)
{
    float width = size.x;
    float height = size.y;

    _center.setSize(sf::Vector2f(width - 2 * _radius, height - 2 * _radius));
    _center.setPosition(_pos.x + _radius, _pos.y + _radius);

    _hBar.setSize(sf::Vector2f(width - _radius, height + _radius));
    _hBar.setPosition(_pos.x + _radius, _pos.y);

    _vBar.setSize(sf::Vector2f(width + _radius, height - _radius));
    _vBar.setPosition(_pos.x, _pos.y + _radius);

    _topLeft.setRadius(_radius);
    _topLeft.setPointCount(20);
    _topLeft.setPosition(_pos.x, _pos.y);

    _topRight.setRadius(_radius);
    _topRight.setPointCount(20);
    _topRight.setPosition(_pos.x + width - _radius, _pos.y);

    _bottomLeft.setRadius(_radius);
    _bottomLeft.setPointCount(20);
    _bottomLeft.setPosition(_pos.x, _pos.y + height - _radius);

    _bottomRight.setRadius(_radius);
    _bottomRight.setPointCount(20);
    _bottomRight.setPosition(_pos.x + width - _radius, _pos.y + height - _radius);
}


void SFMLRoundedRectangle::setColor(const tools::Color& color)
{
    sf::Color sfColor(color.r, color.g, color.b, color.a);
    _center.setFillColor(sfColor);
    _hBar.setFillColor(sfColor);
    _vBar.setFillColor(sfColor);
    _topLeft.setFillColor(sfColor);
    _topRight.setFillColor(sfColor);
    _bottomLeft.setFillColor(sfColor);
    _bottomRight.setFillColor(sfColor);
}

bool SFMLRoundedRectangle::contains(tools::Vector2<float> position)
{
    auto size = getSize();
    sf::FloatRect bounds(_pos.x, _pos.y, size.x, size.y);

    return bounds.contains(position.x, position.y);
}

void SFMLRoundedRectangle::drawObject() const
{
    if (_rWindow && _rWindow->isOpen()) {
        _rWindow->draw(_center);
        _rWindow->draw(_hBar);
        _rWindow->draw(_vBar);
        _rWindow->draw(_topLeft);
        _rWindow->draw(_topRight);
        _rWindow->draw(_bottomLeft);
        _rWindow->draw(_bottomRight);
    }
}
} // namespace sfml