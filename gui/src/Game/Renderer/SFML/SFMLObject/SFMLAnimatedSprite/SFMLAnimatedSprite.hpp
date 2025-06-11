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
                std::unordered_map<int, int> _animationMap);
            ~SFMLAnimatedSprite() = default;
            void playAnimation(int clipIndex, bool loop);
            bool updateObject(float dt);
            const tools::Vector2<float> &getPosition() const;
            const tools::Vector2<float> &getSize() const;
            void setPosition(const tools::Vector2<float> &pos);
            void drawObject() const;
        private:
            std::unordered_map<int, int> _animationMap;
            sf::Sprite sprite;
            std::shared_ptr<sf::RenderWindow> _ctx;
            sf::FloatRect _rect;
    };
} // namespace sfml
