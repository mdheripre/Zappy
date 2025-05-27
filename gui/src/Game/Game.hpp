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
#include <sstream>
#include <thread>
#include <vector>
#include <string>

namespace game
{
    class Game
    {
        public:
            Game(std::shared_ptr<tools::MessageQueue> _incoming,
                std::shared_ptr<tools::MessageQueue> _outgoing);
            ~Game() = default;
            void gameLoop();
            void stopLoop() {_running = false;};
        private:
            std::shared_ptr<tools::MessageQueue> _incoming;
            std::shared_ptr<tools::MessageQueue> _outgoing;
            void welcomeCm(const std::vector<std::string> &);
            void mszCommand(const std::vector<std::string> &token);
            void bctCommand(const std::vector<std::string> &token);
            void tnaCommand(const std::vector<std::string> &token);
            void printErrorCommand(const std::string &cm, const std::vector<std::string> &token);
            void manageCommand(const std::string &command);
            GameState _gm;
            bool _running = true;
            tools::CommandManager _cm;
    };
} // namespace Game
