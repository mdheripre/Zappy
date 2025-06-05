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
                    std::unordered_map<int, int> animationMap,
                    float scale = 1.0f)
        : _modelPath(std::move(modelPath)),
          _animationMap(std::move(animationMap)),
          _scale(scale) {}

    const std::string& getModelPath() const { return _modelPath; }
    float getScale() const { return _scale; }

    int getAnimation(int anim) const {
        auto it = _animationMap.find(anim);
        if (it != _animationMap.end())
            return it->second;
        return -1;
    }
    private:
        std::string _modelPath;
        std::unordered_map<int, int> _animationMap;
        float _scale;

        
};
} // namespace tools

