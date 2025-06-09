#include "raylib.h"
#include <iostream>
#include <cmath>

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Model Viewer - Trantorian");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = { 4.0f, 2.0f, 4.0f };
    camera.target = { 0.0f, 1.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Chargement du modèle et de sa texture de diffusion
    Model model = LoadModel("gui/src/Asset/Incantation/Magic_ring/scene.gltf");
    Texture2D emissive = LoadTexture("gui/src/Asset/Incantation/Magic_ring/textures/Material.001_diffuse.png");

    //Application de la texture d’émission sur tous les matériaux (par précaution)
    for (int i = 0; i < model.materialCount; i++) {
        SetMaterialTexture(&model.materials[i], MATERIAL_MAP_DIFFUSE, emissive);
    }

    // Chargement des animations
    int animCount = 0;
    ModelAnimation *anims = LoadModelAnimations("gui/src/Asset/Incantation/Magic_ring/scene.gltf", &animCount);
    int currentAnim = 0;
    float animTime = 0.0f;
    const float animFps = 30.0f;

    // Mise à l’échelle pour correspondre à un cube unité
    BoundingBox bbox = GetModelBoundingBox(model);
    Vector3 size = {
        bbox.max.x - bbox.min.x,
        bbox.max.y - bbox.min.y,
        bbox.max.z - bbox.min.z
    };
    std::cout << "Model size: "
          << size.x << " x "
          << size.y << " x "
          << size.z << std::endl;
    
    //Scale à tester
    float scaling = 0.5f;

    Vector3 targetSize = {scaling, scaling, scaling};
    float maxDim = fmax(size.x, fmax(size.y, size.z));
    Vector3 scale = {
        targetSize.x / maxDim,
        targetSize.y / maxDim,
        targetSize.z / maxDim
    };

    float modelBase = bbox.min.y * scale.y;
    float surfaceY = 1.0f; // haut du cube
    Vector3 modelPosition = {
    0.0f,
    surfaceY - modelBase,
    0.0f
    };

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_RIGHT)) currentAnim = (currentAnim + 1) % animCount;
        if (IsKeyPressed(KEY_LEFT)) currentAnim = (currentAnim - 1 + animCount) % animCount;

        animTime += GetFrameTime();
        int animFrame = (int)(animTime * animFps);

        //Protection contre les crashs potentiels
        if (anims && IsModelAnimationValid(model, anims[currentAnim])) {
            UpdateModelAnimation(model, anims[currentAnim], animFrame % anims[currentAnim].frameCount);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
            DrawModelEx(model, modelPosition, (Vector3){0, 1, 0}, 0.0f, scale, WHITE);
            DrawCube((Vector3){0.0f, 0.5f, 0.0f}, 1.0f, 1.0f, 1.0f, RED); // Cube unité de référence
        EndMode3D();

        DrawText(TextFormat("Animation %d / %d", currentAnim + 1, animCount), 10, 10, 20, DARKGRAY);
        DrawText("← / → pour changer l'animation", 10, 35, 20, GRAY);
        EndDrawing();
    }

    // Libération des ressources
    UnloadModel(model);
    //UnloadTexture(emissive);
    UnloadModelAnimations(anims, animCount);
    CloseWindow();

    return 0;
}