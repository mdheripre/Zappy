/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "Tools/Vector/Vector.hpp"

namespace render
{
    class IObject
    {
        public:
            virtual ~IObject() = default;
            virtual const tools::Vector2<float> &getPosition() const = 0;
            virtual tools::Vector2<float> getSize() const = 0;
            virtual void setPosition(const tools::Vector2<float> &pos) = 0;
            virtual void drawObject() const = 0;
    };
} // namespace render
