/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLStaticSprite.cpp
*/

#include "SFMLStaticSprite.hpp"
#include <iostream>

namespace sfml
{

SFMLStaticSprite::SFMLStaticSprite(const sf::Texture& texture, float scale, std::shared_ptr<sf::RenderWindow> window)
    : _window(std::move(window))
{
    _sprite.setTexture(texture);
    auto size = texture.getSize();
    _sprite.setScale(sf::Vector2f(scale, scale));
}

const tools::Vector2<float>& SFMLStaticSprite::getPosition() const
{
    static tools::Vector2<float> pos;
    sf::Vector2f sfPos = _sprite.getPosition();
    pos.x = sfPos.x;
    pos.y = sfPos.y;
    return pos;
}

const tools::Vector2<float>& SFMLStaticSprite::getSize() const
{
    static tools::Vector2<float> size;
    auto bounds = _sprite.getGlobalBounds();
    size.x = bounds.width;
    size.y = bounds.height;
    return size;
}


void SFMLStaticSprite::setPosition(const tools::Vector2<float>& pos)
{
    _sprite.setPosition(pos.x, pos.y);
}

void SFMLStaticSprite::drawObject() const
{
    if (_window && _window->isOpen()) {
        _window->draw(_sprite);
    }
}

} // namespace sfml
