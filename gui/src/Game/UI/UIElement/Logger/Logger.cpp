/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Logger.hpp
*/

#include "Logger.hpp"

gui::Logger::Logger(
    std::string title,
    float w,
    float h,
    float t,
    float l,
    std::unique_ptr<render::IText> textDisplayer,
    std::unique_ptr<render::IObject> background) 
    :UIBox(title, w, h, t, l, std::move(textDisplayer), std::move(background))
{}

void gui::Logger::pushEvent(const std::string &newEvent)
{
    constexpr std::size_t maxHistory = 100;
    _events.push_back(newEvent);
    if (_events.size() > maxHistory)
        _events.pop_front();

    const float boxWidth = WIDTH_WINDOW * _width;
    const float boxHeight = HEIGHT_WINDOW * _height;

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

bool gui::Logger::update(float)
{
    return true;
}

void gui::Logger::draw() const
{
    if (!_textDisplayer || !_background)
        return;

    _background->drawObject();
    _textDisplayer->drawObject();
}

