/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** BoundingBox.cpp
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

    Position3D<float> getSize() const;
    Position3D<float> getCenter() const;
    void merge(const BoundingBox& other);
};

}
