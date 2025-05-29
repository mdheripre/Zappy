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
#include "Renderer/Renderer3D.hpp"
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
            void pnwCommand(const std::vector<std::string> &token);
            void ppoCommand(const std::vector<std::string> &token);
            void plvCommand(const std::vector<std::string> &token);
            void pinCommand(const std::vector<std::string> &token);
            void plnCommand(const std::vector<std::string> &token);
            void pexCommand(const std::vector<std::string> &token);
            void pbcCommand(const std::vector<std::string> &token);
            void picCommand(const std::vector<std::string> &token);
            void pieCommand(const std::vector<std::string> &token);
            void pfkCommand(const std::vector<std::string> &token);
            void pdrCommand(const std::vector<std::string> &token);
            void pgtCommand(const std::vector<std::string> &token);
            void pdiCommand(const std::vector<std::string> &token);
            void enwCommand(const std::vector<std::string> &token);
            void eboCommand(const std::vector<std::string> &token);
            void ediCommand(const std::vector<std::string> &token);
            void sgtCommand(const std::vector<std::string> &token);
            void sstCommand(const std::vector<std::string> &token);
            void segCommand(const std::vector<std::string> &token);
            void smgCommand(const std::vector<std::string> &token);
            void sucCommand(const std::vector<std::string> &token);
            void sbpCommand(const std::vector<std::string> &token);
            void printErrorCommand(const std::string &cm, const std::vector<std::string> &token);
            void manageCommand(const std::string &command);
            GameState _gm;
            bool _running = true;
            tools::CommandManager _cm;
            std::unique_ptr<gui::Renderer3D> _renderer;
    };
} // namespace Game
