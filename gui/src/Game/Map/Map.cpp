/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Map.cpp
*/

#include "Map.hpp"
#include "Tools/Error/Error.hpp"

/**
 * @brief Constructs a Map object with rendering capabilities.
 *
 * @param width Width of the map in tiles.
 * @param height Height of the map in tiles.
 * @param tileObject Renderable tile object (base ground).
 * @param propsObject Array of 7 animated objects representing resources.
 */
gui::Map::Map(int width, int height, std::unique_ptr<render::IObject> tileObject, std::array<std::unique_ptr<render::IAnimatedSprite>, 7> propsObject)
    : MapState(width, height),
    _width(width),
    _height(height),
    _map(width, std::vector<Tile>(height)),
    _tileObject(std::move(tileObject)),
    _propsObject(std::move(propsObject)) {}


/**
 * @brief Gets the tile at a specific position.
 *
 * @param pos Tile position.
 * @return The tile at the given position.
 * @throw GameStateError if position is out of bounds.
 */
const gui::Tile& gui::MapState::getTile(const tools::Vector2<int> &pos) const
{
    if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height)
        throw GameStateError("Tile position (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") out of map bounds [0-" + std::to_string(_width-1) + ", 0-" + std::to_string(_height-1) + "]");
    return _map[pos.y][pos.x];
}


/**
 * @brief Sets a tile at the specified position.
 *
 * @param tile Tile data to set.
 * @param pos Position to place the tile.
 * @throw GameStateError if position is out of bounds.
 */
void gui::Map::setTile(const Tile &tile, const tools::Vector2<int> &pos)
{
    if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height)
        throw GameStateError("Tile position (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") out of map bounds [0-" + std::to_string(_width-1) + ", 0-" + std::to_string(_height-1) + "]");
    _map[pos.y][pos.x] = tile;
}


/**
 * @brief Draws resource props (animated objects) on a tile.
 *
 * Places them in a 3x3 grid within the tile bounds.
 *
 * @param tile The tile whose resources to draw.
 * @param tilePos The world position of the tile.
 */
void gui::Map::drawProps(const Tile &tile, const tools::Vector2<float> &tilePos) const
{
    const std::array<int, 7> &ress = tile.getResources();
    tools::Vector2<float> tileSize = _tileObject->getSize();
    float cellSizeX = tileSize.x / 3.0f;
    float cellSizeY = tileSize.y / 3.0f;
    int placed = 0;

    for (int i = 0; i < 7; ++i) {
        if (_propsObject[i] && ress[i] > 0) {
            int cellX = placed % 3;
            int cellY = placed / 3;
            tools::Vector2<float>  offset(
                (cellX - 1) * cellSizeX,
                (cellY - 1) * cellSizeY
            );
            tools::Vector2<float>  propPos(
                tilePos.x + offset.x,
                tilePos.y + offset.y
            );
            _propsObject[i]->setPosition(tools::Vector2<float> (propPos.x, propPos.y));
            _propsObject[i]->drawObject();
            ++placed;
        }
    }
}


/**
 * @brief Draws the entire map.
 *
 * Iterates through all tiles and draws both the tile and its associated props.
 */
void gui::Map::draw() const
{
    if (_tileObject != nullptr) {
        tools::Vector2<float> tileSize = _tileObject->getSize();
        for (int i = 0; i < _map.size(); ++i) {
            for (int j = 0; j < _map[i].size(); ++j) {
                tools::Vector2<float> tilePos(
                    j * tileSize.x,
                    i * tileSize.y
                );
                _tileObject->setPosition(tilePos);
                _tileObject->drawObject();
                drawProps(_map[i][j], tilePos);
            }
        }
    }
}


/**
 * @brief Updates animated props (e.g., idle rotation).
 *
 * @param dt Delta time since last update.
 * @return Always true.
 */
bool gui::Map::update(float dt)
{
    for (int i = 0; i < 7; ++i) {
        if (_propsObject[i]) {
            _propsObject[i]->updateObject(dt);
        }
    }
    return true;
}


/**
 * @brief Attempts to remove a resource from a tile.
 *
 * @param res The resource to remove.
 * @param pos The position of the tile.
 * @return true if the resource was removed, false if invalid position or empty.
 * @throw GameStateError if position is out of bounds.
 */
bool gui::Map::popResource(Tile::Resource res, tools::Vector2<int> pos)
{
    if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height) {
        throw GameStateError("Cannot pop resource: tile position (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") out of map bounds");
    }
    return _map[pos.y][pos.x].popResource(res);
}


/**
 * @brief Adds a resource to a tile.
 *
 * @param res The resource to add.
 * @param pos The position of the tile.
 * @throw GameStateError if position is out of bounds.
 */
void gui::Map::pushResource(Tile::Resource res, tools::Vector2<int> pos)
{
    if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height) {
        throw GameStateError("Cannot push resource: tile position (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") out of map bounds");
    }
    _map[pos.y][pos.x].pushResource(res);
}