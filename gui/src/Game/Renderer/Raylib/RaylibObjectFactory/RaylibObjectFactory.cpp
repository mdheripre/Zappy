/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibObjectFactory.cpp
*/

#include "RaylibObjectFactory.hpp"

std::unique_ptr<render::IAnimatedObject> rl::RaylibObjectFactory::createAnimatedObject(const std::string& path)
{
    std::shared_ptr<render::IModel> model = _mm.getOrLoad(path);

    return std::make_unique<rl::RaylibAnimatedObject>(model);
}

std::unique_ptr<render::IStaticObject> rl::RaylibObjectFactory::createStaticObject(const std::string &path)
{
    std::shared_ptr<render::IModel> model = _mm.getOrLoad(path);

    return std::make_unique<rl::RaylibStaticObject>(model);
}

std::unique_ptr<render::IObject> rl::RaylibObjectFactory::createCube(const tools::Color &color, const tools::Position3D<float> &size)
{
    return std::make_unique<rl::CubeObject>(size, color);
}
