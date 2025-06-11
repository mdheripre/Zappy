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
        private:
            std::unordered_map<std::string, sf::Texture> _textureMap;
            std::shared_ptr<sf::RenderWindow> _rWindow;
    };
} // namespace sfml
