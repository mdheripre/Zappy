/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** help_message.c
*/

#include <unistd.h>

/****************************************************************************/
/*                                                                          */
/*                            HELPER METHODS                                */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Prints the help message listing all available command-line options.
 *
 * This function is called when the user provides the -h, --help or -help
 * flag. It outputs the usage information and describes each argument.
 */
void help_message(void)
{
    write(1, "USAGE: ./zappy_server -p port -x width -y height "
        "-n name1 name2 ... -c clientsNb -f freq\n\n", 91);
    write(1, "OPTIONS:\n", 9);
    write(1, "\t-h\t\t\tDisplay this help message\n", 32);
    write(1, "\t-p port\t\t\tSet the port number\n", 31);
    write(1, "\t-x width\t\tSet the world width\n", 31);
    write(1, "\t-y height\t\tSet the world height\n", 33);
    write(1, "\t-n name1 name2 ...\tSet the team names (at least 2)\n", 52);
    write(1, "\t-c clientsNb\t\tSet the number of clients per team\n", 50);
    write(1, "\t-f freq\t\t\tSet the server frequency\n", 36);
}
