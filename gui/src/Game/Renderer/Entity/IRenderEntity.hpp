/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once

namespace render
{
    class IRenderEntity {
        public:
            virtual ~IRenderEntity() = default;
            //Return false if renderer have to delete this object
            virtual bool update(float dt) = 0;
            virtual void draw() const = 0;
        }; 
} // namespace render

