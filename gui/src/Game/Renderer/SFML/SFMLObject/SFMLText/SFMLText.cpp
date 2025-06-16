/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLText.cpp
*/

#include "SFMLText.hpp"

sfml::SFMLText::SFMLText(sf::Font &font, std::shared_ptr<sf::RenderWindow> rWindow) : 
    _rWindow(rWindow)
{
    _sfText.setFont(font);
}

tools::Vector2<float> sfml::SFMLText::getPosition() const
{
    sf::Vector2f _sPos = _sfText.getPosition();

    return tools::Vector2<float>(_sPos.x, _sPos.y);
}

tools::Vector2<float> sfml::SFMLText::getSize() const
{
    sf::FloatRect bounds = _sfText.getLocalBounds();
    return tools::Vector2<float>(bounds.width, bounds.height);
}

void sfml::SFMLText::setSize(const tools::Vector2<float> &targetSize)
{
    if (_sfText.getString().isEmpty())
        return;

    unsigned int size = _sfText.getCharacterSize();

    sf::FloatRect bounds = _sfText.getLocalBounds();

    float heightFactor = targetSize.y / bounds.height;

    size = static_cast<unsigned int>(size * heightFactor);
    _sfText.setCharacterSize(size);

    bounds = _sfText.getLocalBounds();
    if (bounds.width > targetSize.x) {
        float widthFactor = targetSize.x / bounds.width;
        size = static_cast<unsigned int>(size * widthFactor);
        _sfText.setCharacterSize(size);
    }
}


void sfml::SFMLText::setPosition(const tools::Vector2<float> &pos)
{
    _sfText.setPosition(pos.x, pos.y);
}

void sfml::SFMLText::setText(std::string text)
{
    _sfText.setString(text);
}

void sfml::SFMLText::drawObject() const
{
    _rWindow->draw(_sfText);
}