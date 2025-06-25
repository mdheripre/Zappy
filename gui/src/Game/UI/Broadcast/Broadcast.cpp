/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Broadcast.cpp
*/

#include "Broadcast.hpp"

gui::Broadcast::Broadcast(render::IObjectFactory &factory) :
    Broadcast::Logger("Broadcast",
    0.5f, 0.3f, 0.7f, 0.4f,
    factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
    factory.createRoundedRectangle(20))
{}

