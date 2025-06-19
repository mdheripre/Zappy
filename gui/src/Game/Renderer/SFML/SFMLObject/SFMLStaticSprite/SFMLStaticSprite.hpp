/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLStaticSprite.hpp
*/

#pragma once

#include "Game/Renderer/Object/IStaticSprite.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace sfml
{
    class SFMLStaticSprite : public render::IStaticSprite
    {
    public:
        SFMLStaticSprite(const sf::Texture& texture, float scale, std::shared_ptr<sf::RenderWindow> window);
        SFMLStaticSprite(const sf::Texture& texture, std::shared_ptr<sf::RenderWindow> window);
        ~SFMLStaticSprite() override = default;

        tools::Vector2<float> getPosition() const override;
        tools::Vector2<float> getSize() const override;
        void setPosition(const tools::Vector2<float>& pos) override;
        void setSize(const tools::Vector2<float> &size);
        void drawObject() const override;
        bool contains(tools::Vector2<float> position);
        void setColor(const tools::Color &color);
    private:
        std::shared_ptr<sf::RenderWindow> _window;
        sf::Sprite _sprite;
    };
}
