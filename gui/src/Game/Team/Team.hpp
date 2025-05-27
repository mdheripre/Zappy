/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Teams.hpp
*/

#pragma once
#include <string>
#include <vector>
#include "Game/Team/Trantorian/Trantorian.hpp"
#include "Game/Team/Egg/Egg.hpp"


namespace game
{
    class Team
    {
        public:
            Team(std::string name) : _name(name) {};
            ~Team() = default;
        private:
            std::string _name;
            std::vector<Trantorian> _players;
            std::vector<Egg> _eggs;
    };
} // namespace game
