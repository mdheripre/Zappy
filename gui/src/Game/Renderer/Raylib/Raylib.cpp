/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Raylib.cpp
*/

#include "Game/Renderer/Raylib/Raylib.hpp"
#include <raylib.h>
#include "Raylib.hpp"

namespace rl {

void Raylib::init(std::string title, int width, int height, int frameRate)
{
    InitWindow(width, height, title.c_str());
    SetTargetFPS(frameRate);
}

void Raylib::update(float dt)
{
    _entities.erase(
        std::remove_if(_entities.begin(), _entities.end(),
            [dt](const std::shared_ptr<render::IRenderEntity>& entity) {
                return entity && !entity->update(dt);
            }),
        _entities.end()
    );
}

void Raylib::render()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (_cam) {
        Camera3D raylibCam = {
            .position = { _cam->getPosition().x, _cam->getPosition().y, _cam->getPosition().z },
            .target   = { _cam->getTarget().x,   _cam->getTarget().y,   _cam->getTarget().z },
            .up       = { _cam->getUp().x,       _cam->getUp().y,       _cam->getUp().z },
            .fovy     = _cam->getFov(),
            .projection = _cam->getProjection()
        };

        BeginMode3D(raylibCam);
        DrawCube((Vector3){0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, RED);
        for (auto& entity : _entities) {
            if (entity)
                entity->draw();
        }

        EndMode3D();
    }
    EndDrawing();
}

void Raylib::setCamera(std::shared_ptr<render::Camera> cam)
{
    _cam = std::move(cam);
}

void Raylib::poll() {
    for (const auto& [key, action] : _bindings) {
        auto it = _keyMap.find(key);
        if (it != _keyMap.end() && IsKeyDown(it->second)) {
            action();
        }
    }
}

} // namespace rl
