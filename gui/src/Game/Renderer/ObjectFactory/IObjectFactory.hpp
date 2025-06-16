/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObjectFactory.hpp
*/

#pragma once
#include "Game/Renderer/Object/IAnimatedSprite.hpp"
#include "Game/Renderer/Object/IStaticSprite.hpp"
#include "Tools/AssetDefinition/AssetDefinition.hpp"
#include "Game/Renderer/Object/ICanva.hpp"
#include "Game/Renderer/Object/IText.hpp"
#include "Tools/Color/Color.hpp"
#include <memory>

namespace render
{
    class IObjectFactory
    {
    public:
        virtual ~IObjectFactory() = default;
        virtual std::unique_ptr<IAnimatedSprite> createAnimatedSprite(const tools::AssetDefinition &definition) = 0;
        virtual std::unique_ptr<IStaticSprite> createStaticSprite(const tools::AssetDefinition &definition) = 0;
        virtual std::unique_ptr<IStaticSprite> createStaticSprite(const std::string &texturePath) = 0;
        virtual std::unique_ptr<ICanva> createCanva() const = 0;
        virtual std::unique_ptr<IText> createText(std::string fontPath) = 0;
    };
} // namespace render
