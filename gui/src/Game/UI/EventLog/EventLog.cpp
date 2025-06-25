/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** EventLog.cpp
*/

#include "EventLog.hpp"

gui::EventLog::EventLog(render::IObjectFactory &factory) :
    EventLog::Logger("Event Log",
        0.2f, 0.6f, 0.08f, 0.01f,
        factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
        factory.createRoundedRectangle(20))
{}
