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

    /**
     * @brief Returns the current viewport of the canvas.
     * 
     * @return ViewPort containing center and size.
     * @throws RenderError if the window is null.
     */
    tools::ViewPort SFMLCanva::getViewPort() const {
        if (!_window)
            throw RenderError("Call getViewPort() but Canva has no window");

        auto view = _window->getView();
        return tools::ViewPort(view.getCenter().x, view.getCenter().y,
                               view.getSize().x, view.getSize().y);
    }

    /**
     * @brief Prepares the window for UI drawing by setting the view to screen space.
     */
    void SFMLCanva::beginUI() const {
        if (!_window)
            return;

        _previousView = _window->getView();
        sf::View uiView(sf::FloatRect(0, 0, _window->getSize().x, _window->getSize().y));
        _window->setView(uiView);
    }


    /**
     * @brief Restores the previous view after UI drawing.
     */
    void SFMLCanva::endUI() const {
        if (_window)
            _window->setView(_previousView);
    }

}
