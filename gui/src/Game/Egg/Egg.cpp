/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#include "Egg.hpp"
#include <iostream>

gui::Egg::Egg(int id, tools::Vector2<int> pos, const std::string &teamName, std::unique_ptr<render::IAnimatedSprite> eggObject)
    : EntityState(id, pos, teamName), _eggObject(std::move(eggObject)) {
    setPosition(pos);
    if (_eggObject)
        _eggObject->playAnimation(static_cast<int>(gui::Egg::EggAnimation::IDLE), false);
}

bool gui::Egg::update(float dt)
{
    if (!_alive) {
        return false;
    }
    _eggObject->updateObject(dt);
    return true;
}

void gui::Egg::draw() const
{
    if (_eggObject) {
        _eggObject->drawObject();
    }
}

void gui::Egg::setPosition(tools::Vector2<int> pos)
{
    tools::Vector2<float> eggSize = _eggObject->getSize();
    tools::Vector2<float> dPos(
        (static_cast<float>(pos.x) * TILE_SIZE) + (TILE_SIZE - eggSize.x) / 2.0f,
        (static_cast<float>(pos.y) * TILE_SIZE) + (TILE_SIZE - eggSize.y) / 2.0f
    );
    _eggObject->setPosition(dPos);
    _pos = pos;
}


void gui::Egg::setDead()
{
    _alive = false;
}
