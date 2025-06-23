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


/**
 * @brief Returns the position of the text.
 * 
 * @return 2D position.
 */
tools::Vector2<float> sfml::SFMLText::getPosition() const
{
    sf::Vector2f _sPos = _sfText.getPosition();

    return tools::Vector2<float>(_sPos.x, _sPos.y);
}

/**
 * @brief Returns the size of the text.
 * 
 * @return 2D size.
 */
tools::Vector2<float> sfml::SFMLText::getSize() const
{
    sf::FloatRect bounds = _sfText.getLocalBounds();
    return tools::Vector2<float>(bounds.width, bounds.height);
}

/**
 * @brief Sets the target size of the text.
 * 
 * @param targetSize Desired size.
 */
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

/**
 * @brief Gets the character size in pixels.
 * 
 * @return Font size.
 */
float sfml::SFMLText::getCharacterSize() const
{
    return _sfText.getCharacterSize();
}


/**
 * @brief Sets the position of the text.
 * 
 * @param pos New position.
 */
void sfml::SFMLText::setPosition(const tools::Vector2<float> &pos)
{
    _sfText.setPosition(pos.x, pos.y);
}


/**
 * @brief Sets the string content of the text.
 * 
 * @param text String to display.
 */
void sfml::SFMLText::setText(std::string text)
{
    _sfText.setString(text);
}


/**
 * @brief Draws the text to the window.
 */
void sfml::SFMLText::drawObject() const
{
    _rWindow->draw(_sfText);
}

/**
 * @brief Manually sets the character size.
 * 
 * @param size New size.
 */
void sfml::SFMLText::setCharacterSize(float size)
{
    _sfText.setCharacterSize(size);
}

/**
 * @brief Estimates the maximum number of characters that can fit in a line.
 * 
 * @param width Target width.
 * @return Estimated number of characters.
 */
int sfml::SFMLText::estimateMaxCharsPerLine(float width) const
{
    if (_sfText.getString().isEmpty())
        return 80; // par défaut

    sf::Text temp = _sfText;
    temp.setString("W"); // caractère large
    float charWidth = temp.getLocalBounds().width;
    return static_cast<int>(width / charWidth);
}


/**
 * @brief Returns the line height for vertical spacing.
 * 
 * @return Line height.
 */
float sfml::SFMLText::getLineHeight() const
{
    return static_cast<float>(_sfText.getCharacterSize()) * 1.3f;
}

/**
 * @brief Checks if a point is within the text bounds.
 * 
 * @param position Point to check.
 * @return true if inside.
 */
bool sfml::SFMLText::contains(tools::Vector2<float> position)
{
    return _sfText.getGlobalBounds().contains(sf::Vector2f(position.x, position.y));
}

/**
 * @brief Sets the fill color of the text.
 * 
 * @param color Desired color.
 */
void sfml::SFMLText::setColor(const tools::Color &color)
{
    _sfText.setFillColor({color.r, color.g, color.b, color.a});
}
