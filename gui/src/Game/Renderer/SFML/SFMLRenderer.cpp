/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLRenderer.cpp
*/

#include "SFMLRenderer.hpp"

sfml::SFMLRenderer::SFMLRenderer()
{
    _rWindow = std::make_shared<sf::RenderWindow>();
    _objFactory = std::make_unique<SFMLObjectFactory>(_rWindow);
}


void sfml::SFMLRenderer::init(std::string title, int width, int height, int frameRate)
{
    if (!_rWindow)
        throw RenderError("Access to a null window in renderer init");
    _rWindow->create(
        sf::VideoMode(width, height),
        title,
        sf::Style::Close | sf::Style::Titlebar
    );
    _rWindow->setFramerateLimit(frameRate);
}

void sfml::SFMLRenderer::update(float dt)
{
    auto shouldRemove = [dt](const std::shared_ptr<render::IRenderEntity>& entity) {
        return entity && !entity->update(dt);
    };

    _entities.erase(
        std::remove_if(_entities.begin(), _entities.end(), shouldRemove),
        _entities.end()
    );
}

/**
 * @brief Renders the entire scene.
 *
 * Draws all entities, and ends the drawing frame.
 * Also clears the background at the start.
 */

void sfml::SFMLRenderer::render()
{
    _rWindow->clear(sf::Color::Black);
    for (auto& entity : _entities) {
        if (entity)
            entity->draw();
    }
    _rWindow->display();
}

bool sfml::SFMLRenderer::isClose() const
{
    return !_rWindow->isOpen();
}

void sfml::SFMLRenderer::pushEntity(std::shared_ptr<render::IRenderEntity> renderEntity)
{
    _entities.push_back(renderEntity);
}

render::IObjectFactory &sfml::SFMLRenderer::getFactory()
{
    return *_objFactory;
}

void sfml::SFMLRenderer::poll()
{
    sf::Event event;
    while (_rWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _rWindow->close();
        else if (event.type == sf::Event::KeyPressed) {
            manageKeyCode(event);
        }
    }
}

void sfml::SFMLRenderer::manageKeyCode(const sf::Event &event)
{
    auto it = _keyMap.find(event.key.code);

    if (it != _keyMap.end()) {
        auto bindIt = _bindings.find(it->second);

        if (bindIt != _bindings.end())
            bindIt->second();
    }
}
