/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Core.cpp
*/

#include "Core.hpp"

/**
 * @brief Constructs the GUI Core object.
 *
 * Parses command-line arguments, initializes network and game components,
 * and validates the graphical environment. Throws on invalid or missing arguments.
 *
 * @param args Command-line arguments.
 * @param env Environment variables.
 * @throw std::runtime_error if invalid arguments or no graphical environment.
 */

gui::Core::Core(std::vector<std::string> args, char **env)
{
    int port = 0;
    std::string addr;

    for (size_t i = 0; i < args.size(); i++) {
        if (args[i] == "-help") {
            _help = true;
        } else if (args[i] == "-p" && i + 1 < args.size()) {
            port = std::stoi(args[i + 1]);
            i++;
        } else if (args[i] == "-h" && i + 1 < args.size()) {
            addr = args[i + 1];
            i++;
        } else {
            break;
        }
    }
    if ((port == 0 || addr.empty()) && !_help)
        throw std::runtime_error("USAGE: ./zappy_gui -p port -h machine");
    if (_help)
        return;
    if (!isEnvGraphics(env))
        throw std::runtime_error("Error: There is no graphical environment, sorry :)");
    _incoming = std::make_shared<tools::MessageQueue>();
    _outgoing = std::make_shared<tools::MessageQueue>();
    _net = std::make_unique<net::Network>(_incoming, _outgoing, port, addr);
    _game = std::make_unique<game::Game>(_incoming,
        _outgoing,
        std::make_unique<sfml::SFMLRenderer>());
}

/**
 * @brief Checks if a graphical environment is available.
 *
 * Verifies the presence of a valid DISPLAY variable in the environment.
 *
 * @param env The environment variables array.
 * @return true if a graphical environment is detected, false otherwise.
 */

bool gui::Core::isEnvGraphics(char **env)
{
    std::regex displayRegex(R"(^(:[0-9]+(.[0-9]+)?)$)");
    std::string lines;
    std::string value;

    for (int i = 0; env[i]; i++) {
        lines = env[i];
        if (lines.rfind("DISPLAY=", 0) == 0 && std::regex_match(lines.substr(8), displayRegex))
            return true;
    }
    return false;
}

/**
 * @brief Runs the GUI core loop.
 *
 * Starts the networking thread and executes the main game loop.
 * Also handles the `-help` case and shutdown.
 */

void gui::Core::run()
{
    if (_help) {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        return;
    }
    std::thread netThread(&net::Network::startLoop, _net.get());
    try
    {
        _game->gameLoop();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    _net->stopLoop();
    netThread.join();
}
