/*
** EPITECH PROJECT, 2025
** server
** File description:
** time
*/

#include <sys/time.h>
#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                                 TIME                                     */
/*                                                                          */
/****************************************************************************/

/**
 * @brief Returns the current time in milliseconds.
 *
 * Uses `gettimeofday` to retrieve the current time, then converts it to
 * milliseconds since the Unix epoch.
 *
 * @return Current time in milliseconds as a long integer.
 */
long get_ms_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000L + tv.tv_usec / 1000L;
}
