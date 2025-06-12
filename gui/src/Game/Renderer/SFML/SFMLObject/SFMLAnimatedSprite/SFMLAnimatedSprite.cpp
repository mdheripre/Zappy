/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLObjectFactory.cpp
*/

#include "SFMLAnimatedSprite.hpp"
#include <iostream>

namespace sfml {

    SFMLAnimatedSprite::SFMLAnimatedSprite(const sf::Texture& texture,
        std::shared_ptr<sf::RenderWindow> ctx,
        int columns,
        int rows,
        float pixelSize,
        std::unordered_map<int, int> animationMap)
        : _animationMap(std::move(animationMap)), _ctx(std::move(ctx))
    {
        sprite.setTexture(texture);
    
        auto texSize = texture.getSize();
        int frameWidthPixels = texSize.x / columns;
        int frameHeightPixels = texSize.y / rows;
        float frameMax = static_cast<float>(std::max(frameWidthPixels, frameHeightPixels));
        float scaleFactor = pixelSize / frameMax;
    
        sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidthPixels, frameHeightPixels));
        _rect = sf::FloatRect(0, 0, frameWidthPixels, frameHeightPixels);
    }
    

void SFMLAnimatedSprite::playAnimation(int, bool)
{
   //TODO
}

bool SFMLAnimatedSprite::updateObject(float dt)
{
    return true;
}

const tools::Vector2<float>& SFMLAnimatedSprite::getPosition() const
{
    static tools::Vector2<float> pos;
    sf::Vector2f sfPos = sprite.getPosition();
    pos.x = sfPos.x;
    pos.y = sfPos.y;
    return pos;
}

tools::Vector2<float> SFMLAnimatedSprite::getSize() const
{
    tools::Vector2<float> size;

    auto bounds = sprite.getGlobalBounds();
    size.x = bounds.width;
    size.y = bounds.height;
    return size;
}

void SFMLAnimatedSprite::setPosition(const tools::Vector2<float>& pos)
{
    sprite.setPosition(pos.x, pos.y);
    _rect.left = pos.x;
    _rect.top = pos.y;
}

void SFMLAnimatedSprite::drawObject() const
{
    if (_ctx && _ctx->isOpen())
        _ctx->draw(sprite);
}

} // namespace sfml

