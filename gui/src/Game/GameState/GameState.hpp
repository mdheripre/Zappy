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
        enum class State {
            NOT_CONNECTED = 0,
            CONNECTED,
            END
        };
        GameState() = default;
        ~GameState() = default;
        State state;
        float time_unit = 0;
        std::unique_ptr<Map> map;
        std::unordered_map<std::string, Team> teams;
    };
} // namespace game
