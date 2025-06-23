/*
** EPITECH PROJECT, 2025
** server
** File description:
** event
*/

#ifndef EVENT_H_
    #define EVENT_H_
    #include <stddef.h>
    #include <string.h>


typedef enum event_type_e {
    // --- Core CLI arguments (config_t based)
    EVENT_ARG_PORT,
    EVENT_ARG_WIDTH,
    EVENT_ARG_HEIGHT,
    EVENT_ARG_TEAM_NAME,
    EVENT_ARG_TEAM_SIZE,
    EVENT_ARG_FREQUENCY,
    EVENT_ARG_HELP_SHORT,
    EVENT_ARG_HELP_LONG,
    EVENT_ARG_HELP_ALT,
    EVENT_ARG_DEBUG_SHORT,
    EVENT_ARG_DEBUG_LONG,

    // --- Game logic events (used in game loop / dispatcher)
    EVENT_PLAYER_MOVED,
    EVENT_PLAYER_DIED,
    EVENT_CONNECT_NBR,
    EVENT_LOOK_AROUND,
    EVENT_CHECK_INVENTORY,
    EVENT_PLAYER_EJECT,
    EVENT_EGG_LAID,
    EVENT_START_INCANTATION,
    EVENT_END_INCANTATION,
    EVENT_BROADCAST_MESSAGE,
    EVENT_PLAYER_DROP_ITEM,
    EVENT_PLAYER_TAKE_ITEM,

    // --- Server internal control events
    EVENT_CLIENT_CONNECTED,
    EVENT_CLIENT_IDENTIFY,
    EVENT_SEND_RESPONSE,
    EVENT_GUI_INIT,
    EVENT_IA_INIT,

    // --- GUI events (from protocol)
    EVENT_GUI_PNW,
    EVENT_GUI_SBP,
    EVENT_GUI_ENW,
    EVENT_GUI_EBO,
    EVENT_GUI_PEX,
    EVENT_GUI_PBC,
    EVENT_GUI_PDI,
    EVENT_GUI_EDI,
    EVENT_GUI_PDR,
    EVENT_GUI_PGT,
    EVENT_GUI_SEG,
    EVENT_GUI_PFK,
    EVENT_GUI_PIC,
    EVENT_GUI_PIE,
    EVENT_GUI_PIN,
    EVENT_GUI_PLV,
    EVENT_GUI_PPO,
    EVENT_GUI_PEJ,
    EVENT_GUI_PMV,

    // --- GUI command events
    CMD_GUI_MSZ,
    CMD_GUI_SGT,
    CMD_GUI_BCT,
    CMD_GUI_TNA,
    CMD_GUI_MCT,
    CMD_GUI_PPO,
    CMD_GUI_PLV,
    CMD_GUI_PIN,
    CMD_GUI_SST,

    // --- AI command events
    CMD_IA_FORWARD,
    CMD_IA_RIGHT,
    CMD_IA_LEFT,
    CMD_IA_CONNECT_NBR,
    CMD_IA_INCANTATION,
    CMD_IA_LOOK,
    CMD_IA_INVENTORY,
    CMD_IA_TAKE,
    CMD_IA_SET,
    CMD_IA_EJECT,
    CMD_IA_FORK,
    CMD_IA_BROADCAST,

    // --- Response events (sent to clients)
    EVENT_RESP_PLAYER_MOVED,
    EVENT_RESP_PLAYER_DIED,
    EVENT_RESP_CONNECT_NBR,
    EVENT_RESP_LOOK,
    EVENT_RESP_INVENTORY,
    EVENT_RESP_PLAYER_EJECTED,
    EVENT_RESP_PLAYER_OWNER_EJECTED,
    EVENT_RESP_EGG_LAID,
    EVENT_RESP_START_INCANTATION,
    EVENT_RESP_END_INCANTATION,
    EVENT_RESP_EGG_DIE,
    EVENT_RESP_BROADCAST,
    EVENT_RESP_TILE_UPDATED,
    EVENT_RESP_DROP,
    EVENT_RESP_TAKE,
    EVENT_RESP_BROADCAST_TO_GUI,
    EVENT_RESP_PLAYER_EAT,

    EVENT_TYPE_COUNT
} event_type_t;

typedef struct {
    const char *name;
    event_type_t type;
} event_type_map_entry_t;

static const event_type_map_entry_t EVENT_CLI_MAP[] = {
    {"-p", EVENT_ARG_PORT},
    {"-x", EVENT_ARG_WIDTH},
    {"-y", EVENT_ARG_HEIGHT},
    {"-n", EVENT_ARG_TEAM_NAME},
    {"-c", EVENT_ARG_TEAM_SIZE},
    {"-f", EVENT_ARG_FREQUENCY},
    {"-h", EVENT_ARG_HELP_SHORT},
    {"--help", EVENT_ARG_HELP_LONG},
    {"-help", EVENT_ARG_HELP_ALT},
    {"-d", EVENT_ARG_DEBUG_SHORT},
    {"--debug", EVENT_ARG_DEBUG_LONG},
};

static const event_type_map_entry_t EVENT_CMD_NAME[] = {
    {"command_gui_msz", CMD_GUI_MSZ},
    {"command_gui_sgt", CMD_GUI_SGT},
    {"command_gui_bct", CMD_GUI_BCT},
    {"command_gui_tna", CMD_GUI_TNA},
    {"command_gui_mct", CMD_GUI_MCT},
    {"command_gui_ppo", CMD_GUI_PPO},
    {"command_gui_plv", CMD_GUI_PLV},
    {"command_gui_pin", CMD_GUI_PIN},
    {"command_gui_sst", CMD_GUI_SST},

    {"command_ia_Forward", CMD_IA_FORWARD},
    {"command_ia_Right", CMD_IA_RIGHT},
    {"command_ia_Left", CMD_IA_LEFT},
    {"command_ia_Connect_nbr", CMD_IA_CONNECT_NBR},
    {"command_ia_Incantation", CMD_IA_INCANTATION},
    {"command_ia_Look", CMD_IA_LOOK},
    {"command_ia_Inventory", CMD_IA_INVENTORY},
    {"command_ia_Take", CMD_IA_TAKE},
    {"command_ia_Set", CMD_IA_SET},
    {"command_ia_Eject", CMD_IA_EJECT},
    {"command_ia_Fork", CMD_IA_FORK},
    {"command_ia_Broadcast", CMD_IA_BROADCAST},
};

const char *event_type_name(event_type_t type,
    const event_type_map_entry_t *map, size_t map_size);
event_type_t event_type_from_string(const char *name,
    const event_type_map_entry_t *map, size_t map_size);
#endif /* !EVENT_H_ */
