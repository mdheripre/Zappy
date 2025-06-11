/*
** EPITECH PROJECT, 2025
** server
** File description:
** command_manager_register_all
*/

#include "command_manager.h"
#include "shared.h"

/****************************************************************************/
/*                                                                          */
/*                            GUI COMMAND                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Register GUI commands to the dispatcher.
 *
 * @param self Pointer to the command manager.
 * @param server Pointer to the server instance.
 */
static void register_gui_command(command_manager_t *self, server_t *server)
{
    REGISTER(self->dispatcher, "command_gui_msz", handle_command_gui_msz,
        server);
    REGISTER(self->dispatcher, "command_gui_sgt", handle_command_gui_sgt,
        server);
    REGISTER(self->dispatcher, "command_gui_bct", handle_command_gui_bct,
        server);
    REGISTER(self->dispatcher, "command_gui_tna", handle_command_gui_tna,
        server);
    REGISTER(self->dispatcher, "command_gui_mct", handle_command_gui_mct,
        server);
}

/****************************************************************************/
/*                                                                          */
/*                     IA HANDLER COMMAND                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Register IA commands to the dispatcher.
 *
 * @param self Pointer to the command manager.
 * @param server Pointer to the server instance.
 */
static void extend_register_handler_ia_command(command_manager_t *self,
    server_t *server)
{
    REGISTER(self->dispatcher, "command_ia_Eject", handle_command_eject,
        server);
    REGISTER(self->dispatcher, "command_ia_Fork", handle_command_fork,
        server);
    REGISTER(self->dispatcher, "command_ia_Broadcast",
        handle_command_broadcast, server);
}

/**
 * @brief Register IA commands to the dispatcher.
 *
 * @param self Pointer to the command manager.
 * @param server Pointer to the server instance.
 */
static void register_handler_ia_command(command_manager_t *self,
    server_t *server)
{
    REGISTER(self->dispatcher, "command_ia_Forward", handle_command_forward,
        server);
    REGISTER(self->dispatcher, "command_ia_Right", handle_command_right,
        server);
    REGISTER(self->dispatcher, "command_ia_Left", handle_command_left,
        server);
    REGISTER(self->dispatcher, "command_ia_Connect_nbr",
        handle_command_connect_nbr, server);
    REGISTER(self->dispatcher, "command_ia_Incantation",
        handle_command_incantation, server);
    REGISTER(self->dispatcher, "command_ia_Look", handle_command_look,
        server);
    REGISTER(self->dispatcher, "command_ia_Inventory",
        handle_command_inventory, server);
    REGISTER(self->dispatcher, "command_ia_Take", handle_command_take,
        server);
    REGISTER(self->dispatcher, "command_ia_Set", handle_command_drop,
        server);
    extend_register_handler_ia_command(self, server);
}

/****************************************************************************/
/*                                                                          */
/*                      IA RESPONSE COMMAND                                 */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Register response handlers to the dispatcher.
 *
 * @param self Pointer to the command manager.
 * @param server Pointer to the server instance.
 */
static void register_process_response(command_manager_t *self,
    server_t *server)
{
    REGISTER(self->dispatcher, "RESPONSE_PLAYER_MOVED",
        on_response_player_moved, server);
    REGISTER(self->dispatcher, "RESPONSE_PLAYER_DIED",
        on_response_player_died, server);
    REGISTER(self->dispatcher, "RESPONSE_CONNECT_NBR",
        on_response_connect_nbr, server);
    REGISTER(self->dispatcher, "RESPONSE_LOOK",
        on_response_look, server);
    REGISTER(self->dispatcher, "RESPONSE_INVENTORY",
        on_response_inventory, server);
    REGISTER(self->dispatcher, "RESPONSE_PLAYER_EJECTED",
        on_response_eject, server);
    REGISTER(self->dispatcher, "RESPONSE_EGG_LAID",
        on_response_egg_laid, server);
    REGISTER(self->dispatcher, "RESPONSE_START_INCANTATION",
        on_response_start_incantation, server);
    REGISTER(self->dispatcher, "RESPONSE_END_INCANTATION",
        on_response_end_incantation, server);
}

/****************************************************************************/
/*                                                                          */
/*                          REGISTER COMMAND                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Registers all available commands with the server's dispatcher.
 *
 * @param server Pointer to the server structure.
 */
void register_all(command_manager_t *self, server_t *server)
{
    if (!self || !self->dispatcher)
        return;
    register_gui_command(self, server);
    register_handler_ia_command(self, server);
    register_process_response(self, server);
}
