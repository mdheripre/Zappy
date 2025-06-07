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
    REGISTER(self->dispatcher, "command_ia_Forward", handle_command_forward,
        NULL);
    REGISTER(self->dispatcher, "command_ia_Connect_nbr",
        handle_command_connect_nbr, server);
    REGISTER(self->dispatcher, "command_ia_Incantation",
        handle_command_incantation, server);
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
