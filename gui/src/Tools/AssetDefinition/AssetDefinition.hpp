/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.cpp
*/

#pragma once
#include <string>
#include <unordered_map>

namespace tools {
class AssetDefinition {
public:
    AssetDefinition(std::string modelPath,
                    std::string texturePath,
                    std::unordered_map<int, int> animationMap,
                    float scale = 1.0f)
        : _modelPath(std::move(modelPath)),
          _texturePath(std::move(texturePath)),
          _animationMap(std::move(animationMap)),
          _scale(scale) {}

    const std::string& getModelPath() const { return _modelPath; }
    float getScale() const { return _scale; }

    const std::unordered_map<int, int> &getAnimation() const {return _animationMap;};
    private:
        std::string _modelPath;
        std::string _texturePath;
        std::unordered_map<int, int> _animationMap;
        float _scale;

        
};
} // namespace tools

