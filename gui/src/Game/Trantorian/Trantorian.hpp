/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Trantorian.hpp
*/

#pragma once

#include "Game/GameState/EntityState/EntityState.hpp"
#include "Game/Renderer/IRenderEntity/IRenderEntity.hpp"
#include "Tools/TeamBranding/TeamBranding.hpp"
#include "Game/Map/Tile/Tile.hpp"
#include "Game/Egg/Egg.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include <array>

namespace game {
    class TrantorianState : public EntityState {
        public:
            enum class Orientation {
                NORTH = 1,
                EAST = 2,
                SOUTH = 3,
                WEST = 4
            };
        
            TrantorianState(int id,
                tools::Position<int>  pos,
                const std::string& teamName,
                Orientation orientation = Orientation::NORTH)
                : EntityState(id, pos, teamName), _orientation(orientation), _level(1) {
                _inventory.fill(0);
            }
            virtual ~TrantorianState() = default;
        
            Orientation getOrientation() const { return _orientation; }
            int getLevel() const { return _level; }
            const std::array<int, 7>& getInventory() const { return _inventory; }
            virtual void setOrientation(Orientation ori) = 0;
            virtual void addToInventory(Tile::Resource res) = 0;
            virtual void setLevel(int lvl) = 0;
            virtual void setInventory(const std::array<int, 7>& inv) = 0;
            virtual void laidAnEgg() = 0;
            virtual void expulse() = 0;
            virtual void removeFromInventory(Tile::Resource res) = 0;
            virtual void broadcast(const std::string &msg) = 0;
            virtual void incantationFailed() = 0;
            virtual void incantationSucced() = 0;
        
        protected:
            Orientation _orientation;
            int _level;
            std::array<int, 7> _inventory;
        };
        
        class Trantorian : public TrantorianState, public IRenderEntity {
            public:
                enum class TrantorianAnimation {
                    IDLE,
                    WALK,
                    TALK,
                    INCANT,
                    DIE
                };
            
                Trantorian(int id,
                        tools::Position<int>  pos,
                           const std::string& teamName,
                           Orientation orientation = Orientation::NORTH,
                           int level = 1)
                    : TrantorianState(id, pos, teamName, orientation) {
                    _level = level;
                }
                ~Trantorian() override = default;
            private:
                void setDead() override { _alive = false; }
                void setPosition(tools::Position<int>  pos) override { _pos = pos; }
                void setOrientation(Orientation ori) override { _orientation = ori; }
                void setLevel(int lvl) override { _level = lvl; }
                void setInventory(const std::array<int, 7>& inv) override {_inventory = inv;};
                void laidAnEgg() {std::cout << "Laid an Egg not implemented" << std::endl;};
                void expulse() {std::cout << "Expulsion not implemented" << std::endl;}
                void incantationFailed() {std::cout << "Incantation failed not implemented" << std::endl;};
                void incantationSucced() {std::cout << "Incantation succeed not implemented" << std::endl;};
                void removeFromInventory(Tile::Resource res);
                void addToInventory(Tile::Resource res);
                void broadcast(const std::string &msg) {std::cout << "Brodcast from player " << _id << msg << std::endl;}
                bool update(float dt);
                void draw() const;
            };         
} // namespace game

