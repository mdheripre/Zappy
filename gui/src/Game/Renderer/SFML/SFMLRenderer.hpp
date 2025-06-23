/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLRenderer.cpp
*/

#pragma once
#include "Game/Renderer/IRenderer.hpp"
#include "Game/Renderer/SFML/SFMLObjectFactory/SFMLObjectFactory.hpp"
#include "Tools/Error/Error.hpp"
#include "Game/Renderer/Entity/AInteractiveEntity.hpp"
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
        void setUI(std::shared_ptr<render::IRenderEntity> ui);
        void setBindings(std::unordered_map<tools::KeyCode, std::function<void()>> bindings) {_bindings = bindings;};
        render::IObjectFactory &getFactory();
        void setPositionView(int offsetX, int offsetY);
        void setZoomView(float factor);
        void updateUI(float dt);
        void poll();
        void manageKeyCode(const sf::Event &event);
        const std::unordered_map<sf::Keyboard::Key, tools::KeyCode> _keyMap = {
            { sf::Keyboard::Right, tools::KeyCode::Right },
            { sf::Keyboard::Left,  tools::KeyCode::Left },
            { sf::Keyboard::Up,    tools::KeyCode::Up },
            { sf::Keyboard::Down,  tools::KeyCode::Down },
            { sf::Keyboard::W,     tools::KeyCode::W },
            { sf::Keyboard::S,     tools::KeyCode::S },
            { sf::Keyboard::P,     tools::KeyCode::P },
            { sf::Keyboard::M,     tools::KeyCode::M },
            { sf::Keyboard::A,     tools::KeyCode::A },
            { sf::Keyboard::Z,     tools::KeyCode::Z },
            { sf::Keyboard::E,     tools::KeyCode::E },
            { sf::Keyboard::R,     tools::KeyCode::R },
            { sf::Keyboard::T,     tools::KeyCode::T }
        };
    private:
        void handleMouseInteraction();
        std::unordered_map<tools::KeyCode, std::function<void()>> _bindings;
        std::shared_ptr<sf::RenderWindow> _rWindow;
        std::unique_ptr<SFMLObjectFactory> _objFactory;
        std::list<std::shared_ptr<render::IRenderEntity>> _entities;
        std::shared_ptr<render::IRenderEntity> _ui;
    }; 
} // namespace sfml
