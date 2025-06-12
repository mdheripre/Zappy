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
#include <memory>
#include <stdexcept>
#include <iostream>

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
    private:
        int _width;
        int _height;
        std::vector<std::vector<Tile>> _map;
    
        std::unique_ptr<render::IObject> _tileObject;
        std::array<std::unique_ptr<render::IAnimatedSprite>, 7> _propsObject;
    
    public:
        Map(int width,
            int height,
            std::unique_ptr<render::IObject> tileObject = nullptr,
            std::array<std::unique_ptr<render::IAnimatedSprite>, 7> propsObject = {});
        ~Map() override = default;
    
        void setTile(const Tile& tile, const tools::Vector2<int>& pos);
        void drawProps(const Tile& tile, const tools::Vector2<float> &tilePos) const;
        void draw() const override;
        bool update(float dt) override;
        bool popResource(Tile::Resource res, tools::Vector2<int> pos);
        void pushResource(Tile::Resource res, tools::Vector2<int> pos);
    };
    

} // namespace game


