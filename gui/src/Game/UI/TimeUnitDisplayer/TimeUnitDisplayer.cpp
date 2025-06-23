#include "TimeUnitDisplayer.hpp"
#include <sstream>
#include <iomanip>


#include "TimeUnitDisplayer.hpp"
#include <sstream>
#include <iomanip>

/**
 * @brief Constructor for the TimeUnitDisplayer UI box.
 * @param factory Object factory to build text and UI components.
 */
gui::TimeUnitDisplayer::TimeUnitDisplayer(render::IObjectFactory &factory)
    : UIBox("", 0.4f, 0.1f, 0.05f, 0.3f,
            factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
            factory.createRoundedRectangle(20)),
      _timeUnit(1.0f),
      _elapsed(0.0f),
      _valueText(factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf")),
      _progressBar(factory.createProgressBar())
{
    tools::Vector2<float> absPos(
        WIDTH_WINDOW * _left,
        HEIGHT_WINDOW * _top
    );
    tools::Vector2<float> absSize(
        WIDTH_WINDOW * _width,
        HEIGHT_WINDOW * _height
    );

    _progressBar->setRange(1.0f, 1000.0f);
    _progressBar->setValue(_timeUnit);
    _progressBar->setPosition({absPos.x + 10.f, absPos.y + absSize.y - 20.f});
    _progressBar->setSize({absSize.x - 20.f, 10.f});

    _valueText->setPosition({absPos.x + 10.f, absPos.y + 30.f});
    _valueText->setSize({absSize.x - 20.f, absSize.y - 20.f});
    updateText();
}

/**
 * @brief Updates the values to be displayed.
 * @param timeUnit Current time unit.
 * @param elapsed Elapsed time since last tick.
 */
void gui::TimeUnitDisplayer::setValues(float timeUnit, float elapsed)
{
    _elapsed = elapsed;

    if (_timeUnit != timeUnit) {
        _timeUnit = timeUnit;
        _progressBar->setValue(_timeUnit);
    }
    updateText();
}


/**
 * @brief Rebuilds the display text based on internal values.
 */
void gui::TimeUnitDisplayer::updateText()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Time Unit = " << _timeUnit << " | Elapsed = " << _elapsed;
    _valueText->setText(oss.str());
}

/**
 * @brief Logic update function.
 * @return Always true, placeholder for render loop compatibility.
 */
bool gui::TimeUnitDisplayer::update(float)
{
    return true;
}

/**
 * @brief Draws the UI box, the progress bar, and time text.
 */
void gui::TimeUnitDisplayer::draw() const
{
    if (!_visible)
        return;
    UIBox::draw();
    if (_valueText)
        _valueText->drawObject();
    if (_progressBar)
        _progressBar->drawObject();
}