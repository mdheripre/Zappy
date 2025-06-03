/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "Tools/Position/Position.hpp"

namespace render
{
    class IObject
    {
        public:
            virtual ~IObject() = default;
            virtual const tools::Position3D<float> &getPosition() const = 0;
            virtual void setPosition(tools::Position3D<float> pos) = 0;
            virtual void drawObject() const = 0;
            virtual void updateObject() const = 0;
    };
} // namespace render
