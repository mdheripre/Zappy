/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "IObject.hpp"

namespace render {
    class IProgressBar : public IObject {
    public:
        virtual ~IProgressBar() = default;

        virtual void setRange(float min, float max) = 0;
        virtual void setValue(float value) = 0;
    };
}
