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
#include "Game/UI/TimeUnitDisplayer/TimeUnitDisplayer.hpp"
#include "Game/UI/TrantorianInfoDisplayer/TrantorianInfoDisplayer.hpp"
#include "Game/UI/Broadcast/Broadcast.hpp"
#include "Game/UI/EventLog/EventLog.hpp"
#include "Game/GameState/GameState.hpp"
#include "Game/UI/IController/IController.hpp"
#include <memory>
#include <algorithm>

namespace gui
{
    class UI : public render::IRenderEntity, public ITrantorianUI
    {
        public:
            UI(render::IObjectFactory &factory);
            ~UI() = default;
            void updateTeamInfo(const state::GameState &gm);
            void addNewEvent(const std::string &event);
            void addNewMessage(const std::string &message);
            void updateTimeUnit(const float timeUnit, const float elasped);
            void setTrantInfo(const std::shared_ptr<gui::TrantorianState> trantState, std::unique_ptr<render::IAnimatedSprite> visual);
            bool update(float dt);
            void draw() const;
        private:
            std::unique_ptr<render::ICanva> _canva;
            std::unique_ptr<TimeUnitDisplayer> _TUDisplayer;
            std::unique_ptr<EventLog> _eventLog;
            std::unique_ptr<Broadcast> _broadcast;
            std::unique_ptr<TeamDisplayer> _teamDisplayer;
            std::unique_ptr<TrantorianInfoDisplayer> _trantInfo;
    };
} // namespace gui
