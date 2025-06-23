/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Command.cpp
*/

#include "Game/Game.hpp"

void game::Game::pejCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1) {
        printErrorCommand("pej", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        auto trantorian = it->second;
        trantorian->expulse();
    } else {
        printErrorCommand("Unknown id in smg pej for trantorian", token);
    }
}

void game::Game::pmvCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1) {
        printErrorCommand("pmv", token);
        return;
    }
    int id = std::stoi(token[0].substr(1));

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        auto trantorian = it->second;
        trantorian->setForward(true);
    } else {
        printErrorCommand("Unknown id in smg pmv for trantorian", token);
    }
}