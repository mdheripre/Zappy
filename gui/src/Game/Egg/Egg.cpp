/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#include "Egg.hpp"

bool gui::Egg::update(float)
{
    if (!_alive)
        return false;
    return true;
}

void gui::Egg::draw() const
{
    if (_eggObject)
        _eggObject->drawObject();
}

void gui::Egg::setPosition(tools::Position<int> pos)
{
    tools::Position3D<float> bb = _eggObject->getBoundingBox().getSize();

    tools::Position3D<float> dPos(
        static_cast<float>(pos.x),
        bb.y,
        static_cast<float>(pos.y)
    );
    _eggObject->setPosition(dPos);
    _pos = pos;
}

gui::Egg::Egg(int id, tools::Position<int> pos, const std::string &teamName, std::unique_ptr<render::IAnimatedObject> eggObject)
    : EntityState(id, pos, teamName), _eggObject(std::move(eggObject)) {
    setPosition(pos);
}

void gui::Egg::setDead()
{
    _alive = false;
}
