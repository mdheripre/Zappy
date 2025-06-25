/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamDisplayer.hpp
*/

#include "UIBox.hpp"

gui::UIBox::UIBox(
    std::string title,
    float w,
    float h,
    float t,
    float l,
    std::unique_ptr<render::IText> textDisplayer,
    std::unique_ptr<render::IObject> background
)
    : _title(title),
    _width(w),
    _height(h),
    _top(t),
    _left(l),
    _textDisplayer(std::move(textDisplayer)),
    _background(std::move(background))
{
    tools::Vector2<float> absPos(
        WIDTH_WINDOW * _left,
        HEIGHT_WINDOW * _top
    );
    tools::Vector2<float> absSize(
        WIDTH_WINDOW * _width,
        HEIGHT_WINDOW * _height
    );
    _background->setPosition(absPos);
    _background->setSize(absSize);
    _background->setColor(tools::Color(75, 163, 199, 255));
    _textDisplayer->setPosition(absPos);
    _textDisplayer->setSize(absSize);
    _textDisplayer->setText("  " + _title);
    _textDisplayer->setCharacterSize(20);
}

void gui::UIBox::draw() const
{
    if (!_textDisplayer || !_background || !_visible)
        return;

    _background->drawObject();
    _textDisplayer->drawObject();
}