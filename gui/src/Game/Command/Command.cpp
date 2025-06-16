/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Command.cpp
*/

#include "Game/Game.hpp"
#include "Tools/Error/Error.hpp"

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

    std::cout << "[WELCOME] --- Connected ---" << std::endl;
    std::cout << "    Send Message : GRAPHIC\\n" << std::endl;
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
    if (token.size() != 2) {
        printErrorCommand("msz", token);
        return;
    }

    tools::Vector2<int> size(std::stoi(token[0]), std::stoi(token[1]));
    std::shared_ptr<gui::Map> map = std::make_shared<gui::Map>(
        size.x,
        size.y,
        _maManager.getTileSprites(_renderer->getFactory())
    );
    _gm.map = map;
    _renderer->pushEntity(map);

    std::cout << "[MSZ] --- Map created ---" << std::endl;
    std::cout << "    Dimensions : " << size.x << " x " << size.y << std::endl;
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
    if (token.size() != 9) {
        printErrorCommand("bct", token);
        return;
    }

    tools::Vector2<int> pos(std::stoi(token[0]), std::stoi(token[1]));
    std::array<int, 7> res;
    for (int i = 2; i < 9; i++) {
        res[i - 2] = std::stoi(token[i]); 
    }

    gui::Tile newTile(res);
    _gm.map->setTile(newTile, pos);

    std::cout << "[BCT] --- Tile updated ---" << std::endl;
    std::cout << "    Position : (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "    Content  : ";
    for (int i = 0; i < 7; i++)
        std::cout << res[i] << (i < 6 ? ", " : "");
    std::cout << std::endl;
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
    if (token.empty()) {
        printErrorCommand("tna", token);
        return;
    }

    std::string tokens;
    for (const auto &i : token) {
        tokens += " ";
        tokens += i;
    }
    std::string teamName = tokens.substr(1);
    tools::TeamBranding tb = _tbManager.getTeamBranding(teamName);

    _gm.teams.insert_or_assign(teamName, tb);
    std::cout << "[TNA] --- Team registered ---" << std::endl;
    std::cout << "    Name : " << teamName << std::endl;
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

    std::cout << "[PNW] --- Trantorian Created ---" << std::endl;
    std::cout << "    ID         : " << id << std::endl;
    std::cout << "    Position   : (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "    Orientation: " << orientation << std::endl;
    std::cout << "    Level      : " << lvl << std::endl;
    std::cout << "    Team       : " << tokens << std::endl;
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
    if (token.size() != 4) {
        printErrorCommand("ppo", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));
    tools::Vector2<int> pos(std::stoi(token[1]), std::stoi(token[2]));
    int orientation = std::stoi(token[3]);

    auto it = _gm.trantorians.find(id);

    if (it == _gm.trantorians.end()) {
        printErrorCommand("Unknown id in ppo for trantorian", token);
        return;
    }

    if (orientation < 1 || orientation > 4) {
        printErrorCommand("Invalid orientation id in ppo for trantorian", token);
        return;
    }

    it->second->setOrientation(static_cast<gui::Trantorian::Orientation>(orientation));
    it->second->setPosition(pos);

    std::cout << "[PPO] --- Trantorian moved ---" << std::endl;
    std::cout << "    ID         : " << id << std::endl;
    std::cout << "    Position   : (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "    Orientation: " << orientation << std::endl;
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
    if (token.size() != 2) {
        printErrorCommand("plv", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));
    int lvl = std::stoi(token[1]);

    if (lvl > 10 || lvl < 0) {
        printErrorCommand("Invalid level in plv", token);
        return;
    }

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        it->second->setLevel(lvl);
        std::cout << "[PLV] --- Trantorian level updated ---" << std::endl;
        std::cout << "    ID    : " << id << std::endl;
        std::cout << "    Level : " << lvl << std::endl;
    } else {
        printErrorCommand("Unknown id in plv for trantorian", token);
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
    if (token.size() != 10) {
        printErrorCommand("pin", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));
    tools::Vector2<int> pos(std::stoi(token[1]), std::stoi(token[2]));
    std::array<int, 7> res;
    for (int i = 3; i < 10; i++)
        res[i - 3] = std::stoi(token[i]);  // fix index: i - 3

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        it->second->setInventory(res);
        it->second->setPosition(pos);

        std::cout << "[PIN] --- Trantorian inventory updated ---" << std::endl;
        std::cout << "    ID       : " << id << std::endl;
        std::cout << "    Position : (" << pos.x << ", " << pos.y << ")" << std::endl;
        std::cout << "    Inventory: ";
        for (int i = 0; i < 7; ++i)
            std::cout << res[i] << (i < 6 ? ", " : "");
        std::cout << std::endl;
    } else {
        printErrorCommand("Unknown id in pin for trantorian", token);
    }
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
    if (token.size() != 1) {
        printErrorCommand("pex", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        auto trantorian = it->second;
        trantorian->expulse();

        for (auto &[otherId, other] : _gm.trantorians) {
            if (other.get() != trantorian.get() && other->getPosition() == trantorian->getPosition()) {
                other->expulseFrom(trantorian->getOrientation(), _gm.map->getDim().x, _gm.map->getDim().y);
            }
        }

        std::cout << "[PEX] --- Expulsion triggered ---" << std::endl;
        std::cout << "    ID        : " << id << std::endl;
        std::cout << "    Position  : (" << trantorian->getPosition().x << ", " << trantorian->getPosition().y << ")" << std::endl;
        std::cout << "    Direction : " << static_cast<int>(trantorian->getOrientation()) << std::endl;
    } else {
        printErrorCommand("Unknown id in pex for trantorian", token);
    }
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
    if (token.size() != 2) {
        printErrorCommand("pbc", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        auto trantorian = it->second;
        trantorian->broadcast(token[1]);

        std::cout << "[PBC] --- Broadcast message ---" << std::endl;
        std::cout << "    ID      : " << id << std::endl;
        std::cout << "    Message : \"" << token[1] << "\"" << std::endl;
    } else {
        printErrorCommand("Unknown id in pbc for trantorian", token);
    }
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
        throw EntityError("Error: Unknown Trantorian ID " + std::to_string(firstId) + " in pic command.");
    }

    tools::TeamBranding tb = _tbManager.getTeamBranding(itInit->second->getTeamName());

    for (size_t i = 3; i < token.size(); ++i) {
        int pid = std::stoi(token[i]);
        playerIds.push_back(pid);

        auto it = _gm.trantorians.find(pid);
        if (it == _gm.trantorians.end()) {
            throw EntityError("Error: Unknown Trantorian ID " + std::to_string(pid) + " in pic command.");
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

    std::cout << "[PIC] --- Incantation started ---" << std::endl;
    std::cout << "    Position : (" << x << ", " << y << ")" << std::endl;
    std::cout << "    Level    : " << level << std::endl;
    std::cout << "    Players  : ";
    for (size_t i = 0; i < playerIds.size(); ++i)
        std::cout << playerIds[i] << (i < playerIds.size() - 1 ? ", " : "");
    std::cout << std::endl;
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
    if (it == _gm.incantations.end()) {
        printErrorCommand("Incantation doesn't exist in pie", token);
        return;
    }

    if (success <= 0) {
        it->second->failed();
        for (auto &i : it->second->getPlayerIds()) {
            auto jt = _gm.trantorians.find(i);
            if (jt != _gm.trantorians.end())
                jt->second->incantationFailed();
        }

        std::cout << "[PIE] --- Incantation result ---" << std::endl;
        std::cout << "    Position : (" << pos.x << ", " << pos.y << ")" << std::endl;
        std::cout << "    Result   : FAILED" << std::endl;
    } else {
        it->second->succeed();
        for (auto &i : it->second->getPlayerIds()) {
            auto jt = _gm.trantorians.find(i);
            if (jt != _gm.trantorians.end()) {
                jt->second->incantationSucced();
                jt->second->setLevel(it->second->getTargetLevel());
            }
        }

        std::cout << "[PIE] --- Incantation result ---" << std::endl;
        std::cout << "    Position : (" << pos.x << ", " << pos.y << ")" << std::endl;
        std::cout << "    Result   : SUCCESS" << std::endl;
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
    if (token.size() != 1) {
        printErrorCommand("pfk", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        it->second->laidAnEgg();

        std::cout << "[PFK] --- Egg laying initiated ---" << std::endl;
        std::cout << "    ID : " << id << std::endl;
    } else {
        printErrorCommand("Unknown id in pfk for trantorian", token);
    }
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
    if (token.size() != 2) {
        printErrorCommand("pdr", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));
    gui::Tile::Resource res = static_cast<gui::Tile::Resource>(std::stoi(token[1]));

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        tools::Vector2<int> pos = it->second->getPosition();

        _gm.map->popResource(res, pos);
        it->second->removeFromInventory(res);

        std::cout << "[PDR] --- Resource dropped ---" << std::endl;
        std::cout << "    ID       : " << id << std::endl;
        std::cout << "    Position : (" << pos.x << ", " << pos.y << ")" << std::endl;
        std::cout << "    Resource : " << std::stoi(token[1]) << std::endl;
    } else {
        printErrorCommand("Unknown id in pdr for trantorian", token);
    }
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
    if (token.size() != 2) {
        printErrorCommand("pgt", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));
    gui::Tile::Resource res = static_cast<gui::Tile::Resource>(std::stoi(token[1]));

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        tools::Vector2<int> pos = it->second->getPosition();

        _gm.map->pushResource(res, pos);
        it->second->addToInventory(res);

        std::cout << "[PGT] --- Resource taken ---" << std::endl;
        std::cout << "    ID       : " << id << std::endl;
        std::cout << "    Position : (" << pos.x << ", " << pos.y << ")" << std::endl;
        std::cout << "    Resource : " << std::stoi(token[1]) << std::endl;
    } else {
        printErrorCommand("Unknown id in pgt for trantorian", token);
    }
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
    if (token.size() != 1) {
        printErrorCommand("pdi", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));

    auto it = _gm.trantorians.find(id);
    if (it != _gm.trantorians.end()) {
        it->second->setDead();
        _gm.trantorians.erase(id);

        std::cout << "[PDI] --- Trantorian removed ---" << std::endl;
        std::cout << "    ID : " << id << std::endl;
    } else {
        printErrorCommand("Unknown id in pdi for trantorian", token);
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

    int eggId = std::stoi(token[0].substr(1));
    int tranId = std::stoi(token[1].substr(1));
    std::string teamName;
    tools::Vector2<int> pos(std::stoi(token[2]), std::stoi(token[3]));

    auto tran = _gm.trantorians.find(tranId);
    if (tran != _gm.trantorians.end()) {
        teamName = tran->second->getTeamName();
    } else if (tranId == -1) {
        teamName = "";
    } else {
        printErrorCommand("Trantorian id doesn't exist in enw", token);
        return;
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

        std::cout << "[ENW] --- Egg laid ---" << std::endl;
        std::cout << "    Egg ID     : " << eggId << std::endl;
        std::cout << "    Trantorian : " << tranId << std::endl;
        std::cout << "    Team       : " << (teamName.empty() ? "(unknown)" : teamName) << std::endl;
        std::cout << "    Position   : (" << pos.x << ", " << pos.y << ")" << std::endl;
    } else {
        printErrorCommand("Egg ID already exists in enw", token);
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

        egg->setDead();
        _gm.eggs.erase(id);

        std::cout << "[EBO] --- Egg hatched ---" << std::endl;
        std::cout << "    Egg ID : " << id << std::endl;
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
    if (token.size() != 1) {
        printErrorCommand("edi", token);
        return;
    }

    int id = std::stoi(token[0].substr(1));

    auto it = _gm.eggs.find(id);
    if (it != _gm.eggs.end()) {
        it->second->setDead();
        _gm.eggs.erase(id);

        std::cout << "[EDI] --- Egg removed ---" << std::endl;
        std::cout << "    Egg ID : " << id << std::endl;
    } else {
        printErrorCommand("Unknown id in edi for egg", token);
    }
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
    if (token.size() != 1) {
        printErrorCommand("sgt", token);
        return;
    }

    _gm.time_unit = std::stof(token[0]);

    std::cout << "[SGT] --- Time unit updated ---" << std::endl;
    std::cout << "    New time unit : " << _gm.time_unit << std::endl;
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
    if (token.size() != 1) {
        printErrorCommand("sst", token);
        return;
    }

    _gm.time_unit = std::stof(token[0]);

    std::cout << "[SST] --- Time unit set by client ---" << std::endl;
    std::cout << "    New time unit : " << _gm.time_unit << std::endl;
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
    if (!token.empty()) {
        printErrorCommand("seg", token);
        return;
    }

    _gm.state = state::GameState::State::END;

    std::cout << "[SEG] --- Game ended ---" << std::endl;
    std::cout << "    New state : END" << std::endl;
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
    std::string message;
    for (const auto& word : token) {
        message += " " + word;
    }

    std::cout << "[SMG] --- Server message ---" << std::endl;
    std::cout << "    Content : " << message << std::endl;
}


/**
 * @brief Handles the SUC command (unknown command).
 */
void game::Game::sucCommand(const std::vector<std::string> &token)
{
    std::cout << "[SUC] --- Unknown command ---" << std::endl;
    std::cout << "    The last command was not recognized by the server." << std::endl;
}


/**
 * @brief Handles the SBP command (bad parameters).
 */
void game::Game::sbpCommand(const std::vector<std::string> &token)
{
    std::cout << "[SBP] --- Invalid parameters ---" << std::endl;
    std::cout << "    The server rejected the parameters of the last command." << std::endl;
}


/**
 * @brief Utility to print and throw command error.
 *
 * @param cm The command name.
 * @param token The full token list received.
 * @throw DataParsingError with constructed error message.
 */
 void game::Game::printErrorCommand(const std::string &cm, const std::vector<std::string> &token)
{
    std::string tokens;

    tokens += cm;
    for (auto &i : token) {
        tokens += " ";
        tokens += i;
    }
    throw DataParsingError("Invalid command format: " + tokens);
}