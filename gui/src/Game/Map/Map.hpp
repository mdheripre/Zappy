/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Map.hpp
*/

#pragma once
#include "Game/Map/Tile/Tile.hpp"
#include <vector>
#include <tuple>
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

    void setTile(const Tile& tile, std::tuple<int, int> pos) {
        int x, y;
        std::tie(x, y) = pos;
        if (x < 0 || x >= _width || y < 0 || y >= _height)
            throw std::runtime_error("Invalid tile position");
        _map[y][x] = tile;
    }

    const Tile& getTile(std::tuple<int, int> pos) const {
        int x, y;
        std::tie(x, y) = pos;
        if (x < 0 || x >= _width || y < 0 || y >= _height)
            throw std::runtime_error("Invalid tile position");
        return _map[y][x];
    }

    std::tuple<int, int> getDim() const {
        return { _width, _height };
    }

    const std::vector<std::vector<Tile>>& getMap() const {
        return _map;
    }
};

} // namespace game


