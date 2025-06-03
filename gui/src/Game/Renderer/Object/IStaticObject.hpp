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
    class IStaticObject : public IObject, public IModel
    {
    public:
        virtual ~IStaticObject() = default;
    };
}
