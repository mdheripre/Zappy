/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** ModelManager.cpp
*/

#include "ModelManager.hpp"

namespace rl {

ModelManager::ModelManager() = default;

/**
 * @brief Loads or retrieves a model from the internal cache.
 *
 * If the model is already loaded, returns the existing one. Otherwise,
 * loads it from file and caches it.
 *
 * @param path File path to the model.
 * @return Shared pointer to the model.
 */
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

/**
 * @brief Clears all cached models.
 *
 * Use this to release GPU resources or reset model states.
 */

void ModelManager::clear()
{
    _loadedModels.clear();
}

}
