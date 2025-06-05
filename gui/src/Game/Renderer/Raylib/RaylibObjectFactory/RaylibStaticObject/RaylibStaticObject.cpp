/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibStaticObject.cpp
*/

#include "RaylibStaticObject.hpp"

namespace rl {

RaylibStaticObject::RaylibStaticObject(std::shared_ptr<render::IModel> model)
    : _model(std::move(model)) {}

void RaylibStaticObject::setPosition(const tools::Position3D<float>& pos)
{
    _position = pos;
}

const tools::Position3D<float>& RaylibStaticObject::getPosition() const
{
    return _position;
}

void RaylibStaticObject::drawObject() const
{
    _model->drawAt(_position);
}

const tools::BoundingBox& RaylibStaticObject::getBoundingBox() const
{
    return _model->getBoundingBox();
}
}
