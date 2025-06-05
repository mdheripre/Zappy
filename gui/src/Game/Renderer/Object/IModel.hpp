/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once

#include <string>
#include "Tools/BoundingBox/BoundingBox.hpp"

namespace render
{
    class IModel
    {
    public:
        virtual ~IModel() = default;
        virtual void loadFromFile(const std::string& path) = 0;
        virtual const tools::BoundingBox &getBoundingBox() const = 0;
        virtual int getAnimationFrameCount(int animIndex) const = 0;
        virtual void applyAnimationFrame(int animIndex, int frameIndex) = 0;
        virtual void drawAt(const tools::Position3D<float>& pos) const = 0;
    };
}

