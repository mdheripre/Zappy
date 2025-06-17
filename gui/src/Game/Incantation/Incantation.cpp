/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Incantation.cpp
*/

#include "Incantation.hpp"
gui::Incantation::Incantation(tools::Vector2<int> pos, int level, const std::vector<int> &playerIds, std::unique_ptr<render::IAnimatedSprite> incObject)
    : IncantationState(pos, level, playerIds), _incObject(std::move(incObject))
{
    tools::Vector2<float> size = _incObject->getSize();

    tools::Vector2<float> dPos(
        static_cast<float>(pos.x) * size.x,
        static_cast<float>(pos.y) * size.y
    );
    _incObject->setPosition(dPos);
    _position = pos;
}

bool gui::Incantation::update(float dt)
{
    if (_finished || !_incObject)
        return false;
    _incObject->updateObject(dt);
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


void gui::Incantation::draw() const
{
    _incObject->drawObject();
}
