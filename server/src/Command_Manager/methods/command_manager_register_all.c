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
static void register_gui_internal_command(command_manager_t *self,
    server_t *server)
{
    REGISTER(self->dispatcher, EVENT_GUI_PNW, handle_gui_pnw, server);
    REGISTER(self->dispatcher, EVENT_GUI_SBP, handle_gui_sbp, server);
    REGISTER(self->dispatcher, EVENT_GUI_ENW, handle_gui_enw, server);
    REGISTER(self->dispatcher, EVENT_GUI_EBO, handle_gui_ebo, server);
    REGISTER(self->dispatcher, EVENT_GUI_PEX, handle_gui_pex, server);
    REGISTER(self->dispatcher, EVENT_GUI_PBC, handle_gui_pbc, server);
    REGISTER(self->dispatcher, EVENT_GUI_PDI, handle_gui_pdi, server);
    REGISTER(self->dispatcher, EVENT_GUI_EDI, handle_gui_edi, server);
    REGISTER(self->dispatcher, EVENT_GUI_PDR, handle_gui_pdr, server);
    REGISTER(self->dispatcher, EVENT_GUI_PGT, handle_gui_pgt, server);
    REGISTER(self->dispatcher, EVENT_GUI_SEG, handle_gui_seg, server);
    REGISTER(self->dispatcher, EVENT_GUI_PFK, handle_gui_pfk, server);
    REGISTER(self->dispatcher, EVENT_GUI_PIC, handle_gui_pic, server);
    REGISTER(self->dispatcher, EVENT_GUI_PIE, handle_gui_pie, server);
    REGISTER(self->dispatcher, EVENT_GUI_PIN, handle_gui_pin, server);
    REGISTER(self->dispatcher, EVENT_GUI_PLV, handle_gui_plv, server);
    REGISTER(self->dispatcher, EVENT_GUI_PPO, handle_gui_ppo, server);
    REGISTER(self->dispatcher, EVENT_GUI_PMV, handle_gui_pmv, server);
    REGISTER(self->dispatcher, EVENT_GUI_PEJ, handle_gui_pej, server);
}

/**
 * @brief Register GUI commands to the dispatcher.
 *
 * @param self Pointer to the command manager.
 * @param server Pointer to the server instance.
 */
static void register_gui_command(command_manager_t *self, server_t *server)
{
    REGISTER(self->dispatcher, CMD_GUI_MSZ, handle_command_gui_msz, server);
    REGISTER(self->dispatcher, CMD_GUI_SGT, handle_command_gui_sgt, server);
    REGISTER(self->dispatcher, CMD_GUI_BCT, handle_command_gui_bct, server);
    REGISTER(self->dispatcher, CMD_GUI_TNA, handle_command_gui_tna, server);
    REGISTER(self->dispatcher, CMD_GUI_MCT, handle_command_gui_mct, server);
    REGISTER(self->dispatcher, CMD_GUI_PPO, handle_command_gui_ppo, server);
    REGISTER(self->dispatcher, CMD_GUI_PLV, handle_command_gui_plv, server);
    REGISTER(self->dispatcher, CMD_GUI_PIN, handle_command_gui_pin, server);
    REGISTER(self->dispatcher, CMD_GUI_SST, handle_command_gui_sst, server);
    register_gui_internal_command(self, server);
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
    REGISTER(self->dispatcher, CMD_IA_EJECT, handle_command_eject, server);
    REGISTER(self->dispatcher, CMD_IA_FORK, handle_command_fork, server);
    REGISTER(self->dispatcher, CMD_IA_BROADCAST, handle_command_broadcast,
        server);
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
    REGISTER(self->dispatcher, CMD_IA_FORWARD, handle_command_forward, server);
    REGISTER(self->dispatcher, CMD_IA_RIGHT, handle_command_right, server);
    REGISTER(self->dispatcher, CMD_IA_LEFT, handle_command_left, server);
    REGISTER(self->dispatcher, CMD_IA_CONNECT_NBR, handle_command_connect_nbr,
        server);
    REGISTER(self->dispatcher, CMD_IA_INCANTATION, handle_command_incantation,
        server);
    REGISTER(self->dispatcher, CMD_IA_LOOK, handle_command_look, server);
    REGISTER(self->dispatcher, CMD_IA_INVENTORY, handle_command_inventory,
        server);
    REGISTER(self->dispatcher, CMD_IA_TAKE, handle_command_take, server);
    REGISTER(self->dispatcher, CMD_IA_SET, handle_command_drop, server);
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
static void register_process_response_extend(command_manager_t *self,
    server_t *server)
{
    REGISTER(self->dispatcher, EVENT_RESP_EGG_DIE, on_response_egg_die,
        server);
    REGISTER(self->dispatcher, EVENT_RESP_BROADCAST, on_response_broadcast,
        server);
    REGISTER(self->dispatcher, EVENT_RESP_TILE_UPDATED,
        on_response_tile_updated, server);
    REGISTER(self->dispatcher, EVENT_RESP_DROP, on_response_drop, server);
    REGISTER(self->dispatcher, EVENT_RESP_TAKE, on_response_take, server);
    REGISTER(self->dispatcher, EVENT_RESP_BROADCAST_TO_GUI, handle_gui_pbc,
        server);
    REGISTER(self->dispatcher, EVENT_RESP_PLAYER_EAT, on_response_player_eat,
        server);
}

/**
 * @brief Register response handlers to the dispatcher.
 *
 * @param self Pointer to the command manager.
 * @param server Pointer to the server instance.
 */
static void register_process_response(command_manager_t *self,
    server_t *server)
{
    REGISTER(self->dispatcher, EVENT_RESP_PLAYER_MOVED,
        on_response_player_moved, server);
    REGISTER(self->dispatcher, EVENT_RESP_PLAYER_DIED,
        on_response_player_died, server);
    REGISTER(self->dispatcher, EVENT_RESP_CONNECT_NBR,
        on_response_connect_nbr, server);
    REGISTER(self->dispatcher, EVENT_RESP_LOOK, on_response_look, server);
    REGISTER(self->dispatcher, EVENT_RESP_INVENTORY,
        on_response_inventory, server);
    REGISTER(self->dispatcher, EVENT_RESP_PLAYER_EJECTED,
        on_response_eject, server);
    REGISTER(self->dispatcher, EVENT_RESP_PLAYER_OWNER_EJECTED,
        on_response_eject, server);
    REGISTER(self->dispatcher, EVENT_RESP_EGG_LAID,
        on_response_egg_laid, server);
    REGISTER(self->dispatcher, EVENT_RESP_START_INCANTATION,
        on_response_start_incantation, server);
    REGISTER(self->dispatcher, EVENT_RESP_END_INCANTATION,
        on_response_end_incantation, server);
    register_process_response_extend(self, server);
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
