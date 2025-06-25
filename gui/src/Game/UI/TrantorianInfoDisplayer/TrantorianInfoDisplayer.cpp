/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Logger.hpp
*/

#include "TrantorianInfoDisplayer.hpp"

namespace gui {

    /**
     * @brief Constructor that sets up the UI layout.
     * @param factory Object factory used to build all subcomponents.
     */
    TrantorianInfoDisplayer::TrantorianInfoDisplayer(render::IObjectFactory &factory)
    : UIBox("Trantorian Info",
        0.2f, 0.6f, 0.02f, 0.75f,
        factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
        factory.createRoundedRectangle(20))
{
    const float padding = 0.005f;
    const float titleHeight = 0.03f;

    float baseTop = _top + padding + titleHeight;
    float blockHeight = (_height - titleHeight - 3 * padding) / 3.f;

    _info = std::make_unique<TableDisplayer<2>>(
        "",
        _width - 2 * padding,
        blockHeight,
        baseTop,
        _left + padding,
        factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
        factory.createRectangle(),
        std::array<std::string, 2>{"", ""}
    );

    _inventory = std::make_unique<TableDisplayer<2>>(
        "Inventory",
        _width - 2 * padding,
        blockHeight,
        baseTop + blockHeight + padding + 0.04,
        _left + padding,
        factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
        factory.createRectangle(),
        std::array<std::string, 2>{"Item", "Qty"}
    );

    _currentAction = factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf");
    _currentAction->setText("Idle");
    _currentAction->setCharacterSize(20);
    tools::Vector2<float> absPos(
        (_left + padding) * WIDTH_WINDOW,
        (baseTop + 2 * (blockHeight + padding)) * HEIGHT_WINDOW + 160
    );
    _currentAction->setPosition(absPos);
}

/**
 * @brief Updates the display for the selected Trantorian.
 * If the Trantorian is dead, the display is hidden.
 * @param dt Delta time for animations.
 * @return True if still visible and valid.
 */
bool TrantorianInfoDisplayer::update(float dt)
{
    if (_trantorianSprite)
        _trantorianSprite->updateObject(dt);
    if (_visible && _trantState) {
        if (!_trantState->isAlive()) {
            _trantState = nullptr;
            _trantorianSprite = nullptr;
            _visible = false;
            return false;
        }
        _info->clear();
        _info->pushRow({"Id", std::to_string(_trantState->getId())});
        _info->pushRow({"Team", _trantState->getTeamName()});
        _info->pushRow({"Position",
            "("
            + std::to_string(_trantState->getPosition().x)
            + ","
            + std::to_string(_trantState->getPosition().y)
            + ")"});
        _info->pushRow({"Level", std::to_string(_trantState->getLevel())});
        _info->pushRow({"Orientation", _trantState->orientationToString(_trantState->getOrientation())});

        _inventory->clear();
        const auto &inv = _trantState->getInventory();
        std::array<std::string, 7> names = {
            "Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"
        };
        for (std::size_t i = 0; i < inv.size(); ++i)
            _inventory->pushRow({names[i], std::to_string(inv[i])});

        _currentAction->setText(_trantState->getCurrentAction());
        }
    return true;
}

/**
 * @brief Draws the info box, tables, and current action if visible.
 */
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

/**
 * @brief Sets the Trantorian to display and its animated visual.
 * @param trantState The selected Trantorian state.
 * @param visual A unique animated sprite to show.
 */
void TrantorianInfoDisplayer::updateTrantorianInfo(std::shared_ptr<gui::TrantorianState> trantState, std::unique_ptr<render::IAnimatedSprite> visual)
{
    const float padding = 0.005f;
    const float titleHeight = 0.03f;

    _trantState = trantState;
    visual->setPosition({WIDTH_WINDOW * _left, HEIGHT_WINDOW * _top + 20});
    visual->setSize(tools::Vector2<float>(150, 150));
    _trantorianSprite = std::move(visual);
}

} // namespace gui