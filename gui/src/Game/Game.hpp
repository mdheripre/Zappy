/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Game.hpp
*/

#pragma once
#include "Tools/MessageQueue/MessageQueue.hpp"
#include "Tools/CommandManager/CommandManager.hpp"
#include "Game/GameState/GameState.hpp"

namespace game
{
    class Game
    {
        public:
            Game(std::shared_ptr<tools::MessageQueue> _incoming,
                std::shared_ptr<tools::MessageQueue> _outgoing);
            ~Game();
        private:
            std::shared_ptr<tools::MessageQueue> _incoming;
            std::shared_ptr<tools::MessageQueue> _outgoing;
            void welcomeCm(const std::vector<std::string> &);
            void mszCommand(const std::vector<std::string> &token);
            void bctCommand(const std::vector<std::string> &token);
            void tnaCommand(const std::vector<std::string> &token);
            void printErrorCommand(const std::string &cm, const std::vector<std::string> &token);
            GameState _gm;
            tools::CommandManager _cm;
    };
} // namespace Game
