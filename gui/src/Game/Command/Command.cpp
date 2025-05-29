/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Tile.hpp
*/

#include "Game/Game.hpp"

void game::Game::welcomeCm(const std::vector<std::string> &token)
{
    if (!token.empty())
        printErrorCommand("WELCOME", token);
    _outgoing->push("GRAPHIC\n");
    _gm.state = GameState::State::CONNECTED;
    std::cout << "Connected" << std::endl;
}

void game::Game::mszCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("msz", token);
    _gm.map = std::make_unique<Map>(std::stoi(token[0]), std::stoi(token[1]));
    std::cout << "Map created" << std::endl;
}

void game::Game::bctCommand(const std::vector<std::string> &token)
{
    if (token.size() != 9)
        printErrorCommand("btc", token);
    std::tuple<int, int> pos(std::stoi(token[0]), std::stoi(token[1]));
    std::array<int, 7> res;
    for (int i = 2; i < 9; i++) {
        res[i - 2] = std::stoi(token[i]); 
    }
    game::Tile newTile(res);
    _gm.map->setTile(newTile, pos);
    std::cout << "Tile set" << std::endl;
}

void game::Game::tnaCommand(const std::vector<std::string> &token)
{
    std::string tokens;

    if (token.empty())
        printErrorCommand("tna", token);
    for (auto &i : token) {
        tokens += i;
        tokens += " ";
    }
    tokens.pop_back();
    if (_gm.teams.find(tokens) == _gm.teams.end()) {
        _gm.teams.emplace(tokens, game::Team(tokens));
        std::cout << "Team added: " << tokens << std::endl;
    }
}

void game::Game::pnwCommand(const std::vector<std::string> &token)
{
    if (token.size() != 6)
        printErrorCommand("pnw", token);

    int id = std::stoi(token[0].substr(1));
    int x = std::stoi(token[1]);
    int y = std::stoi(token[2]);
    int orientation = std::stoi(token[3]);

    game::Player player{id, x, y, orientation};
    _gm.players[id] = player;

    std::cout << "New player #" << id << " spawned at (" << x << ", " << y << ")\n";
}

void game::Game::ppoCommand(const std::vector<std::string> &token)
{
    if (token.size() != 4)
        printErrorCommand("ppo", token);

    int id = std::stoi(token[0].substr(1));
    int x = std::stoi(token[1]);
    int y = std::stoi(token[2]);
    int orientation = std::stoi(token[3]);

    if (_gm.players.find(id) == _gm.players.end())
        return;

    _gm.players[id].x = x;
    _gm.players[id].y = y;
    _gm.players[id].orientation = orientation;

    std::cout << "Player #" << id << " moved to (" << x << ", " << y << ")\n";
}



void game::Game::plvCommand(const std::vector<std::string> &token)
{
    std::cerr << "PLV not implemented" << std::endl;
}

void game::Game::pinCommand(const std::vector<std::string> &token)
{
    std::cerr << "PIN not implemented" << std::endl;
}

void game::Game::plnCommand(const std::vector<std::string> &token)
{
    std::cerr << "PLN not implemented" << std::endl;
}

void game::Game::pexCommand(const std::vector<std::string> &token)
{
    std::cerr << "PEX not implemented" << std::endl;
}

void game::Game::pbcCommand(const std::vector<std::string> &token)
{
    std::cerr << "PBC not implemented" << std::endl;
}

void game::Game::picCommand(const std::vector<std::string> &token)
{
    std::cerr << "PIC not implemented" << std::endl;
}

void game::Game::pieCommand(const std::vector<std::string> &token)
{
    std::cerr << "PIE not implemented" << std::endl;
}

void game::Game::pfkCommand(const std::vector<std::string> &token)
{
    std::cerr << "PFK not implemented" << std::endl;
}

void game::Game::pdrCommand(const std::vector<std::string> &token)
{
    std::cerr << "PDR not implemented" << std::endl;
}

void game::Game::pgtCommand(const std::vector<std::string> &token)
{
    std::cerr << "PGT not implemented" << std::endl;
}

void game::Game::pdiCommand(const std::vector<std::string> &token)
{
    std::cerr << "PDI not implemented" << std::endl;
}

void game::Game::enwCommand(const std::vector<std::string> &token)
{
    std::cerr << "ENW not implemented" << std::endl;
}

void game::Game::eboCommand(const std::vector<std::string> &token)
{
    std::cerr << "EBO not implemented" << std::endl;
}

void game::Game::ediCommand(const std::vector<std::string> &token)
{
    std::cerr << "EDI not implemented" << std::endl;
}

void game::Game::sgtCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("sgt", token);

    try
    {
        _gm.time_unit = std::stof(token[0]);
    }
    catch(const std::exception& e)
    {
        printErrorCommand(e.what(), token);
    }
}

void game::Game::sstCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("sst", token);

    try
    {
        _gm.time_unit = std::stof(token[0]);
    }
    catch(const std::exception& e)
    {
        printErrorCommand(e.what(), token);
    }
}

void game::Game::segCommand(const std::vector<std::string> &token)
{
    if (!token.empty())
        printErrorCommand("seg", token);
    _gm.state = GameState::State::END;
    std::cout << "Game end;" << std::endl;
}

void game::Game::smgCommand(const std::vector<std::string> &token)
{
    std::string tokens;

    for (auto &i : token) {
        tokens += " ";
        tokens += i;
    }
    std::cout << "Message from server:" << tokens << std::endl;
}

void game::Game::sucCommand(const std::vector<std::string> &token)
{
    std::cout << "Server don't know the last command" << std::endl;
}

void game::Game::sbpCommand(const std::vector<std::string> &token)
{
    std::cout << "Server don't accept params of the last command" << std::endl;
}

void game::Game::printErrorCommand(const std::string &cm, const std::vector<std::string> &token)
{
    std::string tokens;

    tokens += cm;
    for (auto &i : token) {
        tokens += " ";
        tokens += i;
    }
    throw std::runtime_error("Error " + tokens);
}
