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
#include "Game/Renderer/IRenderer.hpp"
#include "Tools/TeamBranding/TeamBrandingManager/TeamBrandingManager.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Tools/MapAssetManager/MapAssetManager.hpp"
#include "Tools/Input/Input.hpp"
#include "Tools/Define.hpp"
#include "Game/UI/UI.hpp"
#include "Game/Renderer/Sound/ISound.hpp"
#include <chrono>
#include <sstream>
#include <thread>
#include <vector>
#include <string>
#include <functional>

namespace game
{
    class Game
    {
        public:
            Game(std::shared_ptr<tools::MessageQueue> incoming,
                std::shared_ptr<tools::MessageQueue> outgoing,
                std::unique_ptr<render::IRenderer> render);
            ~Game() = default;
            void gameLoop();
            void stopLoop() {_running = false;};
        private:
            std::shared_ptr<tools::MessageQueue> _incoming;
            std::shared_ptr<tools::MessageQueue> _outgoing;
            state::GameState _gm;
            bool _running = true;
            tools::CommandManager _cm;
            std::unique_ptr<render::IRenderer> _renderer;
            std::shared_ptr<gui::UI> _ui;
            tools::TeamBrandingManager _tbManager;
            tools::MapAssetManager _maManager;
            std::unique_ptr<render::ISound> _mainSound;

            void welcomeCm(const std::vector<std::string> &token);
            void mszCommand(const std::vector<std::string> &token);
            void bctCommand(const std::vector<std::string> &token);
            void tnaCommand(const std::vector<std::string> &token);
            void pnwCommand(const std::vector<std::string> &token);
            void ppoCommand(const std::vector<std::string> &token);
            void plvCommand(const std::vector<std::string> &token);
            void pinCommand(const std::vector<std::string> &token);
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
            void pejCommand(const std::vector<std::string> &token);
            void pmvCommand(const std::vector<std::string> &token);
            void printErrorCommand(const std::string &cm, const std::vector<std::string> &token);
            void manageCommand(const std::string &command);
            using CommandHandler = std::function<void(const std::vector<std::string>&)>;
            const std::vector<std::pair<std::string, CommandHandler>> commands = {
                {"WELCOME", std::bind(&Game::welcomeCm, this, std::placeholders::_1)},
                {"msz",     std::bind(&Game::mszCommand, this, std::placeholders::_1)},
                {"tna",     std::bind(&Game::tnaCommand, this, std::placeholders::_1)},
                {"bct",     std::bind(&Game::bctCommand, this, std::placeholders::_1)},
                {"pnw",     std::bind(&Game::pnwCommand, this, std::placeholders::_1)},
                {"ppo",     std::bind(&Game::ppoCommand, this, std::placeholders::_1)},
                {"plv",     std::bind(&Game::plvCommand, this, std::placeholders::_1)},
                {"pin",     std::bind(&Game::pinCommand, this, std::placeholders::_1)},
                {"pex",     std::bind(&Game::pexCommand, this, std::placeholders::_1)},
                {"pbc",     std::bind(&Game::pbcCommand, this, std::placeholders::_1)},
                {"pic",     std::bind(&Game::picCommand, this, std::placeholders::_1)},
                {"pie",     std::bind(&Game::pieCommand, this, std::placeholders::_1)},
                {"pfk",     std::bind(&Game::pfkCommand, this, std::placeholders::_1)},
                {"pdr",     std::bind(&Game::pdrCommand, this, std::placeholders::_1)},
                {"pgt",     std::bind(&Game::pgtCommand, this, std::placeholders::_1)},
                {"pdi",     std::bind(&Game::pdiCommand, this, std::placeholders::_1)},
                {"enw",     std::bind(&Game::enwCommand, this, std::placeholders::_1)},
                {"ebo",     std::bind(&Game::eboCommand, this, std::placeholders::_1)},
                {"edi",     std::bind(&Game::ediCommand, this, std::placeholders::_1)},
                {"sgt",     std::bind(&Game::sgtCommand, this, std::placeholders::_1)},
                {"sst",     std::bind(&Game::sstCommand, this, std::placeholders::_1)},
                {"seg",     std::bind(&Game::segCommand, this, std::placeholders::_1)},
                {"smg",     std::bind(&Game::smgCommand, this, std::placeholders::_1)},
                {"suc",     std::bind(&Game::sucCommand, this, std::placeholders::_1)},
                {"sbp",     std::bind(&Game::sbpCommand, this, std::placeholders::_1)}
            };
            const std::vector<std::pair<std::string, CommandHandler>> _specialCommands = {
                {"pej", std::bind(&Game::pejCommand, this, std::placeholders::_1)},
                {"pmv", std::bind(&Game::pmvCommand, this, std::placeholders::_1)}
            };
            const std::unordered_map<tools::KeyCode, std::function<void()>> bindings = {
                { tools::KeyCode::Right, [this]() { _renderer->setPositionView(-20, 0); }},
                { tools::KeyCode::Left,  [this]() { _renderer->setPositionView(20, 0); }},
                { tools::KeyCode::Up,    [this]() { _renderer->setPositionView(0, 20); }},
                { tools::KeyCode::Down,  [this]() { _renderer->setPositionView(0, -20); }},
                { tools::KeyCode::W,     [this]() { _renderer->setZoomView(1.1f);}},
                { tools::KeyCode::S,     [this]() { _renderer->setZoomView(0.9f);}},
                { tools::KeyCode::R,      [this]() { _renderer->resetZoomView(); }},
                { tools::KeyCode::P,     [this]() { _outgoing->push("sst " + std::to_string(_gm.time_unit + 1) + "\n");}},
                { tools::KeyCode::M,     [this]() { _outgoing->push("sst " + std::to_string(_gm.time_unit - 1) + "\n");}},
                { tools::KeyCode::A,     [this]() { _ui->changeBroadcastVisibility();}},
                { tools::KeyCode::Z,     [this]() { _ui->changeTeamVisibility();}},
                { tools::KeyCode::E,     [this]() { _ui->changeEventVisibility();}},
                { tools::KeyCode::Y,     [this]() { _ui->changePlayerVisibility();}},
                { tools::KeyCode::T,     [this]() { _ui->changeTimeVisibility();}},
                { tools::KeyCode::Q,     [this]() { _mainSound->changeState();}},
            };
    };
} // namespace Game
