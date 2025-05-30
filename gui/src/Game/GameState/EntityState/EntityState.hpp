/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** EntityState.hpp
*/

#pragma once
#include "Tools/Position/Position.hpp"
#include <memory>
#include "Tools/TeamBranding/TeamBranding.hpp"

namespace game {

    class EntityState {
    protected:
        int _id;
        tools::Position<int> _pos;
        std::string _teamName;
        bool _alive = true;
    
    public:
        EntityState(int id, tools::Position<int> pos, const std::string& teamName)
            : _id(id), _pos(pos), _teamName(teamName) {}
        virtual ~EntityState() = default;
    
        int getId() const { return _id; }
        const tools::Position<int> & getPosition() const { return _pos; }
        const std::string& getTeamName() const { return _teamName; }
        bool isAlive() const { return _alive; }
        virtual void setDead() = 0;
        virtual void setPosition(tools::Position<int> pos) = 0;
    };
} // namespace game
