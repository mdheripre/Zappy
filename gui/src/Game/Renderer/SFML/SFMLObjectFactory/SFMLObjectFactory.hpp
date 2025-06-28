/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** SFMLObjectFactory.cpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Game/Renderer/SFML/SFMLObject/SFMLAnimatedSprite/SFMLAnimatedSprite.hpp"
#include "Game/Renderer/SFML/SFMLObject/SFMLStaticSprite/SFMLStaticSprite.hpp"
#include "Game/Renderer/SFML/SFMLObject/SFMLText/SFMLText.hpp"
#include "Game/Renderer/SFML/SFMLObject/SFMLCanva/SFMLCanva.hpp"
#include "Game/Renderer/SFML/SFMLObject/SFMLRectangle/SFMLRectangle.hpp"
#include "Game/Renderer/SFML/SFMLObject/SFMLRoundedRectangle/SFMLRoundedRectangle.hpp"
#include "Game/Renderer/SFML/SFMLObject/SFMLProgressBar/SFMLProgressBar.hpp"
#include "Game/Renderer/SFML/SFMLSound/SFMLSound.hpp"
#include <memory>
#include <unordered_map>

namespace sfml
{
    class SFMLObjectFactory : public render::IObjectFactory
    {
        public:
            SFMLObjectFactory(std::shared_ptr<sf::RenderWindow> rWindow) : 
                _rWindow(rWindow) {};
            ~SFMLObjectFactory() = default;
            std::unique_ptr<render::IAnimatedSprite> createAnimatedSprite(const tools::AssetDefinition &definition);
            std::unique_ptr<render::IStaticSprite> createStaticSprite(const tools::AssetDefinition &definition);
            std::unique_ptr<render::IStaticSprite> createStaticSprite(const std::string &texturePath);
            std::unique_ptr<render::ICanva> createCanva() const;
            std::unique_ptr<render::IText> createText(std::string fontPath);
            std::unique_ptr<render::IObject> createRectangle() const;
            std::unique_ptr<render::IProgressBar> createProgressBar() const;
            std::unique_ptr<render::IObject> createRoundedRectangle(int radius) const;
            std::unique_ptr<render::ISound> createSound(const std::string &soundPath);
        private:
            std::unordered_map<std::string, sf::Texture> _textureMap;
            std::unordered_map<std::string, sf::Font> _fontMap;
            std::unordered_map<std::string, sf::SoundBuffer> _soundBufferMap;
            std::shared_ptr<sf::RenderWindow> _rWindow;
    };
} // namespace sfml
