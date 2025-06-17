/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** EntityState.hpp
*/

#pragma once
#include "Tools/Vector/Vector.hpp"
#include <memory>
#include "Tools/TeamBranding/TeamBranding.hpp"

namespace state {

    class EntityState {
    protected:
        int _id;
        tools::Vector2<int> _pos;
        std::string _teamName;
        bool _alive = true;
    
    public:
        EntityState(int id, tools::Vector2<int> pos, const std::string& teamName)
            : _id(id), _pos(pos), _teamName(teamName) {}
        virtual ~EntityState() = default;
    
        int getId() const { return _id; }
        const tools::Vector2<int> & getPosition() const { return _pos; }
        const std::string& getTeamName() const { return _teamName; }
        bool isAlive() const { return _alive; }
        virtual void setDead() = 0;
        virtual void setPosition(tools::Vector2<int> pos) = 0;
    };
} // namespace game
