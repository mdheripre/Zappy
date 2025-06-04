/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.cpp
*/

#include "Trantorian.hpp"

void gui::Trantorian::draw() const
{
    std::cout << "Draw a Trantorian not implemented" << std::endl;
}

void gui::Trantorian::removeFromInventory(Tile::Resource res)
{
    int index = static_cast<int>(res);

    if (index > _inventory.size() || index < 0)
        throw std::runtime_error("Invalid ressource index " + std::to_string(index));
    _inventory[index]--;
    if (_inventory[index] < 0)
        _inventory[index] = 0;
}

void gui::Trantorian::addToInventory(Tile::Resource res)
{
    int index = static_cast<int>(res);

    if (index > _inventory.size() || index < 0)
        throw std::runtime_error("Invalid ressource index " + std::to_string(index));
    _inventory[index]++;
}

bool gui::Trantorian::update(float)
{
    std::cout << "Update a Trantorian not implemented" << std::endl;
    return false;
}
