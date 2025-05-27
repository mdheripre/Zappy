/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Map.hpp
*/

#pragma once
#include "Game/Map/Tile/Tile.hpp"
#include "array"
#include <tuple>
#include <stdexcept>

namespace game
{
    template <int w, int h>
    class Map
    {
    private:
        std::array<std::array<Tile, w>, h> _map;
        std::tuple<int, int> _dim = std::make_tuple(w, h);

    public:
        Map() = default;
        explicit Map(const std::array<std::array<Tile, w>, h> &map) : _map(map) {}
        ~Map() = default;

        const std::array<std::array<Tile, w>, h> &getMap() const { return _map; }
        void setMap(const std::array<std::array<Tile, w>, h> &map) { _map = map; }
        void setTile(const Tile &tile, std::tuple<int, int> position)
        {
            int x;
            int y;
            std::tie(x, y) = position;

            if (x < 0 || x >= w || y < 0 || y >= h)
                throw std::runtime_error("Error: Invalid tile position");

            _map[y][x] = tile;
        }
        const Tile &getTile(std::tuple<int, int> position) const
        {
            int x;
            int y;
            std::tie(x, y) = position;

            if (x < 0 || x >= w || y < 0 || y >= h)
                throw std::runtime_error("Error: Invalid tile position");
            return _map[y][x];
        }
        std::tuple<int, int> getDim() const {return _dim;}
    };
} // namespace game


