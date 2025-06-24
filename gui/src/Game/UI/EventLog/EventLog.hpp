/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** EventLog.hpp
*/

#pragma once

#include "Game/UI/UIElement/Logger/Logger.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"

namespace gui
{
    class EventLog : public Logger
    {
        public:
            EventLog(render::IObjectFactory &factory);
            ~EventLog() = default;
    };
}
