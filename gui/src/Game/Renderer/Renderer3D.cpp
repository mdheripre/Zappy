/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#include "Renderer3D.hpp"

gui::Renderer3D::Renderer3D() {}

gui::Renderer3D::~Renderer3D()
{
    CloseWindow();
}

void gui::Renderer3D::init()
{
    InitWindow(1280, 720, "Zappy 3D Viewer");
    SetTargetFPS(60);

    _camera.position = { 10.0f, 15.0f, 10.0f };
    _camera.target = { 0.0f, 0.0f, 0.0f };
    _camera.up = { 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;
}

bool gui::Renderer3D::shouldClose() const
{
    return WindowShouldClose();
}

void gui::Renderer3D::handleCameraInput()
{
    if (IsKeyDown(KEY_RIGHT)) _camera.position.x += 0.2f;
    if (IsKeyDown(KEY_LEFT))  _camera.position.x -= 0.2f;
    if (IsKeyDown(KEY_UP))    _camera.position.z -= 0.2f;
    if (IsKeyDown(KEY_DOWN))  _camera.position.z += 0.2f;
    if (IsKeyDown(KEY_W))     _camera.position.y += 0.2f;
    if (IsKeyDown(KEY_S))     _camera.position.y -= 0.2f;
}

static const std::map<int, Color> &getResourceColors() 
{
    static const std::map<int, Color> resourceColors = {
        {0, GREEN},    // food
        {1, ORANGE},   // linemate
        {2, BLUE},     // deraumere
        {3, PURPLE},   // sibur
        {4, RED},      // mendiane
        {5, GOLD},     // phiras
        {6, VIOLET}    // thystame
    };
    return resourceColors;
}

// Les deux fonctions getResourseColor(s) sont ammenées à disparaitre a l'avenir
// TODO : CHANGER POUR UTILISER DES SPRITES

Color gui::Renderer3D::getResourceColor(int id)
{
    const auto &colors = getResourceColors();
    auto it = colors.find(id);
    return it != colors.end() ? it->second : GRAY;
}

void gui::Renderer3D::update()
{
    handleCameraInput();
}

void gui::Renderer3D::drawTileResources(const Vector3& tilePos, const std::array<int, 7>& resources)
{
    for (int type = 0; type < static_cast<int>(resources.size()); ++type) {
        int count = resources[type];
        for (int i = 0; i < count; ++i) {
            Vector3 resPos = {
                tilePos.x + 0.2f * type,
                0.15f + i * 0.15f,
                tilePos.z
            };
            DrawCube(resPos, 0.15f, 0.15f, 0.15f, getResourceColor(type));
        }
    }
}

void gui::Renderer3D::render(const game::Map &map)
{
    auto [width, height] = map.getDim();
    float offsetX = width / 2.0f;
    float offsetY = height / 2.0f;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(_camera);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Vector3 tilePos = { (float)x - offsetX, 0.0f, (float)y - offsetY };
            DrawCube(tilePos, 1.0f, 0.1f, 1.0f, LIGHTGRAY);
            DrawCubeWires(tilePos, 1.0f, 0.1f, 1.0f, DARKGRAY);

            const auto &resources = map.getTile({x, y}).getResources();
            drawTileResources(tilePos, resources);
        }
    }

    EndMode3D();
    DrawText("Zappy 3D Viewer - Fleches pour naviguer", 10, 10, 20, DARKGRAY);
    EndDrawing();
}
