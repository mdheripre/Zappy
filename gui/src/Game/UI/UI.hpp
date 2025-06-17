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
#include "Game/UI/Broadcast/Broadcast.hpp"
#include "Game/UI/EventLog/EventLog.hpp"
#include "Game/GameState/GameState.hpp"
#include <memory>
#include <algorithm>

namespace gui
{
    class UI : public render::IRenderEntity
    {
        public:
            UI(render::IObjectFactory &factory);
            ~UI() = default;
            void updateTeamInfo(const state::GameState &gm);
            void addNewEvent(const std::string &event);
            void addNewMessage(const std::string &message);
            bool update(float dt);
            void draw() const;
        private:
            std::unique_ptr<render::ICanva> _canva;
            std::unique_ptr<EventLog> _eventLog;
            std::unique_ptr<Broadcast> _broadcast;
            std::unique_ptr<TeamDisplayer> _teamDisplayer;
    };
} // namespace gui
