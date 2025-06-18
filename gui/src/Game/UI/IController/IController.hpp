/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** IController.hpp
*/

#pragma once
#include <memory>

namespace gui {
    class Trantorian;
    class Egg;
    class Tile;
}
namespace gui
{
    class ITrantorianUI {
    public:
        virtual ~ITrantorianUI() = default;
        virtual void setTrantInfo(const Trantorian & trant) = 0;
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
