/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Incantation.cpp
*/

#include "Incantation.hpp"

bool gui::Incantation::update(float)
{
    if (_finished || !_incObject)
        return false;
    return true;
}

void gui::Incantation::succeed()
{
    _finished = true;
}

void gui::Incantation::failed()
{
    _finished = true;
}

gui::Incantation::Incantation(tools::Position<int> pos, int level, const std::vector<int> &playerIds, std::unique_ptr<render::IAnimatedObject> incObject)
    : IncantationState(pos, level, playerIds), _incObject(std::move(incObject))
{
    tools::Position3D<float> bb = _incObject->getBoundingBox().getSize();

    tools::Position3D<float> dPos(
        static_cast<float>(pos.x),
        bb.y,
        static_cast<float>(pos.y)
    );
    _incObject->setPosition(dPos);
    _position = pos;
}

void gui::Incantation::draw() const
{
    _incObject->drawObject();
}
