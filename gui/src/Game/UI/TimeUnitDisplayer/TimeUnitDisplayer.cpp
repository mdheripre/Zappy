#include "TimeUnitDisplayer.hpp"
#include <sstream>
#include <iomanip>


#include "TimeUnitDisplayer.hpp"
#include <sstream>
#include <iomanip>


gui::TimeUnitDisplayer::TimeUnitDisplayer(render::IObjectFactory &factory)
    : UIBox("Time Unit", 0.4f, 0.1f, 0.05f, 0.3f,
            factory.createText("gui/assets/Fonts/SpaceMono-Regular.ttf"),
            factory.createRectangle()),
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

    _progressBar->setRange(100.0f, 10000.0f);
    _progressBar->setValue(_timeUnit);
    _progressBar->setPosition({absPos.x + 10.f, absPos.y + absSize.y - 20.f});
    _progressBar->setSize({absSize.x - 20.f, 10.f});

    _valueText->setPosition({absPos.x + 10.f, absPos.y + 30.f});
    _valueText->setSize({absSize.x - 20.f, absSize.y - 20.f});
    updateText();
}

void gui::TimeUnitDisplayer::setValues(float timeUnit, float elapsed)
{
    _elapsed = elapsed;

    if (_timeUnit != timeUnit) {
        _timeUnit = timeUnit;
        _progressBar->setValue(_timeUnit);
    }
    updateText();
}

void gui::TimeUnitDisplayer::updateText()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Time Unit = " << _timeUnit << " | Elapsed = " << _elapsed;
    _valueText->setText(oss.str());
}

bool gui::TimeUnitDisplayer::update(float)
{
    return true;
}

void gui::TimeUnitDisplayer::draw() const
{
    UIBox::draw();
    if (_valueText)
        _valueText->drawObject();
    if (_progressBar)
        _progressBar->drawObject();
}