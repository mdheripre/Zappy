/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Renderer3D.cpp
*/

#pragma once
#include <string>
#include "Tools/Color/Color.hpp"
#include "Tools/AssetDefinition/AssetDefinition.hpp"

namespace tools
{
    class TeamBranding
    {
        public:
            TeamBranding(std::string teamName,
            Color color,
            tools::AssetDefinition playerAsset,
            tools::AssetDefinition incantationAsset,
            tools::AssetDefinition eggAsset)
            : _teamName(std::move(teamName)),
            _color(color),
            _playerAsset(std::move(playerAsset)),
            _incantationAsset(std::move(incantationAsset)),
            _eggAsset(std::move(eggAsset)) {}
            ~TeamBranding() = default;
            const std::string &getTeamName() const {return _teamName;};
            const Color &getColor() const {return _color;};
            const tools::AssetDefinition& getPlayerAsset() const { return _playerAsset; }
            const tools::AssetDefinition& getEggAsset() const { return _eggAsset; }
            const tools::AssetDefinition& getIncantationAsset() const { return _incantationAsset; }
        private:
            std::string _teamName;
            Color _color;
            tools::AssetDefinition _playerAsset;
            tools::AssetDefinition _incantationAsset;
            tools::AssetDefinition _eggAsset;
        };
} // namespace gui


