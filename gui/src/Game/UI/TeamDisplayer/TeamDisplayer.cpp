/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamDisplayer.cpp
*/

#include "TeamDisplayer.hpp"

gui::TeamDisplayer::TeamDisplayer(render::IObjectFactory &factory) :
    TeamDisplayer::TableDisplayer<5>(
        "Top 3",
        0.5f, 0.2f, 0.7f, 0.01f,
        factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
        factory.createRectangle(),
        std::array<std::string, 5> {"Name", "Players", "High", "Level 8", "Eggs"}
    ) {
        setCharaterSize(30);
    }

std::array<std::string, 5> gui::TeamDisplayer::buildTeamRow(const std::string &teamName, const state::GameState &gm)
{
    int nbPlayers = 0;
    int highLevel = 0;
    int nbPlayersLvl8 = 0;
    int nbEggs = 0;

    for (const auto& [_, t] : gm.trantorians) {
        if (t->getTeamName() == teamName) {
            nbPlayers++;
            if (t->getLevel() == 8)
                nbPlayersLvl8++;
            highLevel = std::max(highLevel, t->getLevel());
        }
    }

    for (const auto& [_, egg] : gm.eggs) {
        if (egg->getTeamName() == teamName)
            nbEggs++;
    }
    return {
        teamName,
        std::to_string(nbPlayers),
        std::to_string(highLevel),
        std::to_string(nbPlayersLvl8),
        std::to_string(nbEggs)
    };
}

bool gui::TeamDisplayer::sortFunction(const std::array<std::string, 5> &a, const std::array<std::string, 5> &b)
{
    int nbPlayersA = std::stoi(a[1]), nbPlayersB = std::stoi(b[1]);
    if (nbPlayersA != nbPlayersB)
        return nbPlayersA > nbPlayersB;

    int highLevelA = std::stoi(a[2]), highLevelB = std::stoi(b[2]);
    if (highLevelA != highLevelB)
        return highLevelA > highLevelB;

    int lvl8A = std::stoi(a[3]), lvl8B = std::stoi(b[3]);
    return lvl8A > lvl8B;
}

void gui::TeamDisplayer::sortTeamRow(std::vector<std::array<std::string, 5>> &rows, std::size_t maxCount)
{
    std::sort(rows.begin(), rows.end(), sortFunction);

    if (rows.size() > maxCount)
        rows.resize(maxCount);
}

void gui::TeamDisplayer::updateInfo(const state::GameState &gm)
{
    std::vector<std::array<std::string, 5>> rows;
    std::cout << "dez" << std::endl;


    for (const auto &[teamName, _] : gm.teams)
        rows.push_back(buildTeamRow(teamName, gm));

    sortTeamRow(rows, 3);

    clear();
    for (const auto& row : rows)
        pushRow(row);
    _background->setSize(_textDisplayer->getSize());
}

bool gui::TeamDisplayer::update(float)
{
    return true;
}

void gui::TeamDisplayer::draw() const
{
    if (!_textDisplayer || !_background)
        return;

    _background->drawObject();
    _textDisplayer->drawObject();
}
