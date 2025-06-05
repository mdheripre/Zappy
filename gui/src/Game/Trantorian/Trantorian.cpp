/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.cpp
*/

#include "Trantorian.hpp"

void gui::Trantorian::draw() const
{
    if (_trantorianObject)
        _trantorianObject->drawObject();
}

void gui::Trantorian::expulseFrom(Orientation O, int maxWidth, int maxHeight)
{
    tools::Position<int> offset;
    switch (O) {
        case Orientation::NORTH: offset = {0, -1}; break;
        case Orientation::SOUTH: offset = {0, 1}; break;
        case Orientation::EAST:  offset = {1, 0}; break;
        case Orientation::WEST:  offset = {-1, 0}; break;
    }

    int newX = (_pos.x + offset.x + maxWidth) % maxWidth;
    int newY = (_pos.y + offset.y + maxHeight) % maxHeight;

    tools::Position<int> newPos(newX, newY);
    setPosition(newPos);
}

void gui::Trantorian::removeFromInventory(Tile::Resource res)
{
    int index = static_cast<int>(res);

    if (index > _inventory.size() || index < 0)
        throw std::runtime_error("Invalid ressource index " + std::to_string(index));
    _inventory[index]--;
    if (_inventory[index] < 0)
        _inventory[index] = 0;
}

void gui::Trantorian::addToInventory(Tile::Resource res)
{
    int index = static_cast<int>(res);

    if (index > _inventory.size() || index < 0)
        throw std::runtime_error("Invalid ressource index " + std::to_string(index));
    _inventory[index]++;
}

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
        _trantorianObject->playClip(
            static_cast<int>(TrantorianAnimation::IDLE), true);
    return true;
}

void gui::Trantorian::setPosition(tools::Position<int>  pos)
{
    tools::Position3D<float> bb = _trantorianObject->getBoundingBox().getSize();

    tools::Position3D<float> dPos(
        static_cast<float>(pos.x),
        bb.y,
        static_cast<float>(pos.y)
    );

    _trantorianObject->setPosition(dPos);
    _pos = pos;
}
