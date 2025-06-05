/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibObjectFactory.hpp
*/

#pragma once
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Game/Renderer/Raylib/RaylibObjectFactory/RaylibAnimatedObject/RaylibAnimatedObject.hpp"
#include "Game/Renderer/Raylib/RaylibObjectFactory/RaylibStaticObject/RaylibStaticObject.hpp"
#include "Game/Renderer/Raylib/RaylibObjectFactory/CubeObject/CubeObject.hpp"
#include "Game/Renderer/Raylib/RaylibObjectFactory/ModelManager/ModelManager.hpp"

namespace rl
{
    class RaylibObjectFactory : public render::IObjectFactory
    {
        private:
            ModelManager _mm;
        public:
            RaylibObjectFactory() = default;
            ~RaylibObjectFactory() = default;
            std::unique_ptr<render::IAnimatedObject> createAnimatedObject(const std::string &path, std::unordered_map<int, int> animationMap);
            std::unique_ptr<render::IStaticObject> createStaticObject(const std::string &path);
            std::unique_ptr<render::IObject> createCube(const tools::Color &Color, const tools::Position3D<float> &size);
    };
} // namespace rl
