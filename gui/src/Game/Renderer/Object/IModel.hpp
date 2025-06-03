/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once

#pragma once

#include <string>

namespace render
{
    class IModel
    {
    public:
        virtual ~IModel() = default;
        virtual void loadFromFile(const std::string& path) = 0;
    };
}

