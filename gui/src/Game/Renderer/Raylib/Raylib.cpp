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

/**
 * @brief Initializes the Raylib window and sets the frame rate.
 *
 * Uses Raylib's InitWindow and SetTargetFPS functions to create the rendering window.
 *
 * @param title Title of the window.
 * @param width Width of the window.
 * @param height Height of the window.
 * @param frameRate Target FPS.
 */
void Raylib::init(std::string title, int width, int height, int frameRate)
{
    InitWindow(width, height, title.c_str());
    SetTargetFPS(frameRate);
}

/**
 * @brief Updates all active entities in the scene.
 *
 * Calls each entity's update method and removes those that return false.
 *
 * @param dt Delta time since last frame.
 */
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

/**
 * @brief Renders the entire scene.
 *
 * Begins a 3D camera mode, draws all entities, and ends the drawing frame.
 * Also clears the background at the start.
 */
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

/**
 * @brief Sets the current camera used for 3D rendering.
 *
 * The camera is passed to Raylib during rendering to define the 3D viewpoint.
 *
 * @param cam Shared pointer to the camera object.
 */
void Raylib::setCamera(std::shared_ptr<render::Camera> cam)
{
    _cam = std::move(cam);
}

/**
 * @brief Polls input events and triggers bound actions.
 *
 * For each registered key binding, checks if the corresponding Raylib key is pressed,
 * and if so, executes the associated action.
 */
void Raylib::poll() {
    for (const auto& [key, action] : _bindings) {
        auto it = _keyMap.find(key);
        if (it != _keyMap.end() && IsKeyDown(it->second)) {
            action();
        }
    }
}

} // namespace rl
