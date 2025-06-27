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

    std::array<std::unique_ptr<render::IAnimatedSprite>, 7>
    MapAssetManager::getProps(render::IObjectFactory& factory) const
    {
        std::array<std::unique_ptr<render::IAnimatedSprite>, 7> props;

        for (const auto& [res, tuple] : _resourceAssets) {
            const std::string& file = std::get<0>(tuple);
            float size = std::get<1>(tuple);

            props[static_cast<int>(res)] = factory.createAnimatedSprite(
                tools::AssetDefinition(
                    "gui/assets/Tiny Swords/Resources/Resources/" + file,
                    { {0, {false, 0, 1}} },
                    size,
                    1, 1
                )
            );
            props[static_cast<int>(res)]->playAnimation(0, false);
        }

        return props;
    }


} // namespace tools

