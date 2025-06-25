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

/**
 * @brief Retrieves the name of an event type from a mapping table.
 *
 * @param type Event type to look up.
 * @param map Pointer to the event type mapping table.
 * @param map_size Number of entries in the mapping table.
 * @return String name of the event type, or "UNKNOWN_EVENT" if not found.
 */
const char *event_type_name(event_type_t type,
    const event_type_map_entry_t *map, size_t map_size)
{
    for (size_t i = 0; i < map_size; ++i) {
        if (map[i].type == type)
            return map[i].name;
    }
    return "UNKNOWN_EVENT";
}

/**
 * @brief Retrieves the event type matching a given name.
 *
 * @param name String name to look up.
 * @param map Pointer to the event type mapping table.
 * @param map_size Number of entries in the mapping table.
 * @return Matching event type, or EVENT_TYPE_COUNT if not found.
 */
event_type_t event_type_from_string(const char *name,
    const event_type_map_entry_t *map, size_t map_size)
{
    for (size_t i = 0; i < map_size; ++i) {
        if (strcmp(map[i].name, name) == 0)
            return map[i].type;
    }
    return EVENT_TYPE_COUNT;
}
