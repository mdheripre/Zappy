/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamBrandingManager.cpp
*/

#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

namespace tools
{
    class TextTableBuilder {
        public:
            TextTableBuilder() = default;
            ~TextTableBuilder() = default;
            void setColumns(const std::vector<std::string>& columns);
            void addRow(const std::vector<std::string>& row);
            std::string build() const;
        private:
            std::vector<std::string> _columns;
            std::vector<std::vector<std::string>> _rows;
            std::vector<size_t> _colWidths;
    };
} // namespace tools


