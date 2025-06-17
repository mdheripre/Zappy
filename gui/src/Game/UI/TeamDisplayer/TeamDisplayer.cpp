/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamDisplayer.cpp
*/

#include "TeamDisplayer.hpp"

gui::TeamDisplayer::TeamDisplayer(render::IObjectFactory &factory)
{
    _textDisplayer = factory.createText(fontPath);
    _background = factory.createRectangle();

    tools::Vector2<float> absPos(
        WIDTH_WINDOW * left,
        HEIGHT_WINDOW * top
    );
    tools::Vector2<float> absSize(
        WIDTH_WINDOW * width,
        HEIGHT_WINDOW * height
    );

    _background->setPosition(absPos);
    _background->setSize(absSize);

    _textDisplayer->setPosition(absPos);
    _textDisplayer->setSize(absSize);
}

void gui::TeamDisplayer::updateInfo(const std::vector<TeamInfo> &teamList)
{
    if (!_textDisplayer || !_background)
        return;

    tools::TextTableBuilder builder;
    builder.setColumns({"Name", "Players", "High", "Level 8", "Eggs"});
    
    for (const auto& team : teamList) {
        builder.addRow({
            team.teamName,
            std::to_string(team.nbPlayers),
            std::to_string(team.highLevel),
            std::to_string(team.nbPlayersLvl8),
            std::to_string(team.nbEggs)
        });
    }

    std::string finalText = _title + "\n\n" + builder.build();
    _textDisplayer->setText(finalText);
    _background->setSize(_textDisplayer->getSize());
    _background->setPosition(_textDisplayer->getPosition());
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

