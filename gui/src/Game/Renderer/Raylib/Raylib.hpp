/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RayLib.hpp
*/

#pragma once

#include <unordered_map>
#include "Game/GameState/GameState.hpp"
#include "Game/Map/Map.hpp"
#include "Game/Renderer/IRenderer.hpp"
#include "Game/Renderer/Camera/Camera.hpp"
#include "raylib.h"
#include <memory>
#include <algorithm>
#include <map>

namespace rl {
    class Raylib : public render::IRenderer {
    public:
        Raylib() = default;
        ~Raylib() {CloseWindow;};

        void init(std::string title, int width, int height, int frameRate);
        void update(float dt);
        void render();
        bool isClose() const {return WindowShouldClose();};
        void setCamera(std::shared_ptr<render::Camera> cam);
        void pushEntity(std::shared_ptr<render::IRenderEntity> renderEntity) {_entities.push_back(renderEntity);};
        void setBindings(std::unordered_map<tools::KeyCode, std::function<void()>> bindings) {_bindings = bindings;};
        void poll();
        const std::unordered_map<tools::KeyCode, int> _keyMap = {
            { tools::KeyCode::Right, KEY_RIGHT },
            { tools::KeyCode::Left,  KEY_LEFT },
            { tools::KeyCode::Up,    KEY_UP },
            { tools::KeyCode::Down,  KEY_DOWN },
            { tools::KeyCode::W,     KEY_W },
            { tools::KeyCode::S,     KEY_S }
        };
    private:
        std::unordered_map<tools::KeyCode, std::function<void()>> _bindings;
        std::shared_ptr<render::Camera> _cam;
        std::vector<std::shared_ptr<render::IRenderEntity>> _entities;
    };
}
