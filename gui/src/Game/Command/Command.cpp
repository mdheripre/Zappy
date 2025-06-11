/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Command.cpp
*/

#include "Game/Game.hpp"

/**
 * @brief Handles the WELCOME command from the server.
 *
 * Sends the GRAPHIC identifier and sets the game state to CONNECTED.
 *
 * @param token Unused tokens from the command.
 */
void game::Game::welcomeCm(const std::vector<std::string> &token)
{
    if (!token.empty())
        printErrorCommand("WELCOME", token);
    _outgoing->push("GRAPHIC\n");
    _gm.state = state::GameState::State::CONNECTED;
    std::cout << "Connected" << std::endl;
}

/**
 * @brief Handles the MSZ command (map size).
 *
 * Creates a new map and pushes it to the renderer.
 *
 * @param token Expected format: {width, height}
 */
void game::Game::mszCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("msz", token);
    std::shared_ptr<gui::Map> map = std::make_shared<gui::Map>(
        std::stoi(token[0]),
        std::stoi(token[1])
    );
    _gm.map = map;
    _renderer->pushEntity(map);
    std::cout << "Map created" << std::endl;
}

/**
 * @brief Handles the BCT command (tile content).
 *
 * Sets resources on the given tile position.
 *
 * @param token Expected format: {x, y, q0, q1, ..., q6}
 */
void game::Game::bctCommand(const std::vector<std::string> &token)
{
    if (token.size() != 9)
        printErrorCommand("btc", token);
    tools::Vector2<int> pos(std::stoi(token[0]), std::stoi(token[1]));
    std::array<int, 7> res;
    for (int i = 2; i < 9; i++) {
        res[i - 2] = std::stoi(token[i]); 
    }
    gui::Tile newTile(res);
    _gm.map->setTile(newTile, pos);
    std::cout << "Tile set" << std::endl;
}

/**
 * @brief Handles the TNA command (team names).
 *
 * Adds a team to the internal list if not already present.
 *
 * @param token List of team names.
 */
void game::Game::tnaCommand(const std::vector<std::string> &token)
{
    if (token.empty())
        return printErrorCommand("tna", token);
    
    std::string tokens;

    for (auto &i : token) {
        tokens += " ";
        tokens += i;
    }

    std::string teamName = token[0];

    if (_gm.teams.insert(teamName.substr(1)).second) {
        std::cout << "Team added: " << teamName << std::endl;
    }
}

/**
 * @brief Handles the PNW command (new player).
 *
 * Spawns a new Trantorian with given position, orientation, level, and team.
 *
 * @param token Expected format: {#id, x, y, orientation, level, team_name}
 */
void game::Game::pnwCommand(const std::vector<std::string> &token)
{
    if (token.size() < 6)
        printErrorCommand("pnw", token);

    int id = std::stoi(token[0].substr(1));
    tools::Vector2<int> pos(std::stoi(token[1]), std::stoi(token[2]));
    int orientation = std::stoi(token[3]);
    int lvl = std::stoi(token[4]);
    auto it = _gm.trantorians.find(id);
    const auto& tran = it->second;
    std::string tokens;
    for (int i = 5; i < token.size(); i++) {
        tokens += " ";
        tokens += token[i];
    }
    tools::TeamBranding tb = _tbManager.getTeamBranding(tokens);

    auto trantorian = std::make_shared<gui::Trantorian>(
        id,
        pos,
        tokens,
        static_cast<gui::Trantorian::Orientation>(orientation),
        lvl,
        _renderer->getFactory().createAnimatedSprite(tb.getPlayerAsset())
    );

    std::shared_ptr<gui::TrantorianState> tranState = trantorian;
    std::shared_ptr<render::IRenderEntity> tranRender = trantorian;

    _renderer->pushEntity(tranRender);
    _gm.trantorians[id] = tranState;

    std::cout << "Trantorian " << id << " was created." << std::endl;
}

/**
 * @brief Handles the PPO command (player position).
 *
 * Updates the position and orientation of a player.
 *
 * @param token Expected format: {#id, x, y, orientation}
 */
