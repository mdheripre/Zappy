/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Logger.hpp
*/


#pragma once
#include "Game/UI/UIElement/UIBox/UIBox.hpp"
#include <vector>
#include <array>
#include <cmath>
#include <deque>
#include <string>
#include <iostream>
#include <sstream> 

namespace gui
{
    class Logger : public UIBox
    {
        public:
            Logger(
                std::string title,
                float w,
                float h,
                float t,
                float l,
                std::unique_ptr<render::IText> textDisplayer,
                std::unique_ptr<render::IObject> background);
            virtual ~Logger() = default;
            void pushEvent(const std::string &newEvent);
            bool update(float dt);
            void draw() const;
        protected:
            std::deque<std::string> _events;
        private:
            void updateDisplayFromWrappedLines(const std::vector<std::string>& lines) const;
            void limitLines(std::vector<std::string>& lines, int maxLines) const;
            std::string computeLine(const std::string &event, int maxChars, std::vector<std::string> &wrapped) const;
            std::vector<std::string> wrapEventsToLines(int maxChars) const;


    };    
} // namespace gui
