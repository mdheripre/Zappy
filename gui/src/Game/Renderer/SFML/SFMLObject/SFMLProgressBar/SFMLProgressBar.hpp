/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLCanva.hpp
*/

#pragma once

#include "Game/Renderer/Object/IProgressBar.hpp"
#include <memory>
#include <SFML/Graphics.hpp>

namespace sfml {

    class SFMLProgressBar : public render::IProgressBar {
    public:
        SFMLProgressBar(std::shared_ptr<sf::RenderWindow> rWindow);

        void setRange(float min, float max) override;
        void setValue(float value) override;
        void setPosition(const tools::Vector2<float>& pos) override;
        void setSize(const tools::Vector2<float>& size) override;
        tools::Vector2<float> getPosition() const override;
        tools::Vector2<float> getSize() const override;
        void drawObject() const override;
        void setColor(const tools::Color &color);
        bool contains(tools::Vector2<float> position);
    private:
        float _min;
        float _max;
        float _value;
        tools::Vector2<float> _pos;
        tools::Vector2<float> _size;
        sf::RectangleShape _background;
        sf::RectangleShape _bar;
        std::shared_ptr<sf::RenderWindow> _rWindow;
        void updateBar();
    };
}