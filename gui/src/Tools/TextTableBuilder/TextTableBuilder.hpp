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
#include "Tools/Vector/Vector.hpp"

namespace tools
{
    class TextTableBuilder {
        public:
            TextTableBuilder() = default;
            ~TextTableBuilder() = default;
            void setColumns(const std::vector<std::string>& columns);
            void addRow(const std::vector<std::string>& row);
            std::string build() const;
            void clear();
        private:
            std::vector<std::string> _columns;
            std::vector<std::vector<std::string>> _rows;
            std::vector<size_t> _colWidths;
    };
} // namespace tools


