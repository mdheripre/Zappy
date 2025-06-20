/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLText.cpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Renderer/Object/IText.hpp"
#include <memory>

namespace sfml
{
    class SFMLText : public render::IText
    {
        public:
            SFMLText(sf::Font &font, std::shared_ptr<sf::RenderWindow> rWindow);
            ~SFMLText() = default;
            tools::Vector2<float> getPosition() const;
            tools::Vector2<float> getSize() const;
            void setPosition(const tools::Vector2<float> &pos);
            void setText(std::string text);
            void setSize(const tools::Vector2<float> &size);
            float getCharacterSize() const;
            void drawObject() const;
            void setCharacterSize(float size);
            int estimateMaxCharsPerLine(float width) const;
            float getLineHeight() const;
            bool contains(tools::Vector2<float> position);
            void setColor(const tools::Color &color);
        private:
            std::string _rawText;
            sf::Text _sfText;
            std::shared_ptr<sf::RenderWindow> _rWindow;
    };
} // namespace sfml
