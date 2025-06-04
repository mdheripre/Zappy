/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibAnimatedObject.cpp
*/

#include "RaylibAnimatedObject.hpp"
#include <algorithm>

namespace rl {

RaylibAnimatedObject::RaylibAnimatedObject(std::shared_ptr<render::IModel> model, float fps)
    : _model(std::move(model)), _frameRate(fps) {}

void RaylibAnimatedObject::setPosition(const tools::Position3D<float>& pos)
{
    _position = pos;
}

const tools::Position3D<float>& RaylibAnimatedObject::getPosition() const
{
    return _position;
}

void RaylibAnimatedObject::playClip(int clipIndex, bool loop)
{
    _currentAnim = clipIndex;
    _currentFrame = 0;
    _loop = loop;
    _time = 0.0f;
}

void RaylibAnimatedObject::setFrame(int frameIndex)
{
    _currentFrame = frameIndex;
    _model->applyAnimationFrame(_currentAnim, _currentFrame);
}

void RaylibAnimatedObject::updateObject(float dt)
{
    _time += dt;
    int frame = static_cast<int>(_time * _frameRate);
    setFrame(frame);
}

void RaylibAnimatedObject::drawObject() const
{
    _model->drawAt(_position);
}

const tools::BoundingBox &RaylibAnimatedObject::getBoundingBox() const {
    return _model->getBoundingBox();
}
}
