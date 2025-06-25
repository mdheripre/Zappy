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
    int posX = (1920 - width) / 2;
    int posY = (1080 - height) / 2;
    _rWindow->setPosition(sf::Vector2i(posX, posY));
    _rWindow->setFramerateLimit(frameRate);

    sf::View defaultView = _rWindow->getDefaultView();
    _rWindow->setView(defaultView);

    _zoomFactor = 1.0f;
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
    if (_ui)
        _ui->draw();
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

void sfml::SFMLRenderer::setUI(std::shared_ptr<render::IRenderEntity> ui)
{
    _ui = ui;
}

void sfml::SFMLRenderer::clear()
{
    _entities.clear();
}

render::IObjectFactory &sfml::SFMLRenderer::getFactory()
{
    return *_objFactory;
}

void sfml::SFMLRenderer::setPositionView(int offsetX, int offsetY)
{
    sf::View view = _rWindow->getView();

    view.move(offsetX, offsetY);
    _rWindow->setView(view);
}

void sfml::SFMLRenderer::centerViewOn(float x, float y)
{
    sf::View view = _rWindow->getView();
    view.setCenter(x, y);
    _rWindow->setView(view);
    _viewCenter = {x, y};
}

void sfml::SFMLRenderer::setZoomView(float factor)
{
    float zoomFactor = _zoomFactor * factor;

    if (zoomFactor < 0.5f || zoomFactor > 2.1f) {
        return;
    }

    sf::View view = _rWindow->getView();
    view.zoom(factor);
    _rWindow->setView(view);
    _zoomFactor = zoomFactor;

}

void sfml::SFMLRenderer::resetZoomView()
{
    sf::View view = _rWindow->getDefaultView();
    view.setCenter(_viewCenter.x, _viewCenter.y); // recentre sur la map
    _rWindow->setView(view);
    _zoomFactor = 1.0f;
}


void sfml::SFMLRenderer::updateUI(float dt)
{
    if (_ui)
        _ui->update(dt);
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
    handleMouseInteraction();
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

void sfml::SFMLRenderer::handleMouseInteraction()
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*_rWindow);
    sf::Vector2f worldPos = _rWindow->mapPixelToCoords(pixelPos);
    tools::Vector2<float> mouse(worldPos.x, worldPos.y);

    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    bool hoverHandled = false;

    for (auto it = _entities.rbegin(); it != _entities.rend(); ++it) {
        auto* interactive = dynamic_cast<render::AInteractiveEntity*>(it->get());
        if (!interactive)
            continue;

        if (!hoverHandled && interactive->isMouseOver(mouse)) {
            interactive->computeHover(mouse);
            interactive->processClick(mousePressed, true);
            hoverHandled = true;
        } else {
            interactive->computeHover({-9999.f, -9999.f});
            interactive->processClick(mousePressed, false);
        }
    }
}


