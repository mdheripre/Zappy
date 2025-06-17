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
    _eventLog = std::make_unique<EventLog>(factory, "Event Log");
    _broadcast = std::make_unique<Broadcast>(factory, "Broadcast");
}

bool gui::UI::update(float dt)
{
    _teamDisplayer->update(dt);
    return true;
}

void gui::UI::draw() const {
    _canva->beginUI();
    _teamDisplayer->draw();
    _eventLog->draw();
    _broadcast->draw();
    _canva->endUI();
}

void gui::UI::updateTeamInfo(const state::GameState &gm)
{
    std::vector<gui::TeamDisplayer::TeamInfo> infos;

    for (auto &[teamName, tb] : gm.teams) {
        gui::TeamDisplayer::TeamInfo info;
        info.teamName = teamName;
        info.color = tb.getColor();

        for (const auto& [_, t] : gm.trantorians) {
            if (t->getTeamName() == teamName) {
                info.nbPlayers++;
                if (t->getLevel() == 8)
                    info.nbPlayersLvl8++;
                if (t->getLevel() > info.highLevel)
                    info.highLevel = t->getLevel();
            }
        }

        for (const auto& [_, egg] : gm.eggs) {
            if (egg->getTeamName() == teamName)
                info.nbEggs++;
        }

        infos.push_back(info);
    }

    std::sort(infos.begin(), infos.end(), [](const auto &a, const auto &b) {
        if (a.nbPlayers != b.nbPlayers)
            return a.nbPlayers > b.nbPlayers;
        if (a.highLevel != b.highLevel)
            return a.highLevel > b.highLevel;
        return a.nbPlayersLvl8 > b.nbPlayersLvl8;
    });

    if (infos.size() > 3)
        infos.resize(3); // Ne garder que le top 3

    _teamDisplayer->updateInfo(infos);
}

void gui::UI::addNewEvent(const std::string &event)
{
    _eventLog->pushEvent(event);
}

void gui::UI::addNewMessage(const std::string &message)
{
    _broadcast->pushEvent(message);
}
