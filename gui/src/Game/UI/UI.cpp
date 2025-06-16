/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** UI.cpp
*/

#include "UI.hpp"

gui::UI::UI(render::IObjectFactory &factory)
{
    _canva = factory.createCanva();
    _teamDisplayer = std::make_unique<TeamDisplayer>(factory);
}

bool gui::UI::update(float dt)
{
    _teamDisplayer->update(dt);
    return true;
}

void gui::UI::draw() const {
    _canva->beginUI();
    _teamDisplayer->draw();
    _canva->endUI();
}

void gui::UI::updateTeamInfo(const state::GameState &gm)
{
    std::vector<gui::TeamDisplayer::TeamInfo> infos;

    for (auto &[teamName, tb] : gm.teams) {
        gui::TeamDisplayer::TeamInfo info;
        info.teamName = teamName;

        for (const auto& [_, t] : gm.trantorians) {
            if (t->getTeamName() == teamName) {
                info.nbPlayers++;
                if (t->getLevel() == 8)
                    info.nbPlayersLvl8++;
            }
        }
        for (const auto& [_, egg] : gm.eggs) {
            if (egg->getTeamName() == teamName)
                info.nbEggs++;
        }
        infos.push_back(info);
    }
    _teamDisplayer->updateInfo(infos);
}
