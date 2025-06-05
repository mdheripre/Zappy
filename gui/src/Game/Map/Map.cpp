/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Map.cpp
*/

#include "Map.hpp"

gui::Map::Map(int width, int height, std::unique_ptr<render::IObject> tileObject, std::array<std::unique_ptr<render::IAnimatedObject>, 7> propsObject)
    : MapState(width, height),
    _width(width),
    _height(height),
    _map(width, std::vector<Tile>(height)),
    _tileObject(std::move(tileObject)),
    _propsObject(std::move(propsObject)) {}

const gui::Tile& gui::MapState::getTile(const tools::Position<int> &pos) const
{
    if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height)
        throw std::runtime_error("Invalid tile position");
    return _map[pos.y][pos.x];
}


void gui::Map::setTile(const Tile &tile, const tools::Position<int> &pos)
{
    if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height)
        throw std::runtime_error("Invalid tile position");
    _map[pos.y][pos.x] = tile;
}

void gui::Map::drawProps(const Tile &tile, const tools::Position3D<float> &tilePos) const
{
    const tools::BoundingBox &bb = _tileObject->getBoundingBox();
    const std::array<int, 7> &ress = tile.getResources();
    tools::Position3D<float> tileSize = bb.getSize();
    float cellSizeX = tileSize.x / 3.0f;
    float cellSizeZ = tileSize.z / 3.0f;
    int placed = 0;

    for (int i = 0; i < 7; ++i) {
        if (_propsObject[i] && ress[i] > 0) {
            int cellX = placed % 3;
            int cellY = placed / 3;
            tools::Position3D<float>  offset = {
                (cellX - 1) * cellSizeX,
                0.0f,
                (cellY - 1) * cellSizeZ
            };
            tools::Position3D<float>  propPos = {
                tilePos.x + offset.x,
                tilePos.y,
                tilePos.z + offset.z
            };
            _propsObject[i]->setPosition({propPos.x, propPos.y, propPos.z});
            _propsObject[i]->drawObject();
            ++placed;
        }
    }
}


void gui::Map::draw() const
{
    if (_tileObject != nullptr) {
        tools::Position3D<float> tileSize = _tileObject->getBoundingBox().getSize();
        for (int i = 0; i < _map.size(); ++i) {
            for (int j = 0; j < _map[i].size(); ++j) {
                tools::Position3D<float> tilePos(
                    j * tileSize.x,
                    0.0f,
                    i * tileSize.z
                );
                _tileObject->setPosition(tilePos);
                _tileObject->drawObject();
                drawProps(_map[i][j], tilePos);
            }
        }
    }
}

bool gui::Map::update(float dt)
{
    for (int i = 0; i < 7; ++i) {
        if (_propsObject[i]) {
            _propsObject[i]->updateObject(dt);
        }
    }
    return true;
}

bool gui::Map::popResource(Tile::Resource res, tools::Position<int> pos)
{
    if (pos.y < _map.size() && pos.x < _map[0].size()) {
        return _map[pos.y][pos.x].popResource(res);
    }
    std::cerr << "Invalid position for tile from popResource" << std::endl;
    return false;
}

void gui::Map::pushResource(Tile::Resource res, tools::Position<int> pos)
{
    if (pos.y < _map.size() && pos.x < _map[0].size()) {
        _map[pos.y][pos.x].pushResource(res);
    }
    std::cerr << "Invalid position for tile from pushResource" << std::endl;
}
