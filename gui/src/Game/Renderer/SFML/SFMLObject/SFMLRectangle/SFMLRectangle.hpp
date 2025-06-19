/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLStaticSprite.hpp
*/

#pragma once

#include "Game/Renderer/Object/IObject.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace sfml
{
    class SFMLRectangle : public render::IObject
    {
        public:
            SFMLRectangle(std::shared_ptr<sf::RenderWindow> rWindow);
            ~SFMLRectangle() = default;
            tools::Vector2<float> getPosition() const;
            tools::Vector2<float> getSize() const;
            void setSize(const tools::Vector2<float> &size);
            void setPosition(const tools::Vector2<float> &pos);
            void drawObject() const;
            bool contains(tools::Vector2<float> position);
            void setColor(const tools::Color &color);
        private:
            sf::RectangleShape _rect;
            std::shared_ptr<sf::RenderWindow> _rWindow;
    };
} // namespace sfml