void game::Game::ppoCommand(const std::vector<std::string> &token)
{
    if (token.size() != 4)
        printErrorCommand("ppo", token);

    int id = std::stoi(token[0].substr(1));
    tools::Vector2<int> pos(std::stoi(token[1]), std::stoi(token[2]));
    int orientation = std::stoi(token[3]);

    auto it = _gm.trantorians.find(id);

    if (it == _gm.trantorians.end())
        printErrorCommand("Unknown id in ppo for trantorian ", token);
    if (orientation < 1 || orientation > 4)
        printErrorCommand("Invalid orientation id in ppo for trantorian", token);
    
    it->second->setOrientation(static_cast<gui::Trantorian::Orientation>(orientation));
    it->second->setPosition(pos);

    std::cout << "Player #" << id << " moved to (" << pos.x << ", " << pos.y << ")\n";
}

/**
 * @brief Handles the PLV command (player level).
 *
 * Updates the level of a player.
 *
 * @param token Expected format: {#id, level}
 */
void game::Game::plvCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("pdi", token);

    int id = std::stoi(token[0].substr(1));
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

/**
 * @brief Handles the PIN command (player inventory).
 *
 * Sets a player's position and inventory content.
 *
 * @param token Expected format: {#id, x, y, q0, ..., q6}
 */
void game::Game::pinCommand(const std::vector<std::string> &token)
{
    if (token.size() != 10)
        printErrorCommand("pin", token);
    int id = std::stoi(token[0].substr(1));
    tools::Vector2<int> pos(std::stoi(token[1]), std::stoi(token[2]));
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

/**
 * @brief Handles the PEX command (expulsion).
 *
 * Expels all players from the same tile as the given Trantorian.
 *
 * @param token Expected format: {#id}
 */
void game::Game::pexCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("pdi", token);
    int id = std::stoi(token[0].substr(1));

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->expulse();
        for (auto &[otherId, other] : _gm.trantorians) {
            if (other.get() != it.get() && other->getPosition() == it->getPosition()) {
                other->expulseFrom(it->getOrientation(), _gm.map->getDim().x, _gm.map->getDim().y);
            }
        }
    } else {
        printErrorCommand("Unknown id in pdi for trantorian ", token);
    }
    std::cout << "Trantorian " << id << " expulse" << std::endl;
}

/**
 * @brief Handles the PBC command (broadcast).
 *
 * Broadcasts a message from a player.
 *
 * @param token Expected format: {#id, message}
 */
void game::Game::pbcCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("pbc", token);
    int id = std::stoi(token[0].substr(1));

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->broadcast(token[1]);
    } else {
        printErrorCommand("Unknown id in pbc for trantorian ", token);
    }
    std::cout << "Trantorian " << id << "broadcast: " <<token[1] << std::endl;
}

/**
 * @brief Handles the PIC command (start incantation).
 *
 * Begins an incantation at a tile for a group of players.
 *
 * @param token Expected format: {x, y, level, #id, #id, ...}
 */
void game::Game::picCommand(const std::vector<std::string> &token)
{
    if (token.size() < 4) {
        printErrorCommand("pic", token);
        return;
    }

    int x = std::stoi(token[0]);
    int y = std::stoi(token[1]);
    int level = std::stoi(token[2]);
    tools::Vector2<int> pos(x, y);

    std::vector<int> playerIds;

    int firstId = std::stoi(token[3]);
    auto itInit = _gm.trantorians.find(firstId);
    if (itInit == _gm.trantorians.end()) {
        throw std::runtime_error("Error: Unknown Trantorian ID " + std::to_string(firstId) + " in pic command.");
    }

    tools::TeamBranding tb = _tbManager.getTeamBranding(itInit->second->getTeamName());

    for (size_t i = 3; i < token.size(); ++i) {
        int pid = std::stoi(token[i]);
        playerIds.push_back(pid);

        auto it = _gm.trantorians.find(pid);
        if (it == _gm.trantorians.end()) {
            throw std::runtime_error("Error: Unknown Trantorian ID " + std::to_string(pid) + " in pic command.");
        }

        it->second->startIncantation();
    }

    auto incantation = std::make_shared<gui::Incantation>(
        pos,
        level,
        playerIds,
        _renderer->getFactory().createAnimatedSprite(tb.getIncantationAsset())
    );

    std::shared_ptr<render::IRenderEntity> renderPtr = incantation;
    _renderer->pushEntity(renderPtr);
    _gm.incantations[pos] = incantation;

    std::cout << "Incantation started at (" << x << ", " << y << ") for level " << level << std::endl;
}

