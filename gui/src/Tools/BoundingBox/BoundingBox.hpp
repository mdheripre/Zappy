/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.cpp
*/

#pragma once

#include "Tools/Position/Position.hpp"
#include <cmath>

namespace tools {

class BoundingBox {
    public:
    Position3D<float> min;
    Position3D<float> max;

    BoundingBox() = default;
    BoundingBox(Position3D<float> min, Position3D<float> max) : min(min), max(max) {}

    Position3D<float> getSize() const {
        return {
            max.x - min.x,
            max.y - min.y,
            max.z - min.z
        };
    }

    Position3D<float> getCenter() const {
        return {
            (min.x + max.x) / 2.0f,
            (min.y + max.y) / 2.0f,
            (min.z + max.z) / 2.0f
        };
    }

    void merge(const BoundingBox& other) {
        min.x = fmin(min.x, other.min.x);
        min.y = fmin(min.y, other.min.y);
        min.z = fmin(min.z, other.min.z);

        max.x = fmax(max.x, other.max.x);
        max.y = fmax(max.y, other.max.y);
        max.z = fmax(max.z, other.max.z);
    }
};

}
