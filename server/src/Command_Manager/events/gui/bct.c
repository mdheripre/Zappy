/*
** EPITECH PROJECT, 2025
** server
** File description:
** bct
*/

#include "command_manager.h"

/****************************************************************************/
/*                                                                          */
/*                            COMMAND GUI                                   */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Format the content of a tile as a "bct" command string.
 *
 * @param tile Pointer to the tile to format.
 * @return Newly allocated string representing the tile, or NULL on failure.
 */
static char *format_tile_bct(const tile_t *tile)
{
    char buffer[BUFFER_COMMAND_SIZE];

    if (!tile)
        return NULL;
    snprintf(buffer, sizeof(buffer),
        "bct %d %d %d %d %d %d %d %d %d\n",
        tile->x, tile->y,
        tile->resources[0], tile->resources[1], tile->resources[2],
        tile->resources[3], tile->resources[4], tile->resources[5],
        tile->resources[6]);
    return strdup(buffer);
}

/**
 * @brief Parse les coordonnées d'une commande BCT.
 *
 * @param args La string contenant les arguments (ex: "3 5").
 * @param x Pointeur pour stocker X.
 * @param y Pointeur pour stocker Y.
 * @return true si les coordonnées sont valides, false sinon.
 */
static bool parse_bct_coords(const char *args, int *x, int *y)
{
    char *end = NULL;

    if (!args || !x || !y)
        return false;
    *x = strtol(args, &end, 10);
    if (!end || *end != ' ')
        return false;
    *y = strtol(end + 1, NULL, 10);
    return true;
}

/**
 * @brief Envoie la réponse BCT pour une tuile spécifique au client GUI.
 *
 * @param server Le serveur.
 * @param client Le client GUI.
 * @param tile La tuile à envoyer.
 */
static void emit_bct_response(server_t *server, client_t *client, tile_t *tile)
{
    response_payload_t *payload = malloc(sizeof(response_payload_t));

    if (!server || !client || !tile || !payload)
        return;
    payload->client = client;
    payload->message = format_tile_bct(tile);
    if (!payload->message) {
        free(payload);
        return;
    }
    EMIT(server->dispatcher, "send_response", payload);
}

/**
 * @brief Gère la commande BCT pour un client GUI.
 *
 * @param ctx Pointeur vers le serveur.
 * @param data Pointeur vers le client GUI.
 */
void handle_command_gui_bct(void *ctx, void *data)
{
    server_t *server = ctx;
    client_t *client = data;
    const char *args = NULL;
    int x = 0;
    int y = 0;

    if (!server || !client || !server->game)
        return;
    args = extract_command_args(client_peek_command(client)->content);
    if (!parse_bct_coords(args, &x, &y))
        return EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
    if (x < 0 || y < 0 || x >= server->game->width ||
        y >= server->game->height)
        return EMIT(server->command_manager->dispatcher, "gui_sbp", NULL);
    emit_bct_response(server, client, &server->game->map[y][x]);
}
