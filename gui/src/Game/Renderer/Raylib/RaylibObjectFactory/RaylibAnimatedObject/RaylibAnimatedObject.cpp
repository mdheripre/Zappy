/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibAnimatedObject.cpp
*/

#include "RaylibAnimatedObject.hpp"
#include <algorithm>

namespace rl {

RaylibAnimatedObject::RaylibAnimatedObject(std::shared_ptr<render::IModel> model,
    std::unordered_map<int, int> animationMap,
    float fps)
    : _model(std::move(model)), _frameRate(fps), _animationMap(animationMap) {}

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
    auto it = _animationMap.find(clipIndex);
    if (it == _animationMap.end()) {
        throw std::runtime_error(
            "[RaylibAnimatedObject] Unknown animation logical ID: " + std::to_string(clipIndex));
            _currentAnim = 0;
    }
    if (it->second == -1)
        return;
    _currentAnim = it->second;
    _currentFrame = 0;
    _loop = loop;
    _time = 0.0f;
}

bool RaylibAnimatedObject::updateObject(float dt)
{
    _time += dt;

    int frameCount = _model->getAnimationFrameCount(_currentAnim);
    if (frameCount <= 0)
        return true;

    int frame = static_cast<int>(_time * _frameRate);

    if (_loop) {
        _currentFrame = frame % frameCount;
        return false;
    }

    if (frame >= frameCount) {
        _currentFrame = frameCount - 1;
        return true;
    } else {
        _currentFrame = frame;
        return false;
    }
}


void RaylibAnimatedObject::drawObject() const
{
    _model->applyAnimationFrame(_currentAnim, _currentFrame);
    _model->drawAt(_position);
}

const tools::BoundingBox &RaylibAnimatedObject::getBoundingBox() const {
    return _model->getBoundingBox();
}
}
