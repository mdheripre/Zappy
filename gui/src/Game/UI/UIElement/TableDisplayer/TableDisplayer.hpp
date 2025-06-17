/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TableDisplayer.hpp
*/

#pragma once

#include "Game/UI/UIElement/UIBox/UIBox.hpp"
#include "Tools/TextTableBuilder/TextTableBuilder.hpp"
#include <array>
#include <vector>
#include <string>

namespace gui {

    template <int col>
    class TableDisplayer : public UIBox {
    public:
        TableDisplayer(
            std::string title,
            float w,
            float h,
            float t,
            float l,
            std::unique_ptr<render::IText> textDisplayer,
            std::unique_ptr<render::IObject> background,
            std::array<std::string, col> header
        );

        ~TableDisplayer() = default;

        void clear();
        void pushRow(std::array<std::string, col> row);
        bool update(float dt);
        void draw() const;

    private:
        tools::TextTableBuilder _builder;
        std::vector<std::array<std::string, col>> _rows;
        std::array<std::string, col> _header;
    };

} // namespace gui

#include "TableDisplayer.impl.hpp"
