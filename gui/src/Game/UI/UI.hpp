/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** UI.hpp
*/

#pragma once
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Game/Renderer/Entity/IRenderEntity.hpp"
#include "Game/Renderer/Object/ICanva.hpp"
#include "Game/UI/TeamDisplayer/TeamDisplayer.hpp"
#include "Game/GameState/GameState.hpp"
#include <memory>

namespace gui
{
    class UI : public render::IRenderEntity
    {
        public:
            UI(render::IObjectFactory &factory);
            ~UI() = default;
            void updateTeamInfo(const state::GameState &gm);
            bool update(float dt);
            void draw() const;
        private:
            std::unique_ptr<render::ICanva> _canva;
            std::unique_ptr<TeamDisplayer> _teamDisplayer;
    };
} // namespace gui
