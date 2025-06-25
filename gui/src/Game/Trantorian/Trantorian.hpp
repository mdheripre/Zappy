/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.hpp
*/

#pragma once

#include "Game/GameState/EntityState/EntityState.hpp"
#include "Game/Renderer/Entity/IRenderEntity.hpp"
#include "Game/Renderer/Object/IAnimatedSprite.hpp"
#include "Tools/TeamBranding/TeamBranding.hpp"
#include "Game/Renderer/Entity/AInteractiveEntity.hpp"
#include "Game/UI/IController/IController.hpp"
#include "Game/Map/Tile/Tile.hpp"
#include "Game/Egg/Egg.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include <array>

namespace gui {
    class TrantorianState : public state::EntityState {
        public:
            enum class Orientation {
                NORTH = 1,
                EAST = 2,
                SOUTH = 3,
                WEST = 4
            };
        const std::array<std::string, 5> _orientationString = {"", "NORTH", "EAST", "SOUTH", "WEST"};
            TrantorianState(int id,
                tools::Vector2<int>  pos,
                const std::string& teamName,
                Orientation orientation = Orientation::NORTH)
                : EntityState(id, pos, teamName), _orientation(orientation), _level(1) {
                _inventory.fill(0);
            }
            virtual ~TrantorianState() = default;
            Orientation getOrientation() const { return _orientation; }
            virtual int getLevel() const {return _level; }
            const std::array<int, 7>& getInventory() const { return _inventory; }
            const std::string &getCurrentAction() {return _currentAction;};
            std::string orientationToString(Orientation O) {return _orientationString[static_cast<int>(O)];};
            virtual void setOrientation(Orientation ori) = 0;
            virtual void addToInventory(gui::Tile::Resource res) = 0;
            virtual void setLevel(int lvl) = 0;
            virtual void setInventory(const std::array<int, 7>& inv) = 0;
            virtual void laidAnEgg() = 0;
            virtual void expulse() = 0;
            virtual void setForward(bool value) = 0;
            virtual void expulseFrom(Orientation O, int maxWidth, int maxHeight) = 0;
            virtual void removeFromInventory(Tile::Resource res) = 0;
            virtual void broadcast(const std::string &msg) = 0;
            virtual void startIncantation() = 0;
            virtual void incantationFailed() = 0;
            virtual void incantationSucced() = 0;
        protected:
            Orientation _orientation;
            std::string _currentAction = "";
            int _level;
            std::array<int, 7> _inventory;
            bool _forward = false;
        };
        
        class Trantorian : public TrantorianState,
            public render::IRenderEntity,
            public render::AInteractiveEntity,
            public std::enable_shared_from_this<Trantorian> {
            public:
                enum class TrantorianAnimation {
                    IDLE = 0,
                    EJECT_NORTH,
                    EJECT_EAST,
                    EJECT_SOUTH,
                    EJECT_WEST,
                    WALK_NORTH,
                    WALK_EAST,
                    WALK_SOUTH,
                    WALK_WEST,
                };
                Trantorian(int id,
                        tools::Vector2<int>  pos,
                           const std::string& teamName,
                           Orientation orientation = Orientation::NORTH,
                           int level = 1,
                           std::unique_ptr<render::IAnimatedSprite> trantorianObject = nullptr,
                           std::shared_ptr<ITrantorianUI> uiController = nullptr);
                ~Trantorian() override = default;
            private:
                std::shared_ptr<ITrantorianUI> _uiController;
                std::unique_ptr<render::IAnimatedSprite> _trantorianObject;
                void setDead() override { _alive = false; }
                void setPosition(tools::Vector2<int>  pos) override;
                void setOrientation(Orientation ori) override { _orientation = ori; }
                void setLevel(int lvl) override { _level = lvl; }
                void setInventory(const std::array<int, 7>& inv) override {_inventory = inv;};
                void laidAnEgg();
                void expulse();
                void expulseFrom(Orientation O, int maxWidth, int maxHeight);
                void incantationFailed() {std::cout << "Incantation failed not implemented" << std::endl;};
                void incantationSucced() {std::cout << "Incantation succeed not implemented" << std::endl;};
                void removeFromInventory(Tile::Resource res);
                void addToInventory(Tile::Resource res);
                void startIncantation();
                void broadcast(const std::string &msg) {std::cout << "Brodcast from player " << _id << ": "<< msg << std::endl;}
                void forwardAnimation(float dt);
                bool update(float dt);
                void draw() const;
                bool isMouseOver(const tools::Vector2<float>& mousePosition) const;
                void onHoverEnter() override;
                void onHoverExit() override;
                void onClick();
                void setForward(bool value);
                tools::Vector2<float> orientationToVector(Orientation o);
            };         
} // namespace game
