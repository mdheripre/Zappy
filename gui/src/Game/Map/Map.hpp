/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Map.hpp
*/

#pragma once
#include "Game/Map/Tile/Tile.hpp"
#include <vector>
#include "Tools/Vector/Vector.hpp"
#include "Game/Renderer/IRenderEntity/IRenderEntity.hpp"
#include "Game/Renderer/Object/IStaticSprite.hpp"
#include "Game/Renderer/Object/IAnimatedSprite.hpp"
#include "Tools/Error/Error.hpp"
#include <memory>
#include <tuple>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include <iostream>

namespace std {
    template<>
    struct hash<std::tuple<bool, bool, bool, bool>> {
        std::size_t operator()(const std::tuple<bool, bool, bool, bool>& t) const noexcept {
            auto [top, bot, left, right] = t;
            return (static_cast<std::size_t>(top) << 3)
                 | (static_cast<std::size_t>(bot) << 2)
                 | (static_cast<std::size_t>(left) << 1)
                 | static_cast<std::size_t>(right);
        }
    };
}

namespace gui {

class MapState
{
    private:
        int _width;
        int _height;
        std::vector<std::vector<Tile>> _map;
    public:
        MapState(int width, int height)
            : _width(width), _height(height), _map(height, std::vector<Tile>(width)) {}
        virtual ~MapState() = default;
        const Tile& getTile(const tools::Vector2<int> &pos) const;
        tools::Vector2<int> getDim() const { return tools::Vector2<int>(_width, _height );}
        virtual void setTile(const Tile& tile, const tools::Vector2<int> &pos) = 0;
        virtual bool popResource(Tile::Resource res, tools::Vector2<int> pos) = 0;
        virtual void pushResource(Tile::Resource res, tools::Vector2<int> pos) = 0;
};

class Map : public MapState, public render::IRenderEntity {
    
    public:
        enum class MapTileType {
            MID_GROUND,
            TOP_GROUND,
            BOT_GROUND,
            LEFT_GROUND,
            RIGHT_GROUND,
            LEFT_BOT_GROUND,
            LEFT_TOP_GROUND,
            RIGHT_TOP_GROUND,
            RIGHT_BOT_GROUND
        };

        Map(int width,
            int height,
            std::unordered_map<Map::MapTileType, std::unique_ptr<render::IStaticSprite>> tilesObject,
            std::array<std::unique_ptr<render::IAnimatedSprite>, 7> propsObject = {});
            ~Map() override = default;
            
            void setTile(const Tile& tile, const tools::Vector2<int>& pos);
            void drawProps(const Tile& tile, const tools::Vector2<float> &tilePos) const;
            void draw() const override;
            bool update(float dt) override;
            bool popResource(Tile::Resource res, tools::Vector2<int> pos);
            void pushResource(Tile::Resource res, tools::Vector2<int> pos);

        private:
            int _width;
            int _height;
            std::vector<std::vector<Tile>> _map;
            std::unordered_map<Map::MapTileType, std::unique_ptr<render::IStaticSprite>> _tilesObject;
            std::array<std::unique_ptr<render::IAnimatedSprite>, 7> _propsObject;
            std::vector<std::vector<gui::Map::MapTileType>> _tileTypes;
            tools::Vector2<float> _tileSize;

            void generateTileTypes();

            using BorderFlags = std::tuple<bool, bool, bool, bool>;
            const std::unordered_map<BorderFlags, gui::Map::MapTileType> _tileTypeMap = {
                { {true, false, true, false}, gui::Map::MapTileType::LEFT_TOP_GROUND },
                { {true, false, false, true}, gui::Map::MapTileType::RIGHT_TOP_GROUND },
                { {false, true, true, false}, gui::Map::MapTileType::LEFT_BOT_GROUND },
                { {false, true, false, true}, gui::Map::MapTileType::RIGHT_BOT_GROUND },
                { {true, false, false, false}, gui::Map::MapTileType::TOP_GROUND },
                { {false, true, false, false}, gui::Map::MapTileType::BOT_GROUND },
                { {false, false, true, false}, gui::Map::MapTileType::LEFT_GROUND },
                { {false, false, false, true}, gui::Map::MapTileType::RIGHT_GROUND }
            };
        };
        
        
    } // namespace game

