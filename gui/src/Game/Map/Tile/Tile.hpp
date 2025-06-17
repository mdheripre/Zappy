/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Tile.hpp
*/

#pragma once
#include <array>

namespace gui
{
    class Tile
    {
        public:
            enum class Resource {
                FOOD = 0,
                LINEMATE,
                DERAUMERE,
                SIBUR,
                MENDIANE,
                PHIRAS,
                THYSTAME
            };
            Tile();
            Tile(std::array<int, 7> resources) {setResources(resources);};
            ~Tile() = default;
            int getTotal() const {return _total;};
            const std::array<int, 7> &getResources() const {return _resources;};
            bool popResource(Resource res);
            void pushResource(Resource res);
            void setResources(std::array<int, 7> resources);
        private:
            std::array<int, 7> _resources;
            int _total = 0;
    };
} // namespace game
