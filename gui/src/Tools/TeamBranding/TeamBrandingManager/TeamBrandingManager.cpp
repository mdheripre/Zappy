/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** TeamBrandingManager.cpp
*/

#include "TeamBrandingManager.hpp"

namespace tools {

    const TeamBranding& TeamBrandingManager::getTeamBranding(const std::string& teamName) {
        auto it = _brandMap.find(teamName);

        if (it != _brandMap.end())
            return it->second;
    
        const TeamBranding& branding = _presetBrandings[_nextIndex % _presetBrandings.size()];
        _nextIndex++;
    
        _brandMap.emplace(teamName, TeamBranding(
            teamName,
            branding.getColor(),
            branding.getPlayerAsset(),
            branding.getEggAsset()
        ));
    
        return _brandMap.at(teamName);
    }
    
    } // namespace tools