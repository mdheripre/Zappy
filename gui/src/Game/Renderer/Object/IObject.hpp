/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "Tools/BoundingBox/BoundingBox.hpp"

namespace render
{
    class IObject
    {
        public:
            virtual ~IObject() = default;
            virtual const tools::Position3D<float> &getPosition() const = 0;
            virtual const tools::BoundingBox &getBoundingBox() const = 0; 
            virtual void setPosition(const tools::Position3D<float> &pos) = 0;
            virtual void drawObject() const = 0;
    };
} // namespace render
