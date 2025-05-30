/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#include "Egg.hpp"

bool game::Egg::update(float)
{
    std::cout << "Update an egg not implemented" << std::endl;
    return false;
}

void game::Egg::draw() const
{
    std::cout << "Draw an egg not implemented" << std::endl;
}

void game::Egg::setPosition(tools::Position<int> pos)
{
    _pos = pos;
}

void game::Egg::setDead() {
    _alive = false; 
}
