/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** ModelManager.cpp
*/

#include "ModelManager.hpp"

namespace rl {

ModelManager::ModelManager() = default;

std::shared_ptr<render::IModel> ModelManager::getOrLoad(const std::string& path)
{
    auto it = _loadedModels.find(path);
    if (it != _loadedModels.end()) {
        return it->second;
    }

    auto model = std::make_shared<RaylibModel>();
    model->loadFromFile(path);
    _loadedModels[path] = model;
    return model;
}

void ModelManager::clear()
{
    _loadedModels.clear();
}

}
