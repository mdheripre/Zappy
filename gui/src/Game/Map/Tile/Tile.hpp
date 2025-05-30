/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Tile.hpp
*/

#pragma once
#include <array>

namespace game
{
    class Tile
    {
    private:
        std::array<int, 7> _resources;
    public:
        enum class Resource {
            FOOD,
            LINEMATE,
            DERAUMERE,
            SIBUR,
            MENDIANE,
            PHIRAS,
            THYSTAME
        };
        Tile() {
            for (auto &i : _resources)
                i = 0;
        };
        Tile(std::array<int, 7> resources) {_resources = resources;};
        ~Tile() = default;
        const std::array<int, 7> &getResources() const {return _resources;};
        void setResources(std::array<int, 7> resources) {_resources = resources;};
    };
} // namespace game
