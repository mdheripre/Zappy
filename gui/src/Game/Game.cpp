/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Game.cpp
*/

#include "Game.hpp"

/**
 * @brief Constructs the Game object.
 *
 * Initializes renderer, object factory, camera and command manager.
 *
 * @param incoming Message queue for incoming messages from server.
 * @param outgoing Message queue for messages to send to server.
 * @param render Renderer used to draw the world.
 * @param objFactory Factory used to generate world objects.
 */
game::Game::Game(std::shared_ptr<tools::MessageQueue> incoming,
    std::shared_ptr<tools::MessageQueue> outgoing,
    std::unique_ptr<render::IRenderer> render)
    : _incoming(incoming), _outgoing(outgoing), _renderer(std::move(render))
{
    for (const auto& [name, handler] : commands) {
        _cm.addCommand(name, handler);
    }
    _renderer->init("Zappy", 1920, 1080, 60);
    _renderer->setBindings(bindings);
}

/**
 * @brief Processes a single server command.
 *
 * Tokenizes the string and delegates handling to the CommandManager.
 *
 * @param command Raw command string.
 * @throw std::runtime_error if command is unknown.
 */
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

/**
 * @brief Main game loop.
 *
 * Continuously updates the renderer, processes incoming commands,
 * and handles errors. Runs until the renderer is closed.
 */
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
