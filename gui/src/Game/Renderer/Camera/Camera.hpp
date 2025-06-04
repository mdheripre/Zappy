/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once
#include "Tools/Position/Position.hpp"

namespace render {

class Camera {
private:
    tools::Position3D<float> _position;
    tools::Position3D<float> _target;
    tools::Position3D<float> _up;
    float _fov;
    int _projection;

public:
    Camera()
    : _position(5.f, 5.f, 5.f),
    _target(0.f, 0.f, 0.f),
    _up(0.f, 1.f, 0.f),
    _fov(45.f),
    _projection(0) {}

    ~Camera() = default;
    const tools::Position3D<float>& getPosition() const { return _position; }
    const tools::Position3D<float>& getTarget() const { return _target; }
    const tools::Position3D<float>& getUp() const { return _up; }
    float getFov() const { return _fov; }
    int getProjection() const { return _projection; }
    void setPosition(const tools::Position3D<float>& pos) { _position = pos; }
    void setTarget(const tools::Position3D<float>& target) { _target = target; }
    void setUp(const tools::Position3D<float>& up) { _up = up; }
    void setFov(float fov) { _fov = fov; }
    void setProjection(int projection) { _projection = projection; }
    void move(float dx, float dy, float dz) {
        _position.x += dx;
        _position.y += dy;
        _position.z += dz;
    }
    void lookAt(const tools::Position3D<float>& newTarget) {
        _target = newTarget;
    }
};

} // namespace render
