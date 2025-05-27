#include "Game.hpp"
/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Game.cpp
*/

game::Game::Game(std::shared_ptr<tools::MessageQueue> incoming,
    std::shared_ptr<tools::MessageQueue> outgoing) : _incoming(incoming), _outgoing(outgoing)
{

}