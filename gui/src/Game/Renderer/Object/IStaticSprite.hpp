/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "IObject.hpp"

namespace render
{
    class IStaticSprite : public IObject
    {
    public:
        virtual ~IStaticSprite() = default;
    };
}
