/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibModel.cpp
*/

#include "RaylibModel.hpp"

namespace rl {

RaylibModel::RaylibModel() = default;

/**
 * @brief Destructor for RaylibModel.
 *
 * Frees the model and its animations from memory if they were loaded.
 */
RaylibModel::~RaylibModel()
{
    if (_animations)
        UnloadModelAnimations(_animations, _animationCount);
    if (_loaded)
        UnloadModel(_model);
}

/**
 * @brief Loads a 3D model and its animations from a file.
 *
 * Also computes the overall bounding box for all meshes in the model.
 *
 * @param path Path to the model file.
 */
void RaylibModel::loadFromFile(const std::string& path)
{
    _model = LoadModel(path.c_str());
    _loaded = true;

    _animations = LoadModelAnimations(path.c_str(), &_animationCount);
    if (_animationCount == 0)
        _animations = nullptr;
        
    BoundingBox bb = GetMeshBoundingBox(_model.meshes[0]);
    Vector3 min = bb.min;
    Vector3 max = bb.max;
    for (int i = 1; i < _model.meshCount; ++i) {
        BoundingBox b = GetMeshBoundingBox(_model.meshes[i]);
        min.x = fmin(min.x, b.min.x);
        min.y = fmin(min.y, b.min.y);
        min.z = fmin(min.z, b.min.z);
        max.x = fmax(max.x, b.max.x);
        max.y = fmax(max.y, b.max.y);
        max.z = fmax(max.z, b.max.z);
    }

    _boundingBox = tools::BoundingBox(tools::Position3D<float>(min.x, min.y, min.z),
        tools::Position3D<float>(max.x, max.y, max.z));
}

/**
 * @brief Returns the computed bounding box for the model.
 *
 * @return A reference to the bounding box.
 */
const tools::BoundingBox &RaylibModel::getBoundingBox() const
{
    return _boundingBox;
}

/**
 * @brief Returns the number of animation frames for a given animation index.
 *
 * @param animIndex Index of the animation.
 * @return Number of frames in the animation.
 * @throw RenderError if the animation index is invalid.
 */
int RaylibModel::getAnimationFrameCount(int animIndex) const
{
    if (!_animations || animIndex < 0 || animIndex >= _animationCount) {
        throw RenderError("[RaylibModel] Invalid animation index");
    }
    return _animations[animIndex].frameCount;
}

/**
 * @brief Applies a specific frame of an animation to the model.
 *
 * If the frame index exceeds the frame count, it wraps around.
 *
 * @param animIndex Animation index to apply.
 * @param frameIndex Frame index to apply.
 */
void RaylibModel::applyAnimationFrame(int animIndex, int frameIndex)
{
    if (!_animations || animIndex >= _animationCount || animIndex < 0)
        return;

    const ModelAnimation& anim = _animations[animIndex];
    int frame = frameIndex % anim.frameCount;
    UpdateModelAnimation(_model, anim, frame);
}

/**
 * @brief Draws the model at a specified 3D position.
 *
 * Uses a scale of 1.0 and white color tint.
 *
 * @param pos World position to draw the model at.
 */
void RaylibModel::drawAt(const tools::Position3D<float>& pos) const
{
    Vector3 rayPos = { pos.x, pos.y, pos.z };
    DrawModel(_model, rayPos, 1.0f, WHITE);
}

}
