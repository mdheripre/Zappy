/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Game.cpp
*/

#include "Game.hpp"

game::Game::Game(std::shared_ptr<tools::MessageQueue> incoming,
    std::shared_ptr<tools::MessageQueue> outgoing)
    : _incoming(incoming), _outgoing(outgoing)
{
    for (const auto& [name, handler] : commands) {
        _cm.addCommand(name, handler);
    }
    _renderer = std::make_unique<gui::Renderer3D>();
    _renderer->init();
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
    bool errorCaught = false;
    std::string errorMessage;

    while (!_renderer->shouldClose()) {
        try {
            if (!errorCaught) {
                std::string message;
                while (_incoming->tryPop(message))
                    manageCommand(message);
            }
            _renderer->update();
            if (_gm.map)
                _renderer->render(*_gm.map, _gm.players);
        } catch (const std::exception& e) {
            std::cerr << "Game " << e.what() << std::endl;
            errorCaught = true;
            errorMessage = e.what();
            _running = false;
        }
    }
}