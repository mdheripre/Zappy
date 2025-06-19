/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IController.hpp
*/

#pragma once
#include <memory>

namespace gui {
    class TrantorianState;
    class EggState;
    class Tile;
}
namespace gui
{
    class ITrantorianUI {
    public:
        virtual ~ITrantorianUI() = default;
        virtual void setTrantInfo(std::shared_ptr<gui::TrantorianState> trantState, std::unique_ptr<render::IAnimatedSprite> visual) = 0;
    };
    
/*     class IEggUI {
    public:
        virtual void setEgg(std::shared_ptr<gui::Egg>) = 0;
        virtual ~IEggUI() = default;
    };
    
    class ITileUI {
    public:
        virtual void setTile(const gui::Tile&) = 0;
        virtual ~ITileUI() = default;
    };
     */
} // namespace gui
