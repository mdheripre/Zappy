/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once

#include "Tools/Vector/Vector.hpp"
#include <functional>
namespace render
{
    class AInteractiveEntity {
        public:
            virtual ~AInteractiveEntity() = default;
        
            void computeHover(const tools::Vector2<float>& mousePosition)
            {
                bool isOver = isMouseOver(mousePosition);
        
                if (isOver && !_hovered) {
                    _hovered = true;
                    onHoverEnter();
                } else if (!isOver && _hovered) {
                    _hovered = false;
                    onHoverExit();
                }
            }
        
            void processClick(bool mousePressed, bool isSelected = false)
            {
                if (isSelected && mousePressed && !_clicked) {
                    _clicked = true;
                    onClick();
                } else if (!mousePressed && _clicked) {
                    _clicked = false;
                    onRelease();
                }
            }
            virtual bool isMouseOver(const tools::Vector2<float>& mousePosition) const = 0;
            protected:
                virtual void onHoverEnter() {}
                virtual void onHoverExit() {}
                virtual void onClick() {}
                virtual void onRelease() {}
            private:
                bool _hovered = false;
                bool _clicked = false;
        };
} // namespace render


