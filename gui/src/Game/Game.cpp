/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Game.cpp
*/

#include "Game.hpp"

game::Game::Game(std::shared_ptr<tools::MessageQueue> incoming,
    std::shared_ptr<tools::MessageQueue> outgoing,
    std::unique_ptr<render::IRenderer> render)
    : _incoming(incoming), _outgoing(outgoing), _renderer(std::move(render))
{
    for (const auto& [name, handler] : commands) {
        _cm.addCommand(name, handler);
    }
    _cam = std::make_shared<render::Camera>();
    _renderer->init("Zappy", 1920, 1080, 60);
    _renderer->setCamera(_cam);
    _renderer->setBindings(bindings);
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

    using clock = std::chrono::high_resolution_clock;
    auto lastTime = clock::now();

    while (!_renderer->isClose()) {
        auto currentTime = clock::now();
        std::chrono::duration<float> elapsed = currentTime - lastTime;
        float dt = elapsed.count();
        lastTime = currentTime;
        try {
            if (!errorCaught) {
                std::string message;
                while (_incoming->tryPop(message))
                    manageCommand(message);
            }
            _renderer->poll();
            _renderer->update(dt);
            if (_gm.map)
                _renderer->render();
        } catch (const std::exception& e) {
            std::cerr << "Game " << e.what() << std::endl;
            errorCaught = true;
            errorMessage = e.what();
            _running = false;
        }
    }
}
