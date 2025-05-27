/*
** EPITECH PROJECT, 2025
** server
** File description:
** print_log
*/

#include "utils.h"

/****************************************************************************/
/*                                                                          */
/*                                CONSOLE LOG                               */
/*                                                                          */
/****************************************************************************/

/**
 * LOG_COLORS - Array mapping log levels to their corresponding color codes.
 * Each index corresponds to a log level (LOG_INFO, LOG_SUCCESS, etc.)
 * and holds the ANSI color code string for that level.
 */

static const char *LOG_COLORS[] = {
    [LOG_INFO] = COLOR_INFO,
    [LOG_SUCCESS] = COLOR_SUCCESS,
    [LOG_WARNING] = COLOR_WARNING,
    [LOG_ERROR] = COLOR_ERROR
};

/**
 * LOG_LABELS - Array of string labels for log message types.
 * Maps log level enums (LOG_INFO, LOG_SUCCESS, LOG_WARNING, LOG_ERROR)
 * to their corresponding string representations.
 */

static const char *LOG_LABELS[] = {
    [LOG_INFO] = "INFO",
    [LOG_SUCCESS] = "SUCCESS",
    [LOG_WARNING] = "WARNING",
    [LOG_ERROR] = "ERROR"
};

/**
 * @brief Logs a formatted message to stderr with timestamp and log level.
 *
 * @param level The log level to use (index for LOG_COLORS and LOG_LABELS).
 * @param format The printf-style format string.
 * @param ... Arguments for the format string.
 */

void console_log(log_level_t level, const char *format, ...)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_buf[9];
    va_list args;

    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info);
    fprintf(stderr, "%s[%s] [%s] ", LOG_COLORS[level], time_buf,
        LOG_LABELS[level]);
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "%s\n", COLOR_RESET);
}
