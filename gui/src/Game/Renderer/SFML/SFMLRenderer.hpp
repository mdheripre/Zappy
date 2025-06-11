/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLRenderer.cpp
*/

#pragma once
#include "Game/Renderer/IRenderer.hpp"
#include "Game/Renderer/SFML/SFMLObjectFactory/SFMLObjectFactory.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <list>

namespace sfml
{
    class SFMLRenderer : public render::IRenderer
    {
    public:
        SFMLRenderer();
        ~SFMLRenderer() = default;
        void init(std::string title, int width, int height, int frameRate);
        void update(float dt);
        void render();
        bool isClose() const;
        void pushEntity(std::shared_ptr<render::IRenderEntity> renderEntity);
        void setBindings(std::unordered_map<tools::KeyCode, std::function<void()>> bindings) {_bindings = bindings;};
        render::IObjectFactory &getFactory();
        void poll();
        const std::unordered_map<tools::KeyCode, sf::Keyboard::Key> _keyMap = {
            { tools::KeyCode::Right, sf::Keyboard::Right },
            { tools::KeyCode::Left,  sf::Keyboard::Left },
            { tools::KeyCode::Up,    sf::Keyboard::Up },
            { tools::KeyCode::Down,  sf::Keyboard::Down },
            { tools::KeyCode::W,     sf::Keyboard::W },
            { tools::KeyCode::S,     sf::Keyboard::S }
        };
    private:
        std::unordered_map<tools::KeyCode, std::function<void()>> _bindings;
        std::shared_ptr<sf::RenderWindow> _rWindow;
        std::unique_ptr<SFMLObjectFactory> _objFactory;
        std::list<std::shared_ptr<render::IRenderEntity>> _entities;
    }; 
} // namespace sfml
