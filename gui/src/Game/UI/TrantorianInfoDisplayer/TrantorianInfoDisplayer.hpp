/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Logger.hpp
*/

#pragma once
#include "Game/UI/UIElement/TableDisplayer/TableDisplayer.hpp"
#include "Game/Renderer/Object/IAnimatedSprite.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Game/Trantorian/Trantorian.hpp"
#include <unordered_map>

namespace gui
{
    class TrantorianInfoDisplayer : public UIBox
    {
        public:
            TrantorianInfoDisplayer(render::IObjectFactory &factory);
            ~TrantorianInfoDisplayer() = default;
            bool update(float dt);
            void draw() const;
            void updateTrantorianInfo(std::shared_ptr<gui::TrantorianState> trantState, std::unique_ptr<render::IAnimatedSprite> visual);
        private:
            std::shared_ptr<gui::TrantorianState> _trantState;
            std::unique_ptr<TableDisplayer<2>> _inventory;
            std::unique_ptr<TableDisplayer<2>> _info;
            std::unique_ptr<render::IText> _currentAction;
            std::unique_ptr<render::IAnimatedSprite> _trantorianSprite;
    };
} // namespace gui
