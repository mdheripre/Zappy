/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Broadcast.hpp
*/

#pragma once

#include "Game/Renderer/Object/IText.hpp"
#include "Game/Renderer/Object/IStaticSprite.hpp"
#include "Tools/AssetDefinition/AssetDefinition.hpp"
#include "Tools/Define.hpp"
#include "Game/Renderer/Entity/IRenderEntity.hpp"
#include "Tools/TextTableBuilder/TextTableBuilder.hpp"
#include "Game/Renderer/ObjectFactory/IObjectFactory.hpp"
#include "Tools/Color/Color.hpp"
#include <memory>
#include <vector>
#include <array>
#include <cmath>
#include <deque>

namespace gui
{
    class Broadcast
    {
        public:
            Broadcast(render::IObjectFactory &factory, const std::string &title);
            ~Broadcast() = default;
            void pushEvent(const std::string &newEvent);
            bool update(float dt);
            void draw() const;
            const std::string fontPath = "gui/assets/Fonts/SpaceMono-Regular.ttf";
        private:
            std::unique_ptr<render::IText> _textDisplayer;
            std::unique_ptr<render::IObject> _background;
            std::deque<std::string> _events;
            const std::string _title;
            const float height = 0.6f;
            const float width = 0.2f;
            const float top = 0.08f;
            const float left =  0.79f;
    };
}
