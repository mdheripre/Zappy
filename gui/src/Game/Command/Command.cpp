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
    tools::Position<int> pos(std::stoi(token[0]), std::stoi(token[1]));
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
    if (token.empty())
        return printErrorCommand("tna", token);

    std::string teamName = token[0];

    if (_gm.teams.insert(teamName).second) {
        std::cout << "Team added: " << teamName << std::endl;
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
    if (token.size() != 2)
        printErrorCommand("pdi", token);

    int id = std::stoi(token[0]);
    int lvl = std::stoi(token[1]);

    if (lvl > 10 || lvl < 0)
        printErrorCommand("Invalid level in plv ", token);
    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->setLevel(lvl);
    } else {
        printErrorCommand("Unknown id in pdi for trantorian ", token);
    }
}

void game::Game::pinCommand(const std::vector<std::string> &token)
{
    if (token.size() != 10)
        printErrorCommand("pin", token);
    int id = std::stoi(token[0]);
    tools::Position<int> pos(std::stoi(token[1]), std::stoi(token[2]));
    std::array<int, 7> res;

    for (int i = 3; i < 10; i++)
        res[i - 2] = std::stoi(token[i]); 

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->setInventory(res);
        it->setPosition(pos);
    } else {
        printErrorCommand("Unknown id in pdi for trantorian ", token);
    }
    std::cout << "Inventory's Player " << id << " set" << std::endl;
}

void game::Game::pexCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("pdi", token);
    int id = std::stoi(token[0]);

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->expulse();
    } else {
        printErrorCommand("Unknown id in pdi for trantorian ", token);
    }
    std::cout << "Trantorian " << id << " expulse" << std::endl;
}

void game::Game::pbcCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("pbc", token);
    int id = std::stoi(token[0]);

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->broadcast(token[1]);
    } else {
        printErrorCommand("Unknown id in pbc for trantorian ", token);
    }
    std::cout << "Trantorian " << id << "broadcast: " <<token[1] << std::endl;
}

void game::Game::picCommand(const std::vector<std::string> &token)
{
    if (token.size() < 4) {
        printErrorCommand("pic", token);
        return;
    }

    int level = std::stoi(token[2]);
    tools::Position<int> pos(std::stoi(token[0]), std::stoi(token[1]));
    std::vector<int> playerIds;

    for (size_t i = 3; i < token.size(); i++)
        playerIds.push_back(std::stoi(token[i]));
    auto incantation = std::make_shared<game::Incantation>(pos, level, playerIds);

    std::shared_ptr<IRenderEntity> renderPtr = incantation;
    _renderer->pushEntity(renderPtr);
    _gm.incantations[pos] = incantation;
    std::cout << "Incantation started at (" << std::stoi(token[0]) << ", " << std::stoi(token[1]) << ") for level " << level << std::endl;
}


void game::Game::pieCommand(const std::vector<std::string> &token)
{
    if (token.size() != 3) {
        printErrorCommand("pie", token);
        return;
    }

    tools::Position<int> pos(std::stoi(token[0]), std::stoi(token[1]));
    int success = std::stoi(token[2]);
    auto it = _gm.incantations.find(pos);

    if (it == _gm.incantations.end())
        printErrorCommand("Incantation doesn't exist in pie", token);

    if (success <= 0) {
        it->second->failed();
        for (auto &i : it->second->getPlayerIds()) {
            auto jt = _gm.trantorians.find(i);
            if (jt != _gm.trantorians.end())
                jt->second->incantationFailed();
        }
        std::cout << "Incantation failed" << std::endl;
    } else {
        it->second->succeed();
        for (auto &i : it->second->getPlayerIds()) {
            auto jt = _gm.trantorians.find(i);
            if (jt != _gm.trantorians.end()) {
                jt->second->incantationSucced();
                jt->second->setLevel(it->second->getTargetLevel());
            }
        }
        std::cout << "Incantation succeeded" << std::endl;
    }
    _gm.incantations.erase(pos);
}


void game::Game::pfkCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("pfk", token);
    int id = std::stoi(token[0]);

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->laidAnEgg();
    } else {
        printErrorCommand("Unknown id in pfk for trantorian ", token);
    }
    std::cout << "Trantorian" << id << "laid an egg" << std::endl;
}

