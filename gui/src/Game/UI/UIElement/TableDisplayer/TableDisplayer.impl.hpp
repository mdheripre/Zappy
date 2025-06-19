/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TableDisplayer.impl.hpp
*/

#pragma once

#include "TableDisplayer.hpp"
#include <sstream>
#include <iomanip>

namespace gui {

    template <int col>
    TableDisplayer<col>::TableDisplayer(
        std::string title,
        float w,
        float h,
        float t,
        float l,
        std::unique_ptr<render::IText> textDisplayer,
        std::unique_ptr<render::IObject> background,
        std::array<std::string, col> header
    ) : UIBox(title, w, h, t, l, std::move(textDisplayer), std::move(background)), _header(header)
    {
        _builder.setColumns(std::vector<std::string>(_header.begin(), _header.end()));
        _rows.clear();
    }

    template <int col>
    void TableDisplayer<col>::clear()
    {
        _rows.clear();
        _builder.clear();
        _builder.setColumns(std::vector<std::string>(_header.begin(), _header.end()));
    }

    template <int col>
    void TableDisplayer<col>::pushRow(std::array<std::string, col> row)
    {
        _rows.push_back(row);
        _builder.addRow(std::vector<std::string>(row.begin(), row.end()));

        std::ostringstream oss;
        oss << _title << "\n\n" << _builder.build();
        _textDisplayer->setText(oss.str());
    }

    template <int col>
    bool TableDisplayer<col>::update(float)
    {
        return true;
    }

    template <int col>
    void TableDisplayer<col>::draw() const
    {
        UIBox::draw();
    }

    template <int col>
    void TableDisplayer<col>::setCharaterSize(int size)
    {
        _textDisplayer->setCharacterSize(size);
    }

} // namespace gui