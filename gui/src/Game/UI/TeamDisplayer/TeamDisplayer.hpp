/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamDisplayer.hpp
*/

#pragma once
#include "Game/Renderer/Object/IText.hpp"
#include "Game/Renderer/Object/IStaticSprite.hpp"
#include "Tools/AssetDefinition/AssetDefinition.hpp"
#include "Tools/Define.hpp"
#include "Game/Renderer/Entity/IRenderEntity.hpp"
#include "Tools/TextTableBuilder/TextTableBuilder.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Tools/Color/Color.hpp"
#include <memory>
#include <vector>
#include <array>
#include <cmath>

namespace gui
{
    class TeamDisplayer : public render::IRenderEntity
    {
        public:
            struct TeamInfo {
                std::string teamName;
                tools::Color color;
                int nbPlayers = 0;
                int highLevel = 0;
                int nbPlayersLvl8 = 0;
                int nbEggs = 0;
            };
            TeamDisplayer(render::IObjectFactory &factory);
            ~TeamDisplayer() = default;
            void updateInfo(const std::vector<TeamInfo> &teamList);
            bool update(float dt);
            void draw() const;

            private:
                const std::string fontPath = "gui/assets/Fonts/SpaceMono-Regular.ttf";
                std::unique_ptr<render::IText> _textDisplayer;
                std::unique_ptr<render::IObject> _background;
                const std::string _title = "Top 3";
                const std::array<std::string, 5> _columns = {"Name", "Players", "High", "Level 8", "Eggs"};
                const float height = 0.2f;
                const float width = 0.8f;
                const float top = 0.70f;
                const float left =  0.2f;
    };
}

