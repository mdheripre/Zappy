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
void register_all(command_manager_t *self)
{
    if (!self || !self->dispatcher)
        return;
    REGISTER(self->dispatcher, "command_ia_Forward", handle_command_forward,
        NULL);
}
