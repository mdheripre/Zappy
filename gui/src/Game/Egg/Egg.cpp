/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#include "Egg.hpp"

bool gui::Egg::update(float)
{
    std::cout << "Update an egg not implemented" << std::endl;
    return false;
}

void gui::Egg::draw() const
{
    std::cout << "Draw an egg not implemented" << std::endl;
}

void gui::Egg::setPosition(tools::Position<int> pos)
{
    _pos = pos;
}

void gui::Egg::setDead() {
    _alive = false; 
}
