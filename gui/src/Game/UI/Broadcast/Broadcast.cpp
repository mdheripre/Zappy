/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Broadcast.cpp
*/

#include "Broadcast.hpp"

gui::Broadcast::Broadcast(render::IObjectFactory &factory, const std::string &title) : _title(title)
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
    pushEvent("");
}

void gui::Broadcast::pushEvent(const std::string &newEvent)
{
    constexpr std::size_t maxHistory = 100;
    _events.push_back(newEvent);
    if (_events.size() > maxHistory)
        _events.pop_front();

    const float boxWidth = WIDTH_WINDOW * width;
    const float boxHeight = HEIGHT_WINDOW * height;

    int maxChars = _textDisplayer->estimateMaxCharsPerLine(boxWidth);
    float lineHeight = _textDisplayer->getLineHeight();

    int maxLines = static_cast<int>(boxHeight / lineHeight) - 5;
    if (maxLines <= 0)
        return;

    std::vector<std::string> wrappedLines;
    for (const auto& event : _events) {
        std::istringstream iss(event);
        std::string word, line;

        while (iss >> word) {
            if (line.length() + word.length() + 1 > static_cast<size_t>(maxChars)) {
                wrappedLines.push_back(line);
                line = word;
            } else {
                if (!line.empty()) line += " ";
                line += word;
            }
        }
        if (!line.empty()) wrappedLines.push_back(line);
        wrappedLines.push_back("");
    }

    while (static_cast<int>(wrappedLines.size()) > maxLines)
        wrappedLines.erase(wrappedLines.begin());

    std::ostringstream oss;
    oss << _title << "\n\n";
    for (const auto& l : wrappedLines)
        oss << l << '\n';

    _textDisplayer->setText(oss.str());
}

bool gui::Broadcast::update(float)
{
    return true;
}

void gui::Broadcast::draw() const
{
    if (!_textDisplayer || !_background)
        return;

    _background->drawObject();
    _textDisplayer->drawObject();
}

