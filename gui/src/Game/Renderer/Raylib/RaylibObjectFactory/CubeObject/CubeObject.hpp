/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibStaticObject.cpp
*/

#pragma once

#include "Game/Renderer/Object/IObject.hpp"
#include "Tools/Position/Position.hpp"
#include "Tools/Color/Color.hpp"
#include <raylib.h>

namespace rl
{
    class CubeObject : public render::IObject
    {
        public:
            CubeObject(const tools::Position3D<float>& size = {1.0f, 1.0f, 1.0f},
            tools::Color color = tools::Color(255, 255, 255, 255));
            const tools::BoundingBox& getBoundingBox() const override;
            void setPosition(const tools::Position3D<float>& pos) override;
            const tools::Position3D<float>& getPosition() const override;
            void drawObject() const override;
        private:
            tools::BoundingBox _bb;
            tools::Position3D<float> _position;
            tools::Position3D<float> _size;
            tools::Color _color;
    };
}