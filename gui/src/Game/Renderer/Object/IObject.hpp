/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "Tools/Vector/Vector.hpp"
#include "Tools/Color/Color.hpp"

namespace render
{
    class IObject
    {
        public:
            virtual ~IObject() = default;
            virtual tools::Vector2<float> getPosition() const = 0;
            virtual tools::Vector2<float> getSize() const = 0;
            virtual void setSize(const tools::Vector2<float> &size) = 0;
            virtual void setPosition(const tools::Vector2<float> &pos) = 0;
            virtual void drawObject() const = 0;
            virtual bool contains(tools::Vector2<float> position) = 0;
            virtual void setColor(const tools::Color &color) = 0;
    };
} // namespace render
