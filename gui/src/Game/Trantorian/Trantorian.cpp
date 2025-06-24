/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.cpp
*/

#include "Trantorian.hpp"
#include "Tools/Error/Error.hpp"


gui::Trantorian::Trantorian(int id, tools::Vector2<int> pos, 
    const std::string &teamName,
    Orientation orientation,
    int level,
    std::unique_ptr<render::IAnimatedSprite> trantorianObject,
    std::shared_ptr<ITrantorianUI> uiController)
        : TrantorianState(id, pos, teamName, orientation),
        _trantorianObject(std::move(trantorianObject)),
        _uiController(uiController) 
{
    _level = level;
    setPosition(pos);
}

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

bool gui::Trantorian::isMouseOver(const tools::Vector2<float> &mousePosition) const
{
    return _trantorianObject->contains(mousePosition);
}

void gui::Trantorian::laidAnEgg()
{
    _currentAction = "Laid an egg";
}
void gui::Trantorian::expulse()
{
    switch (_orientation)
    {
    case Orientation::NORTH:
        _trantorianObject->playAnimation(static_cast<int>(Trantorian::TrantorianAnimation::EJECT_NORTH), false);
        break;
    case Orientation::EAST:
        _trantorianObject->playAnimation(static_cast<int>(Trantorian::TrantorianAnimation::EJECT_EAST), false);
        break;
    case Orientation::SOUTH:
        _trantorianObject->playAnimation(static_cast<int>(Trantorian::TrantorianAnimation::EJECT_SOUTH), false);
        break;
    case Orientation::WEST:
        _trantorianObject->playAnimation(static_cast<int>(Trantorian::TrantorianAnimation::EJECT_WEST), false);
        break;
    default:
        break;
    }
    _currentAction = "Expulse";
};

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
    _currentAction = "Explused from " + orientationToString(O);
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
    _currentAction = "Drop " + Tile::resToString.at(res);
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
    _currentAction = "Take " + Tile::resToString.at(res);
}

void gui::Trantorian::startIncantation()
{
    _currentAction = "Do an incantation ";
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
    if (!_alive)
        return false;
    return true;
}

/**
 * @brief Sets the Trantorian's position on the map and updates its render position.
 *
 * Converts a grid position into a 3D position and updates the animated model accordingly.
 *
 * @param pos New map position (grid coordinates).
 */

void gui::Trantorian::setPosition(tools::Vector2<int> pos)
{
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(42);
        seeded = true;
    }

    tools::Vector2<float> tranSize = _trantorianObject->getSize();

    const float maxOffset = TILE_SIZE * 0.05f;
    float offsetX = (static_cast<float>(std::rand()) / RAND_MAX) * 2.0f * maxOffset - maxOffset;
    float offsetY = (static_cast<float>(std::rand()) / RAND_MAX) * 2.0f * maxOffset - maxOffset;

    tools::Vector2<float> dPos(
        (static_cast<float>(pos.x) * TILE_SIZE) + (TILE_SIZE - tranSize.x) / 2.0f + offsetX,
        (static_cast<float>(pos.y) * TILE_SIZE) + (TILE_SIZE - tranSize.y) / 2.0f + offsetY);

    _currentAction = "Move";
    _trantorianObject->setPosition(dPos);
    _pos = pos;
}

/**
 * @brief Triggered when the mouse hovers over the Trantorian.
 * Changes the color to highlight hover state.
 */
void gui::Trantorian::onHoverEnter()
{
    _trantorianObject->setColor(tools::Color(255, 255, 180, 255));
}

/**
 * @brief Triggered when the mouse stops hovering over the Trantorian.
 * Resets the color to default.
 */
void gui::Trantorian::onHoverExit()
{
    _trantorianObject->setColor(tools::Color(255, 255, 255, 255));
}


/**
 * @brief Triggered when the Trantorian is clicked.
 * Sends this Trantorian's info and a cloned sprite to the UI controller.
 */
void gui::Trantorian::onClick()
{
    _uiController->setTrantInfo(shared_from_this(), _trantorianObject->clone());
}
