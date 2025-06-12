/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.cpp
*/

#include "Trantorian.hpp"
#include "Tools/Error/Error.hpp"

/**
 * @brief Draws the Trantorian on screen.
 *
 * Delegates the rendering to the animated object if it exists.
 */
void gui::Trantorian::draw() const
{
    if (_trantorianObject)
        _trantorianObject->drawObject();
}

/**
 * @brief Moves the Trantorian away from a given direction.
 *
 * Simulates an expulsion from another player by updating the position
 * based on the given orientation, applying toroidal wrapping.
 *
 * @param O Orientation from which the expulsion occurs.
 * @param maxWidth Map width for wrap-around.
 * @param maxHeight Map height for wrap-around.
 */
void gui::Trantorian::expulseFrom(Orientation O, int maxWidth, int maxHeight)
{
    tools::Vector2<int> offset;
    switch (O) {
        case Orientation::NORTH: offset = {0, -1}; break;
        case Orientation::SOUTH: offset = {0, 1}; break;
        case Orientation::EAST:  offset = {1, 0}; break;
        case Orientation::WEST:  offset = {-1, 0}; break;
    }

    int newX = (_pos.x + offset.x + maxWidth) % maxWidth;
    int newY = (_pos.y + offset.y + maxHeight) % maxHeight;

    tools::Vector2<int> newPos(newX, newY);
    setPosition(newPos);
}

/**
 * @brief Removes a resource from the Trantorian's inventory.
 *
 * Decrements the quantity of the specified resource.
 * If it goes below zero, resets it to zero.
 *
 * @param res Resource to remove.
 * @throw EntityError if the resource index is invalid.
 */
void gui::Trantorian::removeFromInventory(Tile::Resource res)
{
    int index = static_cast<int>(res);

    if (index > _inventory.size() || index < 0)
        throw EntityError("Invalid resource index " + std::to_string(index));
    _inventory[index]--;
    if (_inventory[index] < 0)
        _inventory[index] = 0;
}

/**
 * @brief Adds a resource to the Trantorian's inventory.
 *
 * Increments the quantity of the specified resource.
 *
 * @param res Resource to add.
 * @throw EntityError if the resource index is invalid.
 */
void gui::Trantorian::addToInventory(Tile::Resource res)
{
    int index = static_cast<int>(res);

    if (index > _inventory.size() || index < 0)
        throw EntityError("Invalid resource index " + std::to_string(index));
    _inventory[index]++;
}

/**
 * @brief Updates the Trantorian's animation state.
 *
 * If the animation ends and the Trantorian is alive, it will loop the IDLE animation.
 * If the Trantorian is dead, it will return false to remove itself from rendering.
 *
 * @param dt Delta time since the last update.
 * @return true if the Trantorian should continue rendering, false otherwise.
 */
bool gui::Trantorian::update(float dt)
{
    bool anim_end = true;

    if (_trantorianObject)
        anim_end = _trantorianObject->updateObject(dt);
    else
        return false;

    if (anim_end && !_alive)
        return false;
    if (anim_end)
        _trantorianObject->playAnimation(
            static_cast<int>(TrantorianAnimation::IDLE), true);
    return true;
}

/**
 * @brief Sets the Trantorian's position on the map and updates its render position.
 *
 * Converts a grid position into a 3D position and updates the animated model accordingly.
 *
 * @param pos New map position (grid coordinates).
 */
void gui::Trantorian::setPosition(tools::Vector2<int>  pos)
{
    tools::Vector2<float> size = _trantorianObject->getSize();

    tools::Vector2<float> dPos(
        static_cast<float>(pos.x) * size.x,
        static_cast<float>(pos.y) * size.y
    );
    _trantorianObject->setPosition(dPos);
    _pos = pos;
}
