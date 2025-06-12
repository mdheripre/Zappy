/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#include "Egg.hpp"

bool gui::Egg::update(float dt)
{
    if (!_alive)
        return false;
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
    tools::Vector2<float> size = _eggObject->getSize();

    tools::Vector2<float> dPos(
        static_cast<float>(pos.x) * size.x,
        static_cast<float>(pos.y) * size.y
    );
    _eggObject->setPosition(dPos);
    _pos = pos;
}

gui::Egg::Egg(int id, tools::Vector2<int> pos, const std::string &teamName, std::unique_ptr<render::IAnimatedSprite> eggObject)
    : EntityState(id, pos, teamName), _eggObject(std::move(eggObject)) {
    setPosition(pos);
}

void gui::Egg::setDead()
{
    _alive = false;
}
