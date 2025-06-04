/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObjectFactory.hpp
*/

#pragma once
#include "Game/Renderer/Object/IAnimatedObject.hpp"
#include "Game/Renderer/Object/IStaticObject.hpp"
#include "Tools/Color/Color.hpp"
#include "Tools/Position/Position.hpp"
#include <memory>

namespace render
{
    class IObjectFactory
    {
    public:
        virtual ~IObjectFactory() = default;
        virtual std::unique_ptr<IAnimatedObject> createAnimatedObject(const std::string &path) = 0;
        virtual std::unique_ptr<IStaticObject> createStaticObject(const std::string &path) = 0;
        virtual std::unique_ptr<IObject> createCube(const tools::Color &Color, const tools::Position3D<float> &size) = 0;
    };
} // namespace render