/**
 * @brief Handles the PIE command (end incantation).
 *
 * Marks an incantation as success or failure and updates involved players.
 *
 * @param token Expected format: {x, y, result}
 */
void game::Game::pieCommand(const std::vector<std::string> &token)
{
    if (token.size() != 3) {
        printErrorCommand("pie", token);
        return;
    }

    tools::Vector2<int> pos(std::stoi(token[0]), std::stoi(token[1]));
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

/**
 * @brief Handles the PFK command (egg laid).
 *
 * Marks a Trantorian as having laid an egg.
 *
 * @param token Expected format: {#id}
 */
void game::Game::pfkCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("pfk", token);
    int id = std::stoi(token[0].substr(1));

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->laidAnEgg();
    } else {
        printErrorCommand("Unknown id in pfk for trantorian ", token);
    }
    std::cout << "Trantorian" << id << "laid an egg" << std::endl;
}

/**
 * @brief Handles the PDR command (drop resource).
 *
 * Updates the map and player inventory after a resource is dropped.
 *
 * @param token Expected format: {#id, resource_id}
 */
void game::Game::pdrCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("pdr", token);
    int id = std::stoi(token[0].substr(1));
    gui::Tile::Resource res = static_cast<gui::Tile::Resource>(std::stoi(token[1]));

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        tools::Vector2<int> pos = it->getPosition();

        _gm.map->popResource(res, pos);
        it->removeFromInventory(res);
    } else {
        printErrorCommand("Unknown id in pdr for trantorian ", token);
    }
    std::cout << "Trantorian " << id << " droped " << std::stoi(token[1]) << std::endl;
}

/**
 * @brief Handles the PGT command (take resource).
 *
 * Updates the map and player inventory after a resource is taken.
 *
 * @param token Expected format: {#id, resource_id}
 */
void game::Game::pgtCommand(const std::vector<std::string> &token)
{
    if (token.size() != 2)
        printErrorCommand("pgt", token);
    int id = std::stoi(token[0].substr(1));
    gui::Tile::Resource res = static_cast<gui::Tile::Resource>(std::stoi(token[1]));

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        tools::Vector2<int> pos = it->getPosition();

        _gm.map->pushResource(res, pos);
        it->addToInventory(res);

    } else {
        printErrorCommand("Unknown id in pgt for trantorian ", token);
    }
    std::cout << "Trantorian " << id << " take " << std::stoi(token[1]) << std::endl;
}

/**
 * @brief Handles the PDI command (player death).
 *
 * Removes the player from the game.
 *
 * @param token Expected format: {#id}
 */
void game::Game::pdiCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("pdi", token);
    int id = std::stoi(token[0].substr(1));

    if (_gm.trantorians.find(id) != _gm.trantorians.end()) {
        auto it = _gm.trantorians.at(id);
        it->setDead();
        _gm.trantorians.erase(id);
    } else {
        printErrorCommand("Unknown id in pdi for trantorian ", token);
    }
}

/**
 * @brief Handles the ENW command (egg laid on map).
 *
 * Creates a new Egg entity on the map.
 *
 * @param token Expected format: {egg_id, trantorian_id, x, y}
 */
void game::Game::enwCommand(const std::vector<std::string> &token)
{
    if (token.size() != 4) {
        printErrorCommand("enw", token);
        return;
    }

    int eggId = std::stoi(token[0]);
    int tranId = std::stoi(token[1]);
    std::string teamName;
    tools::Vector2<int> pos(std::stoi (token[2]), std::stoi(token[3]));

    auto tran = _gm.trantorians.find(tranId);
    if (tran != _gm.trantorians.end()) {
        teamName = tran->second->getTeamName();
    } else {
        printErrorCommand("Trantorian id don't exist in enw ", token);
    }
    if (_gm.eggs.find(eggId) == _gm.eggs.end()) {

        tools::TeamBranding tb = _tbManager.getTeamBranding(teamName);
        auto egg = std::make_shared<gui::Egg>(
            eggId,
            pos,
            teamName,
            _renderer->getFactory().createAnimatedSprite(tb.getEggAsset())
        );
        std::shared_ptr<state::EntityState> eggState = egg;
        std::shared_ptr<render::IRenderEntity> eggRender = egg;

        _renderer->pushEntity(eggRender);
        _gm.eggs[egg->getId()] = eggState;
        std::cout << "Egg " << eggId << " was laid by a player." << std::endl;
    } else {
        printErrorCommand("Id already exist in enw for egg", token);
    }
}

