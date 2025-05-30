/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Egg.hpp
*/

#pragma once

#include "Game/Renderer/IRenderEntity/IRenderEntity.hpp"
#include "Game/GameState/EntityState/EntityState.hpp"
#include <string>
#include <memory>
#include <iostream>

namespace gui {
    class Egg : public state::EntityState, public render::IRenderEntity {
    public:
        enum class EggAnimation {
            IDLE,
            HATCH,
            DIE
        };
        Egg(int id, tools::Position<int> pos, const std::string& teamName)
            : EntityState(id, pos, teamName) {}
        ~Egg() override = default;
    private:
        void setDead() override;
        void setPosition(tools::Position<int>  pos) override;
        bool update(float dt) override;
        void draw() const override;
    };
}
