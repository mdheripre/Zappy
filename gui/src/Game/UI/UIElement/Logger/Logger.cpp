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
    const std::size_t maxHistory = 20;

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

    std::vector<std::string> wrappedLines = wrapEventsToLines(maxChars);
    limitLines(wrappedLines, maxLines);
    updateDisplayFromWrappedLines(wrappedLines);
}

std::vector<std::string> gui::Logger::wrapEventsToLines(int maxChars) const
{
    std::vector<std::string> wrapped;

    for (const auto& event : _events) {
        std::string line = computeLine(event, maxChars, wrapped);

        if (!line.empty()) wrapped.push_back(line);
        wrapped.push_back("");
    }
    return wrapped;
}

void gui::Logger::limitLines(std::vector<std::string>& lines, int maxLines) const
{
    while (static_cast<int>(lines.size()) > maxLines)
        lines.erase(lines.begin());
}

std::string gui::Logger::computeLine(const std::string &event,
    int maxChars,
    std::vector<std::string> &wrapped) const
{
    std::istringstream iss(event);
    std::string word;
    std::string line;

    while (iss >> word) {
        if (line.length() + word.length() + 1 > static_cast<size_t>(maxChars)) {
            wrapped.push_back(line);
            line = word;
        } else {
            if (!line.empty()) line += " ";
            line += word;
        }
    }
    return line;
}

void gui::Logger::updateDisplayFromWrappedLines(const std::vector<std::string>& lines) const
{
    std::ostringstream oss;
    oss << "  " << _title << "\n\n";
    for (const auto& line : lines)
        oss << line << '\n';

    _textDisplayer->setText(oss.str());
}

bool gui::Logger::update(float)
{
    return true;
}

void gui::Logger::draw() const
{
    if (!_textDisplayer || !_background || !_visible)
        return;

    _background->drawObject();
    _textDisplayer->drawObject();
}

