/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibModel.hpp
*/

#pragma once

#include "Game/Renderer/Object/IModel.hpp"
#include "Tools/BoundingBox/BoundingBox.hpp"
#include "Error/Error.hpp"
#include <raylib.h>
#include <string>
#include <cmath>
#include <stdexcept>

namespace rl
{
    class RaylibModel : public render::IModel
    {
        
        public:
            RaylibModel();
            ~RaylibModel() override;
            
            void loadFromFile(const std::string& path) override;
            const tools::BoundingBox &getBoundingBox() const override;
            int getAnimationFrameCount(int animIndex) const;
            void applyAnimationFrame(int animIndex, int frameIndex) override;
            void drawAt(const tools::Position3D<float>& pos) const override;
        private:
            Model _model{};
            ModelAnimation* _animations = nullptr;
            int _animationCount = 0;
            tools::BoundingBox _boundingBox;
            bool _loaded = false;
    };
}
