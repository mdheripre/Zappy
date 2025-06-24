/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once

#include "IStaticSprite.hpp"
#include <memory>

namespace render
{
    class IAnimatedSprite : public IStaticSprite
    {
    public:
        virtual ~IAnimatedSprite() = default;

        virtual void playAnimation(int clipIndex, bool loop) = 0;
        virtual bool updateObject(float dt) = 0;
        virtual std::unique_ptr<IAnimatedSprite> clone() const = 0;
    };
}
