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
        std::unordered_map<int, tools::AssetDefinition::AnimationInfo> animationMap,
        float fps)
        : _animationMap(animationMap), _rows(rows), _columns(columns), _ctx(std::move(ctx)), _fps(fps)
    {
        sprite.setTexture(texture);
        auto texSize = texture.getSize();
        _frameWidth = texSize.x / _columns;
        _frameHeight = texSize.y / _rows;
    
        float frameMax = static_cast<float>(std::max(_frameWidth, _frameHeight));
        float scaleFactor = pixelSize / frameMax;
        sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
        
        _currentAnimation = animationMap.at(0);
        _defaultAnimation = animationMap.at(0);
        playAnimation(_currentAnimation, true);
    }
    

    void SFMLAnimatedSprite::playAnimation(int keyAnim, bool loop)
    {
        auto animIt = _animationMap.find(keyAnim);
        if (animIt == _animationMap.end()) {
            throw RenderError("Error animation " + std::to_string(keyAnim) + " doesn't exist");
        }
        _currentAnimRow = animIt->second.line;
        _currentFrame = 0;
        _loop = loop;
        _currentAnimation = animIt->second;
        _reversed = animIt->second.reverse;

        updateSpriteDirection(); 
        sprite.setTextureRect(sf::IntRect(
            _currentFrame * _frameWidth,
            _currentAnimRow * _frameHeight,
            _frameWidth,
            _frameHeight
        ));
    }

    void SFMLAnimatedSprite::playAnimation(tools::AssetDefinition::AnimationInfo animInfo, bool loop)
    {
        _currentAnimRow = animInfo.line;
        _currentFrame = 0;
        _loop = loop;
        _currentAnimation = animInfo;
        _reversed = animInfo.reverse;

        updateSpriteDirection();    
        sprite.setTextureRect(sf::IntRect(
            _currentFrame * _frameWidth,
            _currentAnimRow * _frameHeight,
            _frameWidth,
            _frameHeight
        ));
    }

    bool SFMLAnimatedSprite::updateObject(float dt)
    {
        acc += dt;
    
        if (acc < (1.0f / _fps)) {
            return false;
        }
        acc = 0.0f;
        _currentFrame++;
        if (_currentFrame >= _currentAnimation.frames) {
            if (_loop) {
                _currentFrame = 0;
            } else {
                playAnimation(_defaultAnimation, true);
                return true;
            }
        }
        sprite.setTextureRect(sf::IntRect(
            _currentFrame * _frameWidth,
            _currentAnimRow * _frameHeight,
            _frameWidth,
            _frameHeight
        ));
        return false;
    }
tools::Vector2<float> SFMLAnimatedSprite::getPosition() const
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

void SFMLAnimatedSprite::setSize(const tools::Vector2<float>& size)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    if (bounds.width == 0 || bounds.height == 0)
        return;

    float scaleX = size.x / bounds.width;
    float scaleY = size.y / bounds.height;
    sprite.setScale(scaleX, scaleY);
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

std::unique_ptr<render::IAnimatedSprite> SFMLAnimatedSprite::clone() const 
{
    auto copy = std::make_unique<SFMLAnimatedSprite>(
        *sprite.getTexture(),
        _ctx,
        _columns,
        _rows,
        sprite.getScale().x,
        _animationMap,
        _fps
    );

    copy->playAnimation(_defaultAnimation, _loop);
    copy->setPosition(getPosition());
    copy->setSize(getSize());
    return copy;
}

bool SFMLAnimatedSprite::contains(tools::Vector2<float> position)
{
    return sprite.getGlobalBounds().contains(sf::Vector2f(position.x, position.y));
}

void SFMLAnimatedSprite::setColor(const tools::Color &color)
{
    sprite.setColor({color.r, color.g, color.b, color.a});
}

void SFMLAnimatedSprite::updateSpriteDirection()
{
    float scaleX = _reversed ? -std::abs(sprite.getScale().x) : std::abs(sprite.getScale().x);

    sprite.setScale(scaleX, sprite.getScale().y);
    sprite.setOrigin(_reversed ? static_cast<float>(_frameWidth) : 0.f, 0.f);
}

} // namespace sfml

