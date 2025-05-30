// GameState.hpp

#pragma once
#include "Game/Map/Map.hpp"
#include "Game/Trantorian/Trantorian.hpp"
#include "Game/Incantation/Incantation.hpp"
#include "Game/Egg/Egg.hpp"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace game
{
    struct Player {
        int id;
        int x;
        int y;
        int orientation;
    };

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
        std::unordered_set<std::string> teams;
        std::unordered_map<int, Player> players;
        std::unordered_map<int, std::shared_ptr<TrantorianState>> trantorians;
        std::unordered_map<int, std::shared_ptr<EntityState>> eggs;
        std::unordered_map<tools::Position<int>, std::shared_ptr<IncantationState>> incantations;
    };
}
