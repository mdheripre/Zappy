/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once

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
        void render(const game::Map &map);
        bool shouldClose() const;

    private:
        Camera3D _camera;
        void handleCameraInput();
        Color getResourceColor(int resourceId);
    };
}
