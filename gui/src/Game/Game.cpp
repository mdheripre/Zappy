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
    _cm.addCommand("WELCOME", std::bind(&Game::welcomeCm, this, std::placeholders::_1));
    _cm.addCommand("msz", std::bind(&Game::mszCommand, this, std::placeholders::_1));
    _cm.addCommand("tna", std::bind(&Game::tnaCommand, this, std::placeholders::_1));
    _cm.addCommand("bct", std::bind(&Game::bctCommand, this, std::placeholders::_1));
    _cm.addCommand("pnw", std::bind(&Game::pnwCommand, this, std::placeholders::_1));
    _cm.addCommand("ppo", std::bind(&Game::ppoCommand, this, std::placeholders::_1));
    _cm.addCommand("plv", std::bind(&Game::plvCommand, this, std::placeholders::_1));
    _cm.addCommand("pin", std::bind(&Game::pinCommand, this, std::placeholders::_1));
    _cm.addCommand("pex", std::bind(&Game::pexCommand, this, std::placeholders::_1));
    _cm.addCommand("pbc", std::bind(&Game::pbcCommand, this, std::placeholders::_1));
    _cm.addCommand("pic", std::bind(&Game::picCommand, this, std::placeholders::_1));
    _cm.addCommand("pie", std::bind(&Game::pieCommand, this, std::placeholders::_1));
    _cm.addCommand("pfk", std::bind(&Game::pfkCommand, this, std::placeholders::_1));
    _cm.addCommand("pdr", std::bind(&Game::pdrCommand, this, std::placeholders::_1));
    _cm.addCommand("pgt", std::bind(&Game::pgtCommand, this, std::placeholders::_1));
    _cm.addCommand("pdi", std::bind(&Game::pdiCommand, this, std::placeholders::_1));
    _cm.addCommand("enw", std::bind(&Game::enwCommand, this, std::placeholders::_1));
    _cm.addCommand("ebo", std::bind(&Game::eboCommand, this, std::placeholders::_1));
    _cm.addCommand("edi", std::bind(&Game::ediCommand, this, std::placeholders::_1));
    _cm.addCommand("sgt", std::bind(&Game::sgtCommand, this, std::placeholders::_1));
    _cm.addCommand("sst", std::bind(&Game::sstCommand, this, std::placeholders::_1));
    _cm.addCommand("seg", std::bind(&Game::segCommand, this, std::placeholders::_1));
    _cm.addCommand("smg", std::bind(&Game::smgCommand, this, std::placeholders::_1));
    _cm.addCommand("suc", std::bind(&Game::sucCommand, this, std::placeholders::_1));
    _cm.addCommand("sbp", std::bind(&Game::sbpCommand, this, std::placeholders::_1));
    _cm.addCommand("pdr", std::bind(&Game::pdrCommand, this, std::placeholders::_1));
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