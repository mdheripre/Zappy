/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once
#include <memory>
#include "Game/Renderer/Entity/IRenderEntity.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Tools/Input/Input.hpp"
#include <functional>

namespace render
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual void init(std::string title, int width, int height, int frameRate) = 0;
        virtual void update(float dt) = 0;
        virtual void updateUI(float dt) = 0;
        virtual void render() = 0;
        virtual bool isClose() const = 0;
        virtual void pushEntity(std::shared_ptr<IRenderEntity> renderEntity) = 0;
        virtual void setBindings(std::unordered_map<tools::KeyCode, std::function<void()>>) = 0;
        virtual void setPositionView(int offsetX, int offsetY) = 0;
        virtual void setZoomView(float factor) = 0;
        virtual void setUI(std::shared_ptr<IRenderEntity> ui) = 0;
        virtual IObjectFactory &getFactory() = 0;
        virtual void poll() = 0;
    };
} // namespace gui
