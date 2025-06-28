/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/


#pragma once

namespace render
{
    class ISound
    {
    public:
        virtual ~ISound() = default;
        virtual void play(bool loop) = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
        virtual void changeState() = 0;
        virtual void reset() = 0;
    };
} // namespace render
