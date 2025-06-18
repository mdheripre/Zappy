/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamDisplayer.hpp
*/

#pragma once
#include <memory>
#include "Game/Renderer/Entity/IRenderEntity.hpp"
#include "Game/Renderer/Object/IText.hpp"
#include "Tools/Define.hpp"

namespace gui
{
    class UIBox : public render::IRenderEntity
    {
        public:
            UIBox(std::string title,
                float w,
                float h,
                float t,
                float l,
                std::unique_ptr<render::IText> textDisplayer,
                std::unique_ptr<render::IObject> background);
            virtual ~UIBox() = default;
            virtual void draw() const;
            void setVisible(bool value) {_visible = value;};
            bool isVisible() {return _visible;};
        protected:
            std::string _title;
            std::unique_ptr<render::IText> _textDisplayer;
            std::unique_ptr<render::IObject> _background;
            float _width;
            float _height;
            float _top;
            float _left;
            bool _visible = true;
    };
} // namespace gui
