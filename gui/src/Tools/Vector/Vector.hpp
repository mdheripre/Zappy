/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** Position.hpp
*/

#pragma once
#include <unordered_map>

namespace tools {

template <typename T>
class Vector2 {
    public:
    T x;
    T y;

    Vector2(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator*(T scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    Vector2 operator*(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y);

    }
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};
} // namespace tools

namespace std {
    template <>
    struct hash<tools::Vector2<int>> {
        std::size_t operator()(const tools::Vector2<int>& pos) const {
            return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
        }
    };
}    

