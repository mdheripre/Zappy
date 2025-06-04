/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibModel.cpp
*/

#include "RaylibModel.hpp"

namespace rl {

RaylibModel::RaylibModel() = default;

RaylibModel::~RaylibModel()
{
    if (_animations)
        UnloadModelAnimations(_animations, _animationCount);
    if (_loaded)
        UnloadModel(_model);
}

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

const tools::BoundingBox &RaylibModel::getBoundingBox() const
{
    return _boundingBox;
}

void RaylibModel::applyAnimationFrame(int animIndex, int frameIndex)
{
    if (!_animations || animIndex >= _animationCount || animIndex < 0)
        return;

    const ModelAnimation& anim = _animations[animIndex];
    int frame = frameIndex % anim.frameCount;
    UpdateModelAnimation(_model, anim, frame);
}

void RaylibModel::drawAt(const tools::Position3D<float>& pos) const
{
    Vector3 rayPos = { pos.x, pos.y, pos.z };
    DrawModel(_model, rayPos, 1.0f, WHITE);
}

}
