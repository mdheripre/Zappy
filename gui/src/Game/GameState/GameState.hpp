/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** GameState.hpp
*/

#pragma once
#include "Game/Map/Map.hpp"
#include "Game/Trantorian/Trantorian.hpp"
#include "Game/Incantation/Incantation.hpp"
#include "Game/Egg/Egg.hpp"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include "Tools/TeamBranding/TeamBranding.hpp"

namespace state
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
        int time_unit = 0;
        std::shared_ptr<gui::MapState> map;
        std::map<std::string, tools::TeamBranding> teams;
        std::unordered_map<int, std::shared_ptr<gui::TrantorianState>> trantorians;
        std::unordered_map<int, std::shared_ptr<EntityState>> eggs;
        std::unordered_map<tools::Vector2<int>, std::shared_ptr<gui::IncantationState>> incantations;
    };
}
