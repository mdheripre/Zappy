/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IObject.hpp
*/

#pragma once
#include "Game/Renderer/Object/IObject.hpp"
#include <string>

namespace render
{
    class IText : public IObject
    {
    public:
        virtual ~IText() = default;
        virtual void setText(std::string text) = 0;
        virtual float getCharacterSize() const = 0;
        virtual void setCharacterSize(float size) = 0;
        virtual int estimateMaxCharsPerLine(float width) const = 0;
        virtual float getLineHeight() const = 0;
    };
} // namespace render
