/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Raylib.cpp
*/

#pragma once
#include "Game/Renderer/Object/IModel.hpp"
#include "Game/Renderer/Raylib/RaylibObjectFactory/RaylibModel/RaylibModel.hpp"
#include <unordered_map>
#include <memory>
#include <string>

namespace rl
{
    class ModelManager
    {
        public:
            ModelManager();
            ~ModelManager() = default;
            
            std::shared_ptr<render::IModel> getOrLoad(const std::string& path);
            void clear();
        private:
            std::unordered_map<std::string, std::shared_ptr<render::IModel>> _loadedModels;
    };
}

