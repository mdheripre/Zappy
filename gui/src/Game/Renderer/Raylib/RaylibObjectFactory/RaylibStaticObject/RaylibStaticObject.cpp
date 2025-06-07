/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibStaticObject.cpp
*/

#include "RaylibStaticObject.hpp"

namespace rl {

/**
 * @brief Constructs a RaylibStaticObject.
 *
 * Wraps a model that does not require animation.
 *
 * @param model Shared pointer to the 3D model to render.
 */
RaylibStaticObject::RaylibStaticObject(std::shared_ptr<render::IModel> model)
    : _model(std::move(model)) {}

/**
 * @brief Sets the world position of the static object.
 *
 * @param pos 3D position in the world.
 */
void RaylibStaticObject::setPosition(const tools::Position3D<float>& pos)
{
    _position = pos;
}

/**
 * @brief Returns the current world position of the object.
 *
 * @return Reference to the 3D position.
 */
const tools::Position3D<float>& RaylibStaticObject::getPosition() const
{
    return _position;
}

/**
 * @brief Renders the static object at its current position.
 *
 * Delegates drawing to the wrapped model.
 */
void RaylibStaticObject::drawObject() const
{
    _model->drawAt(_position);
}

/**
 * @brief Returns the cube's bounding box.
 *
 * @return A reference to the bounding box.
 */
const tools::BoundingBox& RaylibStaticObject::getBoundingBox() const
{
    return _model->getBoundingBox();
}
}
