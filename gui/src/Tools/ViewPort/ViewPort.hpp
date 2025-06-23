/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamBrandingManager.cpp
*/

#pragma once

namespace tools
{
    class ViewPort
    {
        public:
            ViewPort(float centerX, float centerY, float width, float height)
                : w(width), h(height),
                left(centerX - width / 2.0f),
                top(centerY - height / 2.0f),
                right(centerX + width / 2.0f),
                bottom(centerY + height / 2.0f)
                {}
            ~ViewPort() = default;
            float w;
            float h;
            float top;
            float left;
            float right;
            float bottom;
    };
} // namespace tools
