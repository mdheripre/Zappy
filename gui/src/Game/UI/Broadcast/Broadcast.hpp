/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Broadcast.hpp
*/

#pragma once
#include "Game/UI/UIElement/Logger/Logger.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"

namespace gui
{
    class Broadcast : public Logger
    {
        public:
            Broadcast(render::IObjectFactory &factory);
            ~Broadcast() = default;
    };
}
