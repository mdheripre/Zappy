/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLRoundedRectangle.hpp
*/

#pragma once

#include "Game/Renderer/Object/IObject.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace sfml
{
    class SFMLRoundedRectangle : public render::IObject
    {
        public:
            SFMLRoundedRectangle(std::shared_ptr<sf::RenderWindow> rWindow, int radius);
            ~SFMLRoundedRectangle() = default;
            tools::Vector2<float> getPosition() const;
            tools::Vector2<float> getSize() const;
            void setSize(const tools::Vector2<float> &size);
            void setPosition(const tools::Vector2<float> &pos);
            void drawObject() const;
            bool contains(tools::Vector2<float> position);
            void setColor(const tools::Color &color);
        private:
            int _radius;
            tools::Vector2<float> _pos;
            std::shared_ptr<sf::RenderWindow> _rWindow;
            sf::RectangleShape _center;
            sf::RectangleShape _hBar;
            sf::RectangleShape _vBar;
            sf::CircleShape _topLeft;
            sf::CircleShape _bottomRight;
            sf::CircleShape _topRight;
            sf::CircleShape _bottomLeft;
    };
} // namespace sfml
