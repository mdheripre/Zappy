/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** RaylibStaticObject.cpp
*/

#pragma once
#include "Game/Renderer/Object/IStaticObject.hpp"
#include "Game/Renderer/Object/IModel.hpp"
#include <memory>

namespace rl
{
    class RaylibStaticObject : public render::IStaticObject
    {
    private:
        std::shared_ptr<render::IModel> _model;
        tools::Position3D<float> _position;

    public:
        explicit RaylibStaticObject(std::shared_ptr<render::IModel> model);
        ~RaylibStaticObject() override = default;

        void setPosition(const tools::Position3D<float>& pos) override;
        const tools::Position3D<float>& getPosition() const override;
        const tools::BoundingBox& getBoundingBox() const override;
        void drawObject() const override;
    };
}
