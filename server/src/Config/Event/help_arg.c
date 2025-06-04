/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** help_arg.c
*/

#include "config.h"

void help_arg(void *ctx, void *)
{
    config_t *config = ctx;

    config->methods->help_message();
    config->exit = true;
}
