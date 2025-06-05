/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibAnimatedObject.hpp
*/

#pragma once

#include "Game/Renderer/Object/IAnimatedObject.hpp"
#include <memory>
#include <stdexcept>

namespace rl
{
    class RaylibAnimatedObject : public render::IAnimatedObject
    {
        
        public:
            RaylibAnimatedObject(std::shared_ptr<render::IModel> model,
                std::unordered_map<int, int> animationMap,
                float fps = 24.0);
            ~RaylibAnimatedObject() override = default;
            
            void setPosition(const tools::Position3D<float>& pos) override;
            const tools::Position3D<float>& getPosition() const override;
            
            const tools::BoundingBox &getBoundingBox() const override;
            void playClip(int clipIndex, bool loop) override;
            
            bool updateObject(float dt) override;
            void drawObject() const override;
        private:
            std::shared_ptr<render::IModel> _model;
            tools::Position3D<float> _position;
            std::unordered_map<int, int> _animationMap;
    
            int _currentAnim = 0;
            int _currentFrame = 0;
            bool _loop = true;
            float _time = 0.0f;
            float _frameRate = 24.0f;
    };
}