/**
 * @brief Handles the EBO command (egg hatched).
 *
 * Transforms an egg into a Trantorian.
 *
 * @param token Expected format: {#egg_id}
 */
void game::Game::eboCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1) {
        printErrorCommand("ebo", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));

    auto it = _gm.eggs.find(id);
    if (it != _gm.eggs.end()) {
        const auto& egg = it->second;

        tools::TeamBranding tb = _tbManager.getTeamBranding(egg->getTeamName());

        auto trantorian = std::make_shared<gui::Trantorian>(
            egg->getId(), 
            egg->getPosition(), 
            egg->getTeamName(),
            gui::Trantorian::Orientation::NORTH,
            1,
            _renderer->getFactory().createAnimatedSprite(tb.getEggAsset())
        );

        std::shared_ptr<gui::TrantorianState> tranState = trantorian;
        std::shared_ptr<render::IRenderEntity> tranRender = trantorian;

        _renderer->pushEntity(tranRender);
        _gm.trantorians[egg->getId()] = tranState;

        egg->setDead();
        _gm.eggs.erase(id);

        std::cout << "Egg " << id << " hatched into a Trantorian." << std::endl;
    } else {
        printErrorCommand("Unknown id in ebo for egg", token);
    }
}

/**
 * @brief Handles the EDI command (egg dies).
 *
 * Deletes an egg from the map.
 *
 * @param token Expected format: {#egg_id}
 */
void game::Game::ediCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("edi", token);
    int id = std::stoi(token[0].substr(1));

    if (_gm.eggs.find(id) != _gm.eggs.end()) {
        auto it = _gm.eggs.at(id);
        it->setDead();
        _gm.eggs.erase(id);
    } else {
        printErrorCommand("Unknown id in edi for egg ", token);
    }
    std::cout << "Egg " << id << " died." << std::endl;
}

/**
 * @brief Handles the SGT command (get time unit).
 *
 * Updates the game time unit.
 *
 * @param token Expected format: {time_unit}
 */
void game::Game::sgtCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("sgt", token);

    _gm.time_unit = std::stof(token[0]);
    std::cout << "Time unit has been change to " << _gm.time_unit << std::endl;
}

/**
 * @brief Handles the SST command (set time unit).
 *
 * Updates the game time unit.
 *
 * @param token Expected format: {time_unit}
 */
void game::Game::sstCommand(const std::vector<std::string> &token)
{
    if (token.size() != 1)
        printErrorCommand("sst", token);

    _gm.time_unit = std::stof(token[0]);
    std::cout << "Time unit has been change to " << _gm.time_unit << std::endl;
}

/**
 * @brief Handles the SEG command (game end).
 *
 * Marks the game state as ended.
 *
 * @param token Expected to be empty.
 */
void game::Game::segCommand(const std::vector<std::string> &token)
{
    if (!token.empty())
        printErrorCommand("seg", token);
    _gm.state = state::GameState::State::END;
    std::cout << "Game end;" << std::endl;
}

/**
 * @brief Handles the SMG command (server message).
 *
 * Displays a server-side message.
 *
 * @param token The message content.
 */
void game::Game::smgCommand(const std::vector<std::string> &token)
{
    std::string tokens;

    for (auto &i : token) {
        tokens += " ";
        tokens += i;
    }
    std::cout << "Message from server:" << tokens << std::endl;
}

/**
 * @brief Handles the SUC command (unknown command).
 */
void game::Game::sucCommand(const std::vector<std::string> &token)
{
    std::cout << "Server don't know the last command" << std::endl;
}

/**
 * @brief Handles the SBP command (bad parameters).
 */
void game::Game::sbpCommand(const std::vector<std::string> &token)
{
    std::cout << "Server don't accept params of the last command" << std::endl;
}

/**
 * @brief Utility to print and throw command error.
 *
 * @param cm The command name.
 * @param token The full token list received.
 * @throw std::runtime_error with constructed error message.
 */
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
