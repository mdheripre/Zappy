/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** MapAssetManager.cpp
*/

#include "MapAssetManager.hpp"
#include <stdexcept>

namespace tools
{
    /**
     * @brief Constructs the MapAssetManager and initializes tile definitions.
     *
     * Loads tile asset paths and definitions for all MapTileType entries.
     */
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

    /**
     * @brief Retrieves the AssetDefinition for a given tile type.
     *
     * @param type The tile type to retrieve.
     * @return The corresponding AssetDefinition.
     * @throws std::runtime_error if the tile type is not found.
     */
    const AssetDefinition& MapAssetManager::getTile(gui::Map::MapTileType type) const
    {
        auto it = _tiles.find(type);
        if (it == _tiles.end())
            throw std::runtime_error("Tile not found for MapTileType.");
        return it->second;
    }

    /**
     * @brief Creates static sprites for all tile types using the given factory.
     *
     * @param factory The factory used to create static sprite objects.
     * @return A map of MapTileType to unique pointers of IStaticSprite.
     */
    std::unordered_map<gui::Map::MapTileType, std::unique_ptr<render::IStaticSprite>>
    MapAssetManager::getTileSprites(render::IObjectFactory& factory) const
    {
        std::unordered_map<gui::Map::MapTileType, std::unique_ptr<render::IStaticSprite>> result;
        for (const auto& [type, def] : _tiles) {
            result[type] = factory.createStaticSprite(def);
        }
        return result;
    }

    /**
     * @brief Creates animated sprites for all in-game resources.
     *
     * Uses the _resourceAssets map to configure the asset path and scale for each resource.
     * The animation is locked to frame 0 to behave like a static sprite.
     *
     * @param factory The factory used to create animated sprite objects.
     * @return An array of 7 unique pointers to IAnimatedSprite, one per resource type.
     */
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
