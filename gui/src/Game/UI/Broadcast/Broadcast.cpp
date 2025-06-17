/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Broadcast.cpp
*/

#include "Broadcast.hpp"

gui::Broadcast::Broadcast(render::IObjectFactory &factory) :
    Broadcast::Logger("Broadcast",
    0.2f, 0.6f, 0.08f, 0.79f,
    factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
    factory.createRectangle())
{}

