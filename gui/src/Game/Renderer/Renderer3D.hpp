/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once

#include <unordered_map>
#include "Game/GameState/GameState.hpp"
#include "Game/Map/Map.hpp"
#include "raylib.h"
#include <memory>
#include <map>

namespace gui {
    class Renderer3D {
    public:
        Renderer3D();
        ~Renderer3D();

        void init();
        void update();
        void drawTileResources(const Vector3& tilePos, const std::array<int, 7>& resources);
        void render(const game::Map &map, const std::unordered_map<int, game::Player> &players);
        bool shouldClose() const;

    private:
        Camera3D _camera;
        void handleCameraInput();
        Color getResourceColor(int resourceId);
    };
}
