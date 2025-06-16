/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "Tools/ViewPort/ViewPort.hpp"

namespace render
{
    class ICanva
    {
        public:
            virtual ~ICanva() = default;
            virtual tools::ViewPort getViewPort() const = 0;
            virtual void beginUI() const = 0;
            virtual void endUI() const = 0;
    };
} // namespace render
