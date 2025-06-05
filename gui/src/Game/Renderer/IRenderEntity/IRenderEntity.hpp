/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once
#include "Tools/Position/Position.hpp"

namespace render
{
    class IRenderEntity {
        public:
            virtual ~IRenderEntity() = default;
            virtual bool update(float dt) = 0;
            virtual void draw() const = 0;
        }; 
} // namespace render

