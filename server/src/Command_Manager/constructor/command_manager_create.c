/*
** EPITECH PROJECT, 2025
** server
** File description:
** command_manager_create
*/

#include "command_manager.h"

/****************************************************************************/
/*                                                                          */
/*                            CONSTRUCTOR                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Static constant holding function pointers for command manager
 * methods.
 *
 * Contains pointers to functions for registering all commands,
 * processing identification, and processing all commands.
 */
static const command_manager_methods_t COMMAND_MANAGER_METHODS = {
    .register_all = register_all,
    .process_identify = process_identify,
    .process_all = process_all
};

/**
 * @brief Creates and initializes a new command_manager_t instance.
 *
 * Allocates memory for a command manager, sets its methods and dispatcher.
 * Returns NULL if allocation fails.
 *
 * @return Pointer to the new command_manager_t, or NULL on failure.
 */
command_manager_t *command_manager_create(void)
{
    command_manager_t *manager = malloc(sizeof(command_manager_t));

    if (!manager)
        return NULL;
    manager->methods = &COMMAND_MANAGER_METHODS;
    manager->dispatcher = NEW(dispatcher, on_command_not_found);
    if (!manager->dispatcher)
        return NULL;
    return manager;
}
