/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TextTableBuilder.cpp
*/

#include "TextTableBuilder.hpp"

void tools::TextTableBuilder::setColumns(const std::vector<std::string> &columns)
{
    _columns = columns;
    _colWidths.resize(columns.size());
    for (size_t i = 0; i < columns.size(); ++i)
        _colWidths[i] = std::max(_colWidths[i], columns[i].size());
}

void  tools::TextTableBuilder::addRow(const std::vector<std::string> &row)
{
    _rows.push_back(row);
    for (size_t i = 0; i < row.size(); ++i)
        _colWidths[i] = std::max(_colWidths[i], row[i].size());
}

std::string  tools::TextTableBuilder::build() const
{
    std::ostringstream oss;

    auto formatRow = [&](const std::vector<std::string>& row) {
        for (size_t i = 0; i < row.size(); ++i)
            oss << std::left << std::setw(_colWidths[i] + 2) << row[i];
        oss << '\n';
    };

    formatRow(_columns);
    for (const auto& row : _rows)
        formatRow(row);

    return oss.str();
}
