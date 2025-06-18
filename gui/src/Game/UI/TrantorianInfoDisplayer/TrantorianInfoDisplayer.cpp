/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Logger.hpp
*/

#include "TrantorianInfoDisplayer.hpp"

namespace gui {

    TrantorianInfoDisplayer::TrantorianInfoDisplayer(render::IObjectFactory &factory)
    : UIBox("Trantorian Info",
        0.2f, 0.4f, 0.2f, 0.8f,
        factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
        factory.createRectangle())
{
    const float padding = 0.005f;
    const float titleHeight = 0.06f;

    float baseTop = _top + titleHeight + padding;
    float blockHeight = (_height - titleHeight - 3 * padding) / 3.f;

    _info = std::make_unique<TableDisplayer<2>>(
        "Info",
        _width - 2 * padding,
        blockHeight,
        baseTop,
        _left + padding,
        factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
        factory.createRectangle(),
        std::array<std::string, 2>{"Key", "Value"}
    );

    _inventory = std::make_unique<TableDisplayer<2>>(
        "Inventory",
        _width - 2 * padding,
        blockHeight,
        baseTop + blockHeight + padding,
        _left + padding,
        factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
        factory.createRectangle(),
        std::array<std::string, 2>{"Item", "Qty"}
    );

    _currentAction = factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf");
    _currentAction->setText("Idle");

    tools::Vector2<float> absPos(
        (_left + padding) * WIDTH_WINDOW,
        (baseTop + 2 * (blockHeight + padding)) * HEIGHT_WINDOW
    );
    _currentAction->setPosition(absPos);
}

bool TrantorianInfoDisplayer::update(float dt)
{
    if (_trantorianSprite)
        _trantorianSprite->updateObject(dt);
    return true;
}

void TrantorianInfoDisplayer::draw() const
{
    if (!_visible)
        return;

    UIBox::draw();

    if (_info)
        _info->draw();
    if (_inventory)
        _inventory->draw();
    if (_currentAction)
        _currentAction->drawObject();
    if (_trantorianSprite)
        _trantorianSprite->drawObject();
}

void TrantorianInfoDisplayer::updateTrantorianInfo(const Trantorian &trant)
{
    _info->clear();
    _info->pushRow({"Level", std::to_string(trant.getLevel())});
    _info->pushRow({"Orientation", std::to_string(static_cast<int>(trant.getOrientation()))});

    _inventory->clear();
    const auto &inv = trant.getInventory();
    std::array<std::string, 7> names = {
        "Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"
    };
    for (std::size_t i = 0; i < inv.size(); ++i)
        _inventory->pushRow({names[i], std::to_string(inv[i])});

    if (auto sprite = trant.getVisual()) {
        sprite->setPosition({50.f, 200.f});
        _trantorianSprite = std::move(sprite);
    }

    _currentAction->setText("Current Action : Idle");
}

} // namespace gui