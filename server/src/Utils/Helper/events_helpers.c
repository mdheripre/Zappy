/*
** EPITECH PROJECT, 2025
** server
** File description:
** events_helpers
*/

#include "event.h"

/****************************************************************************/
/*                                                                          */
/*                          HELPER EVENT                                    */
/*                                                                          */
/****************************************************************************/

const char *event_type_name(event_type_t type,
    const event_type_map_entry_t *map, size_t map_size)
{
    for (size_t i = 0; i < map_size; ++i) {
        if (map[i].type == type)
            return map[i].name;
    }
    return "UNKNOWN_EVENT";
}

event_type_t event_type_from_string(const char *name,
    const event_type_map_entry_t *map, size_t map_size)
{
    for (size_t i = 0; i < map_size; ++i) {
        if (strcmp(map[i].name, name) == 0)
            return map[i].type;
    }
    return EVENT_TYPE_COUNT;
}
