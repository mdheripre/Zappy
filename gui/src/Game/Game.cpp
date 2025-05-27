#include "Game.hpp"
/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Game.cpp
*/

game::Game::Game(std::shared_ptr<tools::MessageQueue> incoming,
    std::shared_ptr<tools::MessageQueue> outgoing) : _incoming(incoming), _outgoing(outgoing)
{
    _cm.addCommand("WELCOME", std::bind(&Game::welcomeCm, this, std::placeholders::_1));
    _cm.addCommand("msz", std::bind(&Game::mszCommand, this, std::placeholders::_1));
    _cm.addCommand("tna", std::bind(&Game::tnaCommand, this, std::placeholders::_1));
    _cm.addCommand("bct", std::bind(&Game::bctCommand, this, std::placeholders::_1));
}

void game::Game::manageCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;

    while (iss >> token)
        tokens.push_back(token);
    if (!_cm.handleCommand(tokens))
        throw std::runtime_error("Error Unknown Command " + command);
}

void game::Game::gameLoop()
{
    while (_running) {
        try {
            std::string allMessage;
            while (true) {
                std::string message;
                if (_incoming->tryPop(message)) {
                    manageCommand(message);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        } catch (const std::exception& e) {
            std::cerr << "Game " << e.what() << std::endl;
            _running = false;
        }
    }
}