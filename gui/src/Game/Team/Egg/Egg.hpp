/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#pragma once
#include "Game/Team/Trantorian/Trantorian.hpp"
#include <vector>
#include <string>
#include <tuple>

namespace game {

    class Egg {
    private:
        int _id;
        int _parentId;
        std::string _teamName;
        std::tuple<int, int> _position;
        bool _alive = true;
    
    public:
        Egg(int id, int parentId, const std::string& team, std::tuple<int, int> pos)
            : _id(id), _parentId(parentId), _teamName(team), _position(pos) {}
    
        int getId() const { return _id; }
        int getParentId() const { return _parentId; }
        const std::string& getTeam() const { return _teamName; }
        std::tuple<int, int> getPosition() const { return _position; }
        bool isAlive() const { return _alive; }
        void setDead() { _alive = false; }
};
} // namespace game
