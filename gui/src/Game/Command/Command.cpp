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
    _gm.connected = true;
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
