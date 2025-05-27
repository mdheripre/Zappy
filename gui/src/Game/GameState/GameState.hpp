/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** GameState.hpp
*/

#pragma once
#include "Game/Map/Map.hpp"
#include "Game/Team/Team.hpp"
#include <memory>
#include <unordered_map>

namespace game
{
    class GameState
    {
    public:
        GameState() = default;
        ~GameState() = default;
        bool start = false;
        bool connected = false;
        std::unique_ptr<Map> map;
        std::unordered_map<std::string, Team> teams;
    };
} // namespace game
