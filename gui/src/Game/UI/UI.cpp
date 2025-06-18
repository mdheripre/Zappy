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
    _eventLog = std::make_unique<EventLog>(factory);
    _broadcast = std::make_unique<Broadcast>(factory);
    _TUDisplayer = std::make_unique<TimeUnitDisplayer>(factory);
    _trantInfo = std::make_unique<TrantorianInfoDisplayer>(factory);
    _trantInfo->setVisible(false);
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
    _TUDisplayer->draw();
    _trantInfo->draw();
    _canva->endUI();
}

void gui::UI::updateTeamInfo(const state::GameState &gm)
{
    _teamDisplayer->updateInfo(gm);
}

void gui::UI::addNewEvent(const std::string &event)
{
    _eventLog->pushEvent(event);
}

void gui::UI::addNewMessage(const std::string &message)
{
    _broadcast->pushEvent(message);
}

void gui::UI::updateTimeUnit(const float timeUnit, const float elasped)
{
    _TUDisplayer->setValues(timeUnit, elasped);
}

void gui::UI::setTrantInfo(const Trantorian &trant)
{
    _trantInfo->setVisible(true);
    _trantInfo->updateTrantorianInfo(trant);
}
