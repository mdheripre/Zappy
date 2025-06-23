/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** UI.cpp
*/

#include "UI.hpp"

/**
 * @brief Constructs the main UI by initializing all UI components.
 * @param factory The object factory used to build renderable UI elements.
 */
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


/**
 * @brief Updates the UI components each frame.
 * @param dt Delta time since last frame.
 * @return Always returns true.
 */
bool gui::UI::update(float dt)
{
    _teamDisplayer->update(dt);
    if (_trantInfo->isVisible())
        _trantInfo->update(dt);
    return true;
}

/**
 * @brief Draws the UI components on screen, inside the UI view.
 */
void gui::UI::draw() const {
    _canva->beginUI();
    _teamDisplayer->draw();
    _eventLog->draw();
    _broadcast->draw();
    _TUDisplayer->draw();
    _trantInfo->draw();
    _canva->endUI();
}


/**
 * @brief Updates the displayed team information.
 * @param gm The current game state.
 */
void gui::UI::updateTeamInfo(const state::GameState &gm)
{
    _teamDisplayer->updateInfo(gm);
}

/**
 * @brief Adds a new string to the event log (bottom-left box).
 * @param event The event text to display.
 */
void gui::UI::addNewEvent(const std::string &event)
{
    _eventLog->pushEvent(event);
}

/**
 * @brief Adds a new message to the broadcast log (center box).
 * @param message The message text to display.
 */
void gui::UI::addNewMessage(const std::string &message)
{
    _broadcast->pushEvent(message);
}


/**
 * @brief Updates the time unit displayer with new values.
 * @param timeUnit The current time unit value.
 * @param elasped The time elapsed since the last server tick.
 */

void gui::UI::updateTimeUnit(const float timeUnit, const float elasped)
{
    _TUDisplayer->setValues(timeUnit, elasped);
}

/**
 * @brief Shows Trantorian details in the info box on the right.
 * @param trantState The selected Trantorian state.
 * @param visual A cloned animated sprite to represent the Trantorian.
 */
void gui::UI::setTrantInfo(const std::shared_ptr<gui::TrantorianState> trantState, std::unique_ptr<render::IAnimatedSprite> visual)
{
    _trantInfo->setVisible(true);
    _trantInfo->updateTrantorianInfo(trantState, std::move(visual));
}
