/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once

#include "IStaticSprite.hpp"

namespace render
{
    class IAnimatedSprite : public IStaticSprite
    {
    public:
        virtual ~IAnimatedSprite() = default;

        virtual void playAnimation(int clipIndex, bool loop) = 0;
        virtual bool updateObject(float dt) = 0;
    };
}
