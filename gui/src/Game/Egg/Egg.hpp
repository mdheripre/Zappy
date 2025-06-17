/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#pragma once

#include "Game/Renderer/IRenderEntity/IRenderEntity.hpp"
#include "Game/GameState/EntityState/EntityState.hpp"
#include "Game/Renderer/Object/IAnimatedSprite.hpp"
#include "Tools/Define.hpp"
#include <string>
#include <memory>
#include <iostream>

namespace gui {
    class Egg : public state::EntityState, public render::IRenderEntity {
    public:
        enum class EggAnimation {
            IDLE,
            DIE
        };
        Egg(int id, tools::Vector2<int> pos, const std::string& teamName, std::unique_ptr<render::IAnimatedSprite> eggObject = nullptr);
        ~Egg() override = default;
    private:
        std::unique_ptr<render::IAnimatedSprite> _eggObject;
        void setDead() override;
        void setPosition(tools::Vector2<int>  pos) override;
        bool update(float dt) override;
        void draw() const override;
    };
}
