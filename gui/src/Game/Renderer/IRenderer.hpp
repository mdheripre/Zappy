/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once
#include <memory>
#include "Game/Renderer/IRenderEntity/IRenderEntity.hpp"
#include "Game/Renderer/Camera/Camera.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Tools/Input/Input.hpp"
#include <functional>

namespace render
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;
        virtual void init(std::string title, int height, int width, int frameRate) = 0;
        virtual void update(float dt) = 0;
        virtual void render() = 0;
        virtual bool isClose() const = 0;
        virtual void pushEntity(std::shared_ptr<IRenderEntity> renderEntity) = 0;
        virtual void setBindings(std::unordered_map<tools::KeyCode, std::function<void()>>) = 0;
        virtual const IObjectFactory &getFactory() const = 0;
        virtual void poll() = 0;
    };
} // namespace gui
