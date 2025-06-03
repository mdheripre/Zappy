/*
** EPITECH PROJECT, 2025
** Project
** File description:
** TeamBrandingManager.hpp
*/

#pragma once

#include <unordered_map>
#include <string>
#include <array>
#include "Tools/TeamBranding/TeamBranding.hpp"

namespace tools
{
    /**
     * @brief Manages visual branding for teams (color, player/egg assets).
     *
     * This class assigns a visual style (TeamBranding) to each team name.
     * If a team is not yet known, a default style is assigned from a
     * preset list and reused cyclically.
     */
    class TeamBrandingManager
    {
        
        public:
        
            TeamBrandingManager() = default;
            ~TeamBrandingManager() = default;
            
            /**
             * @brief Retrieves or assigns branding for a given team name.
             *
             * If the team name does not exist in the branding map, a default
             * branding is assigned from the preset list.
             *
             * @param teamName The name of the team.
             * @return A const reference to the TeamBranding associated with the team.
             */

            const TeamBranding& getTeamBranding(const std::string& teamName);

        private:
            std::unordered_map<std::string, TeamBranding> _brandMap;
            int _nextIndex = 0;
    
            const std::array<TeamBranding, 3> _presetBrandings = {
                //Example 1
                TeamBranding("default1", Color(255, 0, 0, 0),
                             AssetDefinition("player_red.glb", {{0, 1}, {1, 2}}, 1.0f),
                             AssetDefinition("egg_red.glb", {{0, 3}}, 0.7f)),
                //Example 2
                TeamBranding("default2", Color(0, 255, 0, 0),
                             AssetDefinition("player_green.glb", {{0, 1}}, 1.0f),
                             AssetDefinition("egg_green.glb", {{0, 2}}, 0.7f)),
                //Example 3
                TeamBranding("default3", Color(0, 0, 255, 0),
                             AssetDefinition("player_blue.glb", {{0, 1}}, 1.0f),
                             AssetDefinition("egg_blue.glb", {{0, 2}}, 0.7f))
            };
    };
} // namespace tools
