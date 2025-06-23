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

    SFMLStaticSprite::SFMLStaticSprite(const sf::Texture& texture, float pixelSize, std::shared_ptr<sf::RenderWindow> window)
    : _window(std::move(window))
{
    _sprite.setTexture(texture);
    auto size = texture.getSize();

    float scaleFactor = pixelSize / static_cast<float>(std::max(size.x, size.y));
    _sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
}

SFMLStaticSprite::SFMLStaticSprite(const sf::Texture &texture, std::shared_ptr<sf::RenderWindow> window)
    : _window(std::move(window))
{
    _sprite.setTexture(texture);
}

/**
 * @brief Gets the position of the sprite.
 * 
 * @return Position vector.
 */
tools::Vector2<float> SFMLStaticSprite::getPosition() const
{
    tools::Vector2<float> pos;
    sf::Vector2f sfPos = _sprite.getPosition();
    pos.x = sfPos.x;
    pos.y = sfPos.y;
    return pos;
}

/**
 * @brief Gets the size of the sprite.
 * 
 * @return Size vector.
 */
tools::Vector2<float> SFMLStaticSprite::getSize() const
{
    tools::Vector2<float> size;

    auto bounds = _sprite.getGlobalBounds();
    size.x = bounds.width;
    size.y = bounds.height;
    return size;
}


/**
 * @brief Sets the position of the sprite.
 * 
 * @param pos New position.
 */
void SFMLStaticSprite::setPosition(const tools::Vector2<float>& pos)
{
    _sprite.setPosition(pos.x, pos.y);
}

/**
 * @brief Sets the size of the sprite, adjusting scale accordingly.
 * 
 * @param size Target size.
 */
void SFMLStaticSprite::setSize(const tools::Vector2<float>& size)
{
    sf::FloatRect bounds = _sprite.getLocalBounds();
    if (bounds.width == 0 || bounds.height == 0)
        return;

    float scaleX = size.x / bounds.width;
    float scaleY = size.y / bounds.height;
    _sprite.setScale(scaleX, scaleY);
}


/**
 * @brief Draws the sprite to the window.
 */

void SFMLStaticSprite::drawObject() const
{
    if (_window && _window->isOpen()) {
        _window->draw(_sprite);
    }
}


/**
 * @brief Checks if a point is inside the sprite.
 * 
 * @param position Point to check.
 * @return true if inside.
 */
bool SFMLStaticSprite::contains(tools::Vector2<float> position)
{
    return _sprite.getGlobalBounds().contains(sf::Vector2f(position.x, position.y));
}

/**
 * @brief Sets the sprite's color.
 * 
 * @param color Color to apply.
 */
void SFMLStaticSprite::setColor(const tools::Color &color)
{
    _sprite.setColor({color.r, color.g, color.b, color.a});

}

} // namespace sfml
