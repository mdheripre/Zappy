/*
** EPITECH PROJECT, 2025
** server
** File description:
** time
*/

#include <sys/time.h>
#include "utils.h"

long get_ms_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000L + tv.tv_usec / 1000L;
}
