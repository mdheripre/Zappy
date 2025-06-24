/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.cpp
*/

#pragma once
#include <string>
#include <unordered_map>

namespace tools
{
  class AssetDefinition {
    public:
        struct AnimationInfo {
          bool reverse;
          int line;
          int frames;
        };
        AssetDefinition(std::string modelPath,
                        std::unordered_map<int, AnimationInfo> animationMap,
                        float scale = 1.0f,
                        int frameWidth = 0,
                        int frameHeight = 0)
            : _modelPath(std::move(modelPath)),
              _animationMap(std::move(animationMap)),
              _scale(scale),
              _frameWidth(frameWidth),
              _frameHeight(frameHeight) {}
    
        const std::string& getModelPath() const { return _modelPath; }
        float getScale() const { return _scale; }
        const std::unordered_map<int, AnimationInfo>& getAnimation() const { return _animationMap; }
        int getFrameWidth() const { return _frameWidth; }
        int getFrameHeight() const { return _frameHeight; }
    
    private:
        std::string _modelPath;
        std::unordered_map<int, AnimationInfo> _animationMap;
        float _scale;
        int _frameWidth;
        int _frameHeight;
    };
} // namespace tools


  

