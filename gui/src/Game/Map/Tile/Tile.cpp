/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

bool gui::Tile::popResource(Resource res)
{
    int index = static_cast<int>(res);

    if (_resources[index] > 0) {
        _resources[index]--;
        _total--;
        return true;
    }
    return false;
}

void gui::Tile::pushResource(Resource res)
{
    int index = static_cast<int>(res);

    _resources[index]++;
    _total++;
}

void gui::Tile::setResources(std::array<int, 7> resources)
{
    int count = 0;

    for (int i = 0; i < 7; i++)
        count += resources[i];
    _total = count;
    _resources = resources;
}
