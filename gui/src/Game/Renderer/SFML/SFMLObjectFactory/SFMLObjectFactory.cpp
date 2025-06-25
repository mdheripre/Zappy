/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLObjectFactory.cpp
*/

#include "SFMLObjectFactory.hpp"

namespace sfml {

/**
 * @brief Creates a static sprite using an asset definition.
 * 
 * @param definition Asset definition containing texture path and scale.
 * @return Unique pointer to the static sprite.
 * @throws std::runtime_error if texture can't be loaded.
 */
std::unique_ptr<render::IStaticSprite> SFMLObjectFactory::createStaticSprite(const tools::AssetDefinition& definition)
{
    const std::string& path = definition.getModelPath();

    // Load texture if not cached
    if (_textureMap.find(path) == _textureMap.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
            throw std::runtime_error("Failed to load texture: " + path);
        texture.setSmooth(true);
        _textureMap[path] = std::move(texture);
    }

    // Create and return the static sprite
    return std::make_unique<SFMLStaticSprite>(
        _textureMap.at(path),
        definition.getScale(),
        _rWindow
    );
}

/**
 * @brief Creates a static sprite using a direct texture path.
 * 
 * @param texturePath Path to the texture file.
 * @return Unique pointer to the static sprite.
 * @throws std::runtime_error if texture can't be loaded.
 */
std::unique_ptr<render::IStaticSprite> SFMLObjectFactory::createStaticSprite(const std::string &texturePath)
{
    const std::string& path = texturePath;

    if (_textureMap.find(path) == _textureMap.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
            throw std::runtime_error("Failed to load texture: " + path);
        texture.setSmooth(true);
        _textureMap[path] = std::move(texture);
    }

    return std::make_unique<SFMLStaticSprite>(
        _textureMap.at(path),
        _rWindow
    );
}

/**
 * @brief Creates a canva object used for viewport switching.
 * 
 * @return Unique pointer to ICanva.
 */
std::unique_ptr<render::ICanva> SFMLObjectFactory::createCanva() const
{
    return std::make_unique<SFMLCanva>(_rWindow);
}

/**
 * @brief Creates a text object with a given font path.
 * 
 * @param fontPath Path to the font file.
 * @return Unique pointer to IText.
 * @throws std::runtime_error if font can't be loaded.
 */
std::unique_ptr<render::IText> SFMLObjectFactory::createText(std::string fontPath)
{
    const std::string& path = fontPath;

    if (_fontMap.find(path) == _fontMap.end()) {
        sf::Font font;
        if (!font.loadFromFile(path))
            throw std::runtime_error("Failed to load font: " + path);
        font.setSmooth(true);
        _fontMap[path] = std::move(font);
    }

    return std::make_unique<SFMLText>(
        _fontMap.at(path),
        _rWindow
    );
}


/**
 * @brief Creates a simple drawable rectangle object.
 * 
 * @return Unique pointer to IObject.
 */
std::unique_ptr<render::IObject> SFMLObjectFactory::createRectangle() const
{
    return std::make_unique<SFMLRectangle>(_rWindow);
}


/**
 * @brief Creates a progress bar object.
 * 
 * @return Unique pointer to IProgressBar.
 */

std::unique_ptr<render::IProgressBar> SFMLObjectFactory::createProgressBar() const
{
    return std::make_unique<SFMLProgressBar>(_rWindow);
}

std::unique_ptr<render::IObject> SFMLObjectFactory::createRoundedRectangle(int radius) const
{
    return std::make_unique<SFMLRoundedRectangle>(_rWindow, radius);
}

/**
 * @brief Creates an animated sprite using an asset definition.
 * 
 * @param definition Asset definition containing texture, animation frames, and fps.
 * @return Unique pointer to IAnimatedSprite.
 * @throws std::runtime_error if texture can't be loaded.
 */
std::unique_ptr<render::IAnimatedSprite> SFMLObjectFactory::createAnimatedSprite(const tools::AssetDefinition& definition)
{
    const std::string& path = definition.getModelPath();

    if (_textureMap.find(path) == _textureMap.end()) {
        sf::Texture texture;
        if (!texture.loadFromFile(path))
            throw std::runtime_error("Failed to load animated texture: " + path);
        texture.setSmooth(true);
        _textureMap[path] = std::move(texture);
    }
    return std::make_unique<SFMLAnimatedSprite>(
        _textureMap.at(path),
        _rWindow,
        definition.getFrameWidth(),
        definition.getFrameHeight(),
        definition.getScale(),
        definition.getAnimation()
    );
}

} // namespace sfml

