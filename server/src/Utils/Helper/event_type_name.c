/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** event_type_name
*/

#include "game.h"

/**
 * @brief Gets the name of an event type.
 *
 * Searches the EVENT_TYPE_MAP array for the given type and returns its
 * associated name. Returns "UNKNOWN" if the type is not found.
 *
 * @param type The event type to resolve.
 * @return String name of the event type, or "UNKNOWN".
 */
const char *event_type_name(game_event_type_t type)
{
    for (size_t i = 0;
        i < sizeof(EVENT_TYPE_MAP) / sizeof(EVENT_TYPE_MAP[0]); i++) {
        if (EVENT_TYPE_MAP[i].type == type)
            return EVENT_TYPE_MAP[i].name;
    }
    return "UNKNOWN";
}
