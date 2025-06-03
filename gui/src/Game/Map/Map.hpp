/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Map.hpp
*/

#pragma once
#include "Game/Map/Tile/Tile.hpp"
#include <vector>
#include "Tools/Position/Position.hpp"
#include "Game/Renderer/IRenderEntity/IRenderEntity.hpp"
#include "Game/Renderer/Object/IStaticObject.hpp"
#include "Game/Renderer/Object/IAnimatedObject.hpp"
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
        const Tile& getTile(const tools::Position<int> &pos) const;
        tools::Position<int> getDim() const { return tools::Position<int>(_width, _height );}
        virtual void setTile(const Tile& tile, const tools::Position<int> &pos) = 0;
};

class Map : public MapState, public render::IRenderEntity{
private:
    int _width;
    int _height;
    std::vector<std::vector<Tile>> _map;

public:
    Map(int width, int height, std::unique_ptr<render::IStaticObject> tileObject = nullptr)
        : MapState(width, height), _tileObject(std::move(tileObject)) {}
    ~Map() = default;
    private:
    std::unique_ptr<render::IStaticObject> _tileObject;
    //Do a table for props;
    void setTile(const Tile& tile, const tools::Position<int> &pos);
    void draw() const {std::cout << "Draw map not implemented" << std::endl;};
    bool update(float) {return true;};
};

} // namespace game


