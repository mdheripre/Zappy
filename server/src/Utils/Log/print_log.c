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
 * debug_state - Manages the debug state of the server.
 *
 * This function allows setting or getting the current debug state.
 * If DEBUG_GET, returns the current debug state without changing it.
 * Otherwise, it sets the debug state to the provided value.
 *
 * @param state The new debug state to set, or DEBUG_GET to retrieve state.
 * @return The current debug state after setting or retrieving it.
 */
debug_state_t debug_state(debug_state_t state)
{
    static debug_state_t debug = DEBUG_ON;

    debug = (state != DEBUG_GET) ? state : debug;
    return debug;
}

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

    if (debug_state(DEBUG_GET) != DEBUG_ON)
        return;
    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", tm_info);
    fprintf(stderr, "%s[%s] [%s] ", LOG_COLORS[level], time_buf,
        LOG_LABELS[level]);
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "%s\n", COLOR_RESET);
}
