/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibStaticObject.cpp
*/

#include "CubeObject.hpp"

namespace rl {

/**
 * @brief Constructs a cube object with a given size and color.
 *
 * Also computes the cube's initial bounding box.
 *
 * @param size Dimensions of the cube.
 * @param color RGBA color of the cube.
 */
CubeObject::CubeObject(const tools::Position3D<float>& size, tools::Color color)
    : _size(size), _color(color) {
        _bb.min = {
            _position.x - _size.x / 2.0f,
            _position.y - _size.y / 2.0f,
            _position.z - _size.z / 2.0f
        };
    
        _bb.max = {
            _position.x + _size.x / 2.0f,
            _position.y + _size.y / 2.0f,
            _position.z + _size.z / 2.0f
        };
    }

/**
 * @brief Sets the world position of the cube.
 *
 * @param pos New 3D position.
 */
void CubeObject::setPosition(const tools::Position3D<float>& pos)
{
    _position = pos;
}

/**
 * @brief Gets the current world position of the cube.
 *
 * @return A reference to the 3D position.
 */
const tools::Position3D<float>& CubeObject::getPosition() const
{
    return _position;
}

/**
 * @brief Renders the cube in the scene.
 *
 * Draws both the filled cube and its black wireframe.
 */
void CubeObject::drawObject() const
{
    Vector3 pos = { _position.x, _position.y, _position.z };
    Vector3 size = { _size.x, _size.y, _size.z };
    ::Color rlColor = { _color.r, _color.g, _color.b, _color.a };

    DrawCube(pos, size.x, size.y, size.z, rlColor);
    DrawCubeWires(pos, size.x, size.y, size.z, BLACK);
}

/**
 * @brief Returns the cube's bounding box.
 *
 * @return A reference to the bounding box.
 */
const tools::BoundingBox& CubeObject::getBoundingBox() const
{
    return _bb;
}
}
