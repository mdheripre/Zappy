/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** Interactive.hpp
*/

#pragma once
#include <memory>
#include <functional>

namespace tools
{
    class InteractionComponent {
    public:
        virtual ~InteractionComponent() = default;
        virtual void onHoverEnter() {
            if (!_hovering)
                _hovering = true;
        }
    
        virtual void onHoverExit() {
            if (_hovering)
                _hovering = false;
        }
    
        virtual void onClick() {
            _isPress = true;
        }
    
        virtual void onRelease() {
            if (_isPress)
                _isPress = false;
        }
    
    private:       
        bool _hovering = false;
        bool _isPress = false;
    };
    
} // namespace tools


