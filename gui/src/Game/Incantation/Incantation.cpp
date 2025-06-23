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


/**
 * @brief Updates the incantation animation.
 * 
 * Does nothing if the incantation is already finished or if the animation object is null.
 * 
 * @param dt Delta time since the last update.
 * @return true if the incantation was updated, false otherwise.
 */
bool gui::Incantation::update(float dt)
{
    if (_finished || !_incObject)
        return false;
    _incObject->updateObject(dt);
    return true;
}

/**
 * @brief Marks the incantation as successful.
 * 
 * Sets the internal state to finished, stopping further updates or animations.
 */

void gui::Incantation::succeed()
{
    _finished = true;
}

/**
 * @brief Marks the incantation as failed.
 * 
 * Sets the internal state to finished, stopping further updates or animations.
 */
void gui::Incantation::failed()
{
    _finished = true;
}

/**
 * @brief Draws the incantation animation to the screen.
 * 
 * Calls the internal draw method of the animated sprite.
 */
void gui::Incantation::draw() const
{
    _incObject->drawObject();
}
