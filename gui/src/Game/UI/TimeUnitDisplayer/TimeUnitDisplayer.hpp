/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TimeUnitDisplayer.hpp
*/

#pragma once

#include "Game/UI/UIElement/UIBox/UIBox.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include <memory>

namespace gui {
    class TimeUnitDisplayer : public UIBox {
    public:
        TimeUnitDisplayer(render::IObjectFactory &factory);

        ~TimeUnitDisplayer() override = default;

        void setValues(float timeUnit, float elapsed);
        bool update(float dt) override;
        void draw() const override;

    private:
        float _timeUnit;
        float _elapsed;

        std::unique_ptr<render::IText> _valueText;
        std::unique_ptr<render::IProgressBar> _progressBar;
        void updateText();
    };
}