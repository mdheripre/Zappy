/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** Position.hpp
*/

#pragma once
#include <unordered_map>

#pragma once
#include <cmath>

namespace tools {

template <typename T>
struct Position {
    T x, y;

    Position(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

template <typename T>
struct Position3D {
    T x, y, z;

    Position3D(T x_ = 0, T y_ = 0, T z_ = 0) : x(x_), y(y_), z(z_) {}

    bool operator==(const Position3D& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};
} // namespace tools

namespace std {
    template <>
    struct hash<tools::Position<int>> {
        std::size_t operator()(const tools::Position<int>& pos) const {
            return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
        }
    };
}    

