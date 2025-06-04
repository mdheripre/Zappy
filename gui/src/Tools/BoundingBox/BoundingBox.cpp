/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** BoundingBox.cpp
*/

#include "BoundingBox.hpp"

tools::Position3D<float> tools::BoundingBox::getSize() const {
    return tools::Position3D<float>(
        max.x - min.x,
        max.y - min.y,
        max.z - min.z
    );
}

tools::Position3D<float> tools::BoundingBox::getCenter() const{
    return {
        (min.x + max.x) / 2.0f,
        (min.y + max.y) / 2.0f,
        (min.z + max.z) / 2.0f
    };
}

void tools::BoundingBox::merge(const BoundingBox &other)
{
    min.x = fmin(min.x, other.min.x);
    min.y = fmin(min.y, other.min.y);
    min.z = fmin(min.z, other.min.z);
    max.x = fmax(max.x, other.max.x);
    max.y = fmax(max.y, other.max.y);
    max.z = fmax(max.z, other.max.z);
}