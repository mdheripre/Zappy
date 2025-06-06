/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibAnimatedObject.cpp
*/

#include "RaylibAnimatedObject.hpp"
#include <algorithm>

namespace rl {

/**
 * @brief Constructs a RaylibAnimatedObject.
 *
 * @param model Model to be animated.
 * @param animationMap Mapping between animation clip indices and actual frame sets.
 * @param fps Playback speed of the animation (default: 24).
 */
RaylibAnimatedObject::RaylibAnimatedObject(std::shared_ptr<render::IModel> model,
    std::unordered_map<int, int> animationMap,
    float fps)
    : _model(std::move(model)), _frameRate(fps), _animationMap(animationMap) {}

/**
 * @brief Sets the world position of the animated object.
 *
 * @param pos 3D position in the scene.
 */
void RaylibAnimatedObject::setPosition(const tools::Position3D<float>& pos)
{
    _position = pos;
}

/**
 * @brief Gets the current position of the object.
 *
 * @return 3D position.
 */
const tools::Position3D<float>& RaylibAnimatedObject::getPosition() const
{
    return _position;
}

/**
 * @brief Starts playing a specific animation clip.
 *
 * @param clipIndex Logical clip index defined in the animation map.
 * @param loop Whether the animation should loop.
 * @throw std::runtime_error if the clip index is invalid.
 */

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

/**
 * @brief Updates the animation frame based on delta time.
 *
 * Advances the animation if it's playing. Handles looping and end conditions.
 *
 * @param dt Time in seconds since the last update.
 * @return true if animation finished (for non-looped), false otherwise.
 */
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

/**
 * @brief Draws the object at its current position and frame.
 *
 * Applies the animation frame and renders the model.
 */
void RaylibAnimatedObject::drawObject() const
{
    _model->applyAnimationFrame(_currentAnim, _currentFrame);
    _model->drawAt(_position);
}

/**
 * @brief Returns the bounding box of the model.
 *
 * @return Bounding box used for spatial queries or rendering bounds.
 */
const tools::BoundingBox &RaylibAnimatedObject::getBoundingBox() const
{
    return _model->getBoundingBox();
}
}
