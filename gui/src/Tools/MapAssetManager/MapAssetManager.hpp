/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** MapAssetManager.hpp
*/

#pragma once
#include <unordered_map>
#include <string>
#include "Tools/AssetDefinition/AssetDefinition.hpp"
#include "Game/Renderer/Object/IStaticSprite.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Game/Map/Map.hpp"
#include "Tools/Define.hpp"

namespace tools
{
    class MapAssetManager
    {
    public:
        MapAssetManager();
        const AssetDefinition& getTile(gui::Map::MapTileType type) const;
        std::unordered_map<gui::Map::MapTileType,  std::unique_ptr<render::IStaticSprite>>
            getTileSprites(render::IObjectFactory& factory) const;
        std::array<std::unique_ptr<render::IAnimatedSprite>, 7>
            getProps(render::IObjectFactory& factory) const;
            
    private:
        std::unordered_map<gui::Map::MapTileType, AssetDefinition> _tiles;
        const std::string _basePathTinySword = "gui/assets/Tiny Swords/Terrain/Ground/";
        const std::unordered_map<gui::Map::MapTileType, std::string> _tileTypeToFilename = {
            { gui::Map::MapTileType::MID_GROUND,         "groundMid.png" },
            { gui::Map::MapTileType::TOP_GROUND,         "groundTop.png" },
            { gui::Map::MapTileType::BOT_GROUND,         "groundBot.png" },
            { gui::Map::MapTileType::LEFT_GROUND,        "groundLeft.png" },
            { gui::Map::MapTileType::RIGHT_GROUND,       "groundRight.png" },
            { gui::Map::MapTileType::LEFT_BOT_GROUND,    "groundBotLeftCorner.png" },
            { gui::Map::MapTileType::RIGHT_BOT_GROUND,   "groundBotRightCorner.png" },
            { gui::Map::MapTileType::LEFT_TOP_GROUND,    "groundTopLeftCorner.png" },
            { gui::Map::MapTileType::RIGHT_TOP_GROUND,   "groundTopRightCorner.png" },
            { gui::Map::MapTileType::SEA,                "Water.png" }
        };
        const std::unordered_map<gui::Tile::Resource, std::tuple<std::string, float>> _resourceAssets = {
            { gui::Tile::Resource::FOOD,     { "Food.png",      TILE_SIZE } },
            { gui::Tile::Resource::LINEMATE, { "Linemate.png",  25.f } },
            { gui::Tile::Resource::DERAUMERE,{ "Deraumere.png", 25.f } },
            { gui::Tile::Resource::SIBUR,    { "Sibur.png",     25.f } },
            { gui::Tile::Resource::MENDIANE, { "Mendiane.png",  25.f } },
            { gui::Tile::Resource::PHIRAS,   { "Phiras.png",    25.f } },
            { gui::Tile::Resource::THYSTAME, { "Thystame.png",  25.f } }
        };
        
    };
}


