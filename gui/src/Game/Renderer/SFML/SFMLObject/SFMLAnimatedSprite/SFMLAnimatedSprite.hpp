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
                std::unordered_map<int, int> _animationMap,
                float fps = 10,
                int defaultAnimation = 0);
            ~SFMLAnimatedSprite() = default;
            void playAnimation(int clipIndex, bool loop);
            bool updateObject(float dt);
            tools::Vector2<float> getPosition() const;
            tools::Vector2<float> getSize() const;
            void setSize(const tools::Vector2<float>& size);
            void setPosition(const tools::Vector2<float> &pos);
            void drawObject() const;
        private:
            std::unordered_map<int, int> _animationMap;
            sf::Sprite sprite;
            int _rows;
            int _columns;
            std::shared_ptr<sf::RenderWindow> _ctx;
            bool _loop = true;
            sf::FloatRect _rect;
            int _currentAnimation;
            int _defaultAnimation;
            float _currentAnimRow;
            float _frameWidth;
            float _frameHeight;
            float _currentFrame;
            float acc = 0;
            float _fps;
    };
} // namespace sfml