void game::Game::pdrCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("pdr", token);
    int id = std::stoi(token[0]);
    Tile::Resource res = static_cast<Tile::Resource>(std::stoi(token[1]));

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->removeFromInventory(res);
    } else {
        printErrorCommand("Unknown id in pdr for trantorian ", token);
    }
    std::cout << "Trantorian " << id << " droped " << std::stoi(token[1]) << std::endl;
}

void game::Game::pgtCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("pgt", token);
    int id = std::stoi(token[0]);
    Tile::Resource res = static_cast<Tile::Resource>(std::stoi(token[1]));

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->addToInventory(res);
    } else {
        printErrorCommand("Unknown id in pgt for trantorian ", token);
    }
    std::cout << "Trantorian " << id << " take " << std::stoi(token[1]) << std::endl;
}

void game::Game::pdiCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("pdi", token);
    int id = std::stoi(token[0]);

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->setDead();
        _gm.trantorians.erase(id);
    } else {
        printErrorCommand("Unknown id in pdi for trantorian ", token);
    }
}

void game::Game::enwCommand(const std::vector<std::string> &token)
{
    if (token.size() != 4) {
        printErrorCommand("enw", token);
        return;
    }

    int eggId = std::stoi(token[0]);
    int tranId = std::stoi(token[1]);
    std::string teamName;
    tools::Position<int> pos(std::stoi (token[2]), std::stoi(token[3]));

    auto tran = _gm.trantorians.find(tranId);
    if (tran != _gm.trantorians.end()) {
        teamName = tran->second->getTeamName();
    } else {
        printErrorCommand("Trantorian id don't exist in enw ", token);
    }
    if (_gm.eggs.find(eggId) == _gm.eggs.end()) {
        //TODO after render implementation
        /*tools::TeamBranding tb = _tbManager.getTeamBranding(teamName)*/;
        auto egg = std::make_shared<Egg>(
            eggId,
            pos,
            teamName
        );
        std::shared_ptr<EntityState> eggState = egg;
        std::shared_ptr<IRenderEntity> eggRender = egg;

        _renderer->pushEntity(eggRender);
        _gm.eggs[egg->getId()] = eggState;
        std::cout << "Egg " << eggId << " was laid by a player." << std::endl;
    } else {
        printErrorCommand("Id already exist in enw for egg", token);
    }
}

void game::Game::eboCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1) {
        printErrorCommand("ebo", token);
        return;
    }

    int id = std::stoi(token[0]);

    auto it = _gm.eggs.find(id);
    if (it != _gm.eggs.end()) {
        const auto& egg = it->second;

        auto trantorian = std::make_shared<Trantorian>(
            egg->getId(), 
            egg->getPosition(), 
            egg->getTeamName()
        );

        std::shared_ptr<TrantorianState> tranState = trantorian;
        std::shared_ptr<IRenderEntity> tranRender = trantorian;

        _renderer->pushEntity(tranRender);
        _gm.trantorians[egg->getId()] = tranState;

        egg->setDead();
        _gm.eggs.erase(id);

        std::cout << "Egg " << id << " hatched into a Trantorian." << std::endl;
    } else {
        printErrorCommand("Unknown id in ebo for egg", token);
    }
}


void game::Game::ediCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("edi", token);
    int id = std::stoi(token[0]);

    if (_gm.eggs.find(id) != _gm.eggs.end()) {
        auto it = _gm.eggs.at(id);
        it->setDead();
        _gm.eggs.erase(id);
    } else {
        printErrorCommand("Unknown id in edi for egg ", token);
    }
    std::cout << "Egg " << id << " died." << std::endl;
}

void game::Game::sgtCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("sgt", token);

    _gm.time_unit = std::stof(token[0]);
    std::cout << "Time unit has been change to " << _gm.time_unit << std::endl;
}

void game::Game::sstCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("sst", token);

    _gm.time_unit = std::stof(token[0]);
    std::cout << "Time unit has been change to " << _gm.time_unit << std::endl;
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
