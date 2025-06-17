/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamDisplayer.hpp
*/

#pragma once
#include "Game/UI/UIElement/TableDisplayer/TableDisplayer.hpp"
#include "Game/GameState/GameState.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include <algorithm>

namespace gui
{
    class TeamDisplayer : public gui::TableDisplayer<5>
    {
        public:
            TeamDisplayer(render::IObjectFactory &factory);
            ~TeamDisplayer() = default;
            void updateInfo(const state::GameState &gm);
            bool update(float dt);
            void draw() const;
        private:
            void sortTeamRow(std::vector<std::array<std::string, 5>> &rows, std::size_t maxCount);
            std::array<std::string, 5> buildTeamRow(const std::string &teamName, const state::GameState &gm);
            static bool sortFunction(const std::array<std::string, 5> &a, const std::array<std::string, 5> &b);
    };
}
