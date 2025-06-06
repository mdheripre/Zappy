/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibObjectFactory.cpp
*/

#include "RaylibObjectFactory.hpp"

/**
 * @brief Creates a new animated object from a model path and an animation map.
 *
 * Loads or reuses the model, then wraps it in a RaylibAnimatedObject.
 *
 * @param path Path to the model file.
 * @param animationMap Mapping between logical animation IDs and actual indices.
 * @return Unique pointer to the animated object.
 */
std::unique_ptr<render::IAnimatedObject> rl::RaylibObjectFactory::createAnimatedObject(const std::string& path, std::unordered_map<int, int> animationMap)
{
    std::shared_ptr<render::IModel> model = _mm.getOrLoad(path);

    return std::make_unique<rl::RaylibAnimatedObject>(model, animationMap);
}

/**
 * @brief Creates a new static object from a model path.
 *
 * Loads or reuses the model and wraps it in a RaylibStaticObject.
 *
 * @param path Path to the model file.
 * @return Unique pointer to the static object.
 */
std::unique_ptr<render::IStaticObject> rl::RaylibObjectFactory::createStaticObject(const std::string &path)
{
    std::shared_ptr<render::IModel> model = _mm.getOrLoad(path);

    return std::make_unique<rl::RaylibStaticObject>(model);
}

/**
 * @brief Creates a colored cube object of a given size.
 *
 * @param color Color of the cube.
 * @param size Size (width, height, depth) of the cube.
 * @return Unique pointer to the cube object.
 */
std::unique_ptr<render::IObject> rl::RaylibObjectFactory::createCube(const tools::Color &color, const tools::Position3D<float> &size)
{
    return std::make_unique<rl::CubeObject>(size, color);
}
