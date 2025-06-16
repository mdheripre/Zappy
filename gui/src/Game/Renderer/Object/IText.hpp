/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "Game/Renderer/Object/IObject.hpp"
#include <string>

namespace render
{
    class IText : public IObject
    {
    public:
        virtual ~IText() = default;
        virtual void setText(std::string text) = 0;
    };
} // namespace render
