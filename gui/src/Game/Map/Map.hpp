/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Map.hpp
*/

#pragma once
#include "Game/Map/Tile/Tile.hpp"
#include <vector>
#include "Tools/Position/Position.hpp"
#include <stdexcept>

namespace game {

class Map {
private:
    int _width;
    int _height;
    std::vector<std::vector<Tile>> _map;

public:
    Map(int width, int height)
        : _width(width), _height(height), _map(height, std::vector<Tile>(width)) {}

    void setTile(const Tile& tile, const tools::Position<int> &pos) {
        if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height)
            throw std::runtime_error("Invalid tile position");
        _map[pos.y][pos.x] = tile;
    }

    const Tile& getTile(const tools::Position<int> &pos) const {
        if (pos.x < 0 || pos.x >= _width || pos.y < 0 || pos.y >= _height)
            throw std::runtime_error("Invalid tile position");
        return _map[pos.y][pos.x];
    }

    tools::Position<int> getDim() const {
        return { _width, _height };
    }

    const std::vector<std::vector<Tile>>& getMap() const {
        return _map;
    }
};

} // namespace game


