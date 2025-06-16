/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamDisplayer.cpp
*/

#pragma once
#include "Tools/ViewPort/ViewPort.hpp"

namespace gui
{
    class AUIElement
    {
        public:
            virtual ~AUIElement() = default;
            virtual void update(float dt) = 0;
            virtual void draw(tools::ViewPort vp) = 0;
            void setVisibility(bool value) {
                _visible = value;
            };
        protected:
            bool _visible = true;
    };
} // namespace gui
