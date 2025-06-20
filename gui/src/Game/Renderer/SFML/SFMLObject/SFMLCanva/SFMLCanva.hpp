/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLCanva.hpp
*/


#pragma once

#include "Game/Renderer/Object/ICanva.hpp"
#include "Tools/Error/Error.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

namespace sfml {
    class SFMLCanva : public render::ICanva {
    public:
        SFMLCanva(std::shared_ptr<sf::RenderWindow> window);
        ~SFMLCanva() override = default;

        tools::ViewPort getViewPort() const override;
        void beginUI() const;
        void endUI() const;

    private:
        std::shared_ptr<sf::RenderWindow> _window;
        mutable sf::View _previousView;
    };
}