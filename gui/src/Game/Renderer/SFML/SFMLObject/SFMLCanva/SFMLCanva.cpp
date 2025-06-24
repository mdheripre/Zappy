/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLCanva.hpp
*/


#include "SFMLCanva.hpp"

namespace sfml {

    SFMLCanva::SFMLCanva(std::shared_ptr<sf::RenderWindow> window)
        : _window(std::move(window)) {}

    tools::ViewPort SFMLCanva::getViewPort() const {
        if (!_window)
            throw RenderError("Call getViewPort() but Canva has no window");

        auto view = _window->getView();
        return tools::ViewPort(view.getCenter().x, view.getCenter().y,
                               view.getSize().x, view.getSize().y);
    }

    void SFMLCanva::beginUI() const {
        if (!_window)
            return;

        _previousView = _window->getView();
        sf::View uiView(sf::FloatRect(0, 0, _window->getSize().x, _window->getSize().y));
        _window->setView(uiView);
    }

    void SFMLCanva::endUI() const {
        if (_window)
            _window->setView(_previousView);
    }

}
