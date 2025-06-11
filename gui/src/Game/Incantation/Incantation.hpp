/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Incantation.hpp
*/

#pragma once
#include "Game/GameState/EntityState/EntityState.hpp"
#include "Game/Renderer/Object/IAnimatedSprite.hpp"
#include <vector>
#include <memory>
#include "Game/Renderer/IRenderEntity/IRenderEntity.hpp"
#include <iostream>

namespace gui {
    class IncantationState {
        public:
            IncantationState(tools::Vector2<int> pos,
                int level,
                const std::vector<int>& playerIds)
                : _position(pos), _targetLevel(level), _playerIds(playerIds) {}
            virtual ~IncantationState() = default;
            const tools::Vector2<int>& getPosition() const { return _position; }
            int getTargetLevel() const { return _targetLevel; }
            const std::vector<int>& getPlayerIds() const { return _playerIds; }
            virtual void succeed() = 0;
            virtual void failed() = 0;
        protected:
            tools::Vector2<int> _position;
            int _targetLevel;
            std::vector<int> _playerIds;
            bool _finished = false;
    };
    class Incantation : public render::IRenderEntity, public IncantationState
    {
        public:
            Incantation(tools::Vector2<int> pos,
                int level,
                const std::vector<int>& playerIds,
                std::unique_ptr<render::IAnimatedSprite> incObject = nullptr);
            ~Incantation() = default;
        private:
            std::unique_ptr<render::IAnimatedSprite> _incObject;
            void draw() const;
            bool update(float);
            void succeed();
            void failed();
    };    
}
    
