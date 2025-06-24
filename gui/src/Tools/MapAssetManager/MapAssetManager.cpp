/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** MapAssetManager.hpp
*/

#include "MapAssetManager.hpp"
#include <stdexcept>

namespace tools
{
    MapAssetManager::MapAssetManager()
    {
        for (const auto& [type, filename] : _tileTypeToFilename) {
            std::string path = (type == gui::Map::MapTileType::SEA)
                ? "gui/assets/Tiny Swords/Terrain/Water/" + filename
                : _basePathTinySword + filename;
    
            _tiles.emplace(
                type,
                AssetDefinition(path, {}, TILE_SIZE, 1, 1)
            );
        }
    }
    
    const AssetDefinition& MapAssetManager::getTile(gui::Map::MapTileType type) const
    {
        auto it = _tiles.find(type);
        if (it == _tiles.end())
            throw std::runtime_error("Tile not found for MapTileType.");
        return it->second;
    }
    
    std::unordered_map<gui::Map::MapTileType, std::unique_ptr<render::IStaticSprite>>
    MapAssetManager::getTileSprites(render::IObjectFactory& factory) const
    {
        std::unordered_map<gui::Map::MapTileType, std::unique_ptr<render::IStaticSprite>> result;
        for (const auto& [type, def] : _tiles) {
            result[type] = factory.createStaticSprite(def);
        }
        return result;
    }
} // namespace tools

