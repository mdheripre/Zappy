/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "Tools/Error/Error.hpp"

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
    for (const auto& [name, handler] : _specialCommands) {
        _cm.addCommand(name, handler);
    }
    _renderer->init("Zappy", WIDTH_WINDOW, HEIGHT_WINDOW, 60);
    _renderer->setBindings(bindings);
    _ui = std::make_shared<gui::UI>(_renderer->getFactory());
    _renderer->setUI(_ui);
    _mainSound = _renderer->getFactory().createSound("gui/assets/Sound/Surf Rider.mp3");
    _mainSound->play(true);
}

/**
 * @brief Processes a single server command.
 *
 * Tokenizes the string and delegates handling to the CommandManager.
 *
 * @param command Raw command string.
 * @throw CommandError if command is unknown.
 */
void game::Game::manageCommand(const std::string &command)
{
    std::istringstream iss(command);
    std::string token;
    std::vector<std::string> tokens;

    while (iss >> token)
        tokens.push_back(token);
    if (!_cm.handleCommand(tokens))
        throw CommandError("Unknown Command: " + command).where("Game::manageCommand");
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
    float acc = 0;

    while (!_renderer->isClose()) {
        auto currentTime = clock::now();
        std::chrono::duration<float> elapsed = currentTime - lastTime;
        float dt = elapsed.count();
        acc += dt * static_cast<float>(_gm.time_unit);
        _ui->updateTimeUnit(_gm.time_unit, acc);
        lastTime = currentTime;
        try {
            if (!errorCaught) {
                std::string message;
                while (_incoming->tryPop(message)) {
                    manageCommand(message);
                }
            }
            _renderer->poll();
            _renderer->update(dt * static_cast<float>(_gm.time_unit));
            _renderer->updateUI(dt);
            if (_gm.map)
                _renderer->render();
        } catch (const Error& e) {
            std::cerr << "Game " << e.what() << std::endl;
            errorCaught = true;
            errorMessage = e.what();
            _running = false;
        } catch (const std::exception& e) {
            std::cerr << "Game (Unexpected Error) " << e.what() << std::endl;
            errorCaught = true;
            errorMessage = e.what();
            _running = false;
        }
    }
}