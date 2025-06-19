#include "SFMLProgressBar.hpp"

sfml::SFMLProgressBar::SFMLProgressBar(std::shared_ptr<sf::RenderWindow> rWindow)
    : _min(0.0f), _max(100.0f), _value(0.0f), _rWindow(rWindow)
{
    _background.setFillColor(sf::Color(100, 100, 100));
    _bar.setFillColor(sf::Color(0, 200, 0));
    _pos = {0.f, 0.f};
    _size = {100.f, 10.f};
    updateBar();
}

void sfml::SFMLProgressBar::setRange(float min, float max) {
    _min = min;
    _max = max;
    updateBar();
}

void sfml::SFMLProgressBar::setValue(float value) {
    _value = std::clamp(value, _min, _max);
    updateBar();
}

void sfml::SFMLProgressBar::setPosition(const tools::Vector2<float>& pos) {
    _pos = pos;
    _background.setPosition(pos.x, pos.y);
    updateBar();
}

void sfml::SFMLProgressBar::setSize(const tools::Vector2<float>& size) {
    _size = size;
    _background.setSize(sf::Vector2f(size.x, size.y));
    updateBar();
}

tools::Vector2<float> sfml::SFMLProgressBar::getPosition() const {
    return _pos;
}

tools::Vector2<float> sfml::SFMLProgressBar::getSize() const {
    return _size;
}

void sfml::SFMLProgressBar::drawObject() const {
    if (!_rWindow)
        return;
    _rWindow->draw(_background);
    _rWindow->draw(_bar);
}

void sfml::SFMLProgressBar::updateBar() {
    float percent = (_max - _min == 0) ? 0.f : (_value - _min) / (_max - _min);

    _bar.setPosition(_pos.x, _pos.y);
    _bar.setSize(sf::Vector2f(_size.x * percent, _size.y));
}

bool sfml::SFMLProgressBar::contains(tools::Vector2<float> position)
{
    return _background.getGlobalBounds().contains(sf::Vector2f(position.x, position.y));
}

void sfml::SFMLProgressBar::setColor(const tools::Color &color)
{
    auto luminance = [](const tools::Color& c) -> float {
        return 0.299f * c.r + 0.587f * c.g + 0.114f * c.b;
    };
    
    sf::Color baseColor(color.r, color.g, color.b, color.a);
    sf::Color contrastColor;
    
    if (luminance(color) > 200.f) {
        contrastColor = sf::Color(
            std::max(0, color.r - 60),
            std::max(0, color.g - 60),
            std::max(0, color.b - 60),
            color.a
        );
    } else {
        contrastColor = sf::Color(
            std::min(255, color.r + 60),
            std::min(255, color.g + 60),
            std::min(255, color.b + 60),
            color.a
        );
    }
    
    _background.setFillColor(contrastColor);
    _bar.setFillColor(baseColor);
}