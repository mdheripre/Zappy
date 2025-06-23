/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#include "Egg.hpp"
#include <iostream>

const tools::AssetDefinition gui::Egg::defaultAsset = tools::AssetDefinition(
    "gui/assets/Tiny Swords/Factions/Knights/Troops/Pawn/Yellow/Pawn_Yellow.png",
    {
        {static_cast<int>(gui::Egg::EggAnimation::IDLE), {false, 0, 6}}
    },
    TILE_SIZE,
    6,
    6
);


gui::Egg::Egg(int id, tools::Vector2<int> pos, const std::string &teamName, std::unique_ptr<render::IAnimatedSprite> eggObject)
    : EntityState(id, pos, teamName), _eggObject(std::move(eggObject)) {
    setPosition(pos);
    if (_eggObject)
        _eggObject->playAnimation(static_cast<int>(gui::Egg::EggAnimation::IDLE), false);
}

/**
 * @brief Updates the Egg's animation.
 * 
 * Skips update if the Egg is marked as dead.
 * 
 * @param dt Delta time since the last update.
 * @return true if the Egg is still alive and was updated, false otherwise.
 */
bool gui::Egg::update(float dt)
{
    if (!_alive) {
        return false;
    }
    _eggObject->updateObject(dt);
    return true;
}

/**
 * @brief Draws the Egg on screen.
 * 
 * Calls the internal draw method of the animated sprite.
 * Does nothing if the sprite is null.
 */
void gui::Egg::draw() const
{
    if (_eggObject) {
        _eggObject->drawObject();
    }
}

/**
 * @brief Sets the position of the Egg.
 * 
 * Calculates pixel-perfect position to center the sprite inside the tile.
 * 
 * @param pos New tile-based position.
 */
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


/**
 * @brief Marks the Egg as dead.
 * 
 * After calling this method, the Egg will no longer be updated or rendered.
 */
void gui::Egg::setDead()
{
    _alive = false;
}
