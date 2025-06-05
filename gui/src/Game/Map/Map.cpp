/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Map.cpp
*/

#include "Map.hpp"

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
