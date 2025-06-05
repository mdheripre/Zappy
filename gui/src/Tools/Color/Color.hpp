/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** HitRecord.cpp
*/

#pragma once
#include <iostream>

namespace tools
{
    class Color {
    public:
        Color() : r(0), g(0), b(0), a(1) {}
        Color(unsigned char red,
            unsigned char green,
            unsigned char blue,
            unsigned char alpha)
        : r(red), g(green), b(blue), a(alpha) {}
        
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

        Color& operator+=(const Color& o) {
            r += o.r;
            g += o.g;
            b += o.b;
            a += o.a;
            return *this;
        }
        Color operator+(const Color& o) {
            Color c;
        
            c.r = r + o.r;
            c.g = g + o.g;
            c.b = b + o.b;
            c.a = a + o.a;
            return c;
        }
        Color operator * (const Color& o) {
            Color c;
        
            c.r = r * o.r;
            c.g = g * o.g;
            c.b = b * o.b;
            c.a = a * o.a;
            return c;
        }
    };
    inline Color operator*(const Color& color, unsigned char scalar) {
        return Color(
            color.r * scalar,
            color.g * scalar,
            color.b * scalar,
            color.a
        );
    }
    inline Color operator*(unsigned char scalar, const Color& color) {
        return color * scalar;
    }
    inline Color operator/(const Color& color, unsigned char scalar) {
        if (scalar == 0.0f)
            throw std::runtime_error("Division by zero in Color operator/");
        return Color(
            color.r / scalar,
            color.g / scalar,
            color.b / scalar,
            color.a
        );
    }
    inline std::ostream& operator<<(std::ostream& os, const Color& color) {
        os << "Color(r=" << color.r
           << ", g=" << color.g
           << ", b=" << color.b
           << ", a=" << color.a << ")";
        return os;
    }
} // namespace Utils

