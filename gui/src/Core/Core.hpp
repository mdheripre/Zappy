/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Core.hpp
*/

#pragma once
#include "Network/Network.hpp"
#include "Game/Renderer/Raylib/Raylib.hpp"
#include "Game/Renderer/Raylib/RaylibObjectFactory/RaylibObjectFactory.hpp"
#include "Game/Game.hpp"
#include "Error/Error.hpp"
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <regex>

namespace gui
{
    class Core
    {
        public:
            Core(std::vector<std::string> args, char **env);
            ~Core() = default;
            void run();
        private:
            bool _help = false;
            std::shared_ptr<tools::MessageQueue> _incoming;
            std::shared_ptr<tools::MessageQueue> _outgoing;
            std::unique_ptr<net::Network> _net;
            std::unique_ptr<game::Game> _game;
            bool isEnvGraphics(char **env);
    };
} // namespace gui
