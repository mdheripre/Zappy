/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLObjectFactory.cpp
*/

#pragma once
#include "Game/Renderer/Object/IAnimatedSprite.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include "Tools/Vector/Vector.hpp"
#include "Tools/AssetDefinition/AssetDefinition.hpp"
#include "Tools/Error/Error.hpp"

namespace sfml
{
    class SFMLAnimatedSprite : public render::IAnimatedSprite
    {
        public:
            SFMLAnimatedSprite(const sf::Texture &texture,
                std::shared_ptr<sf::RenderWindow> _ctx,
                int frameWidth,
                int frameHeight,
                float scale,
                std::unordered_map<int, tools::AssetDefinition::AnimationInfo> _animationMap,
                float fps = 10);
            ~SFMLAnimatedSprite() = default;
            void playAnimation(int keyAnim, bool loop);
            void playAnimation(tools::AssetDefinition::AnimationInfo AnimInfo, bool loop);
            bool updateObject(float dt);
            tools::Vector2<float> getPosition() const;
            tools::Vector2<float> getSize() const;
            void setSize(const tools::Vector2<float>& size);
            void setPosition(const tools::Vector2<float> &pos);
            void drawObject() const;
            std::unique_ptr<IAnimatedSprite> clone() const;
            bool contains(tools::Vector2<float> position);
            void setColor(const tools::Color &color);
            void updateSpriteDirection();
        private:
            std::unordered_map<int, tools::AssetDefinition::AnimationInfo> _animationMap;
            sf::Sprite sprite;
            int _rows;
            int _columns;
            std::shared_ptr<sf::RenderWindow> _ctx;
            bool _loop = true;
            sf::FloatRect _rect;
            tools::AssetDefinition::AnimationInfo _currentAnimation;
            tools::AssetDefinition::AnimationInfo _defaultAnimation;
            float _currentAnimRow;
            bool _reversed;
            float _frameWidth;
            float _frameHeight;
            float _currentFrame;
            float acc = 0;
            float _fps;
    };
} // namespace sfml
