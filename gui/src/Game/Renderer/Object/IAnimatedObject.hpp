/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once

#include "IObject.hpp"
#include "IModel.hpp"

namespace render
{
    class IAnimatedObject : public IObject
    {
    public:
        virtual ~IAnimatedObject() = default;

        virtual void playClip(int clipIndex, bool loop) = 0;
        virtual void setFrame(int frameIndex) = 0;
        virtual void updateObject(float dt) = 0;
    };
}
