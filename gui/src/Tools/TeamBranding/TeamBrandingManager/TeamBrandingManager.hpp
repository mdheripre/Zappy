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
#include "Game/Trantorian/Trantorian.hpp"

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
    
            const std::array<TeamBranding, 1> _presetBrandings = {
                //Team Starmie
                TeamBranding(
                    "Starmie", 
                    Color(255, 0, 0, 0),
                    //Trantorian Asset
                    AssetDefinition(
                        //Model Path
                        "gui/src/Asset/Trantorian/scene.gltf",
                        // Animation Mapping
                        {
                            {static_cast<int>(gui::Trantorian::TrantorianAnimation::DIE), 12},
                            {static_cast<int>(gui::Trantorian::TrantorianAnimation::IDLE), 0},
                            {static_cast<int>(gui::Trantorian::TrantorianAnimation::INCANT), 3}, // if there is no animation available
                            {static_cast<int>(gui::Trantorian::TrantorianAnimation::TALK), -1},
                            {static_cast<int>(gui::Trantorian::TrantorianAnimation::WALK), 8},
                        },
                        // Scaling to apply
                        0.2f
                    ),
                    //Incantation Asset
                    AssetDefinition(
                        //Model Path
                        "gui/src/Asset/Incantation/Magic_ring/scene.gltf",
                        //Animation Mapping
                        {
        
                        },
                        //Scaling to apply
                        0.7f
                    ),
                    //Egg Asset
                    AssetDefinition(
                        //Model Path
                        "gui/src/Asset/Egg/SharkSquid/scene.gltf",
                        //Animation Mapping
                        {

                        },
                        //Scaling to Apply
                        0.2f
                    )
                )
            };
    };
} // namespace tools
