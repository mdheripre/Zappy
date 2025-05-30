/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** Position.hpp
*/

#pragma once
#include <unordered_map>

namespace tools {
    template<typename T>
    class Position {
        public:
            T x;
            T y;
            Position(T x_, T y_) : x(x_), y(y_) {}
            ~Position() = default;
            bool operator==(const Position& other) const {
                return x == other.x && y == other.y;
            }
    };
}
namespace std {
    template <>
    struct hash<tools::Position<int>> {
        std::size_t operator()(const tools::Position<int>& pos) const {
            return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
        }
    };
}    

