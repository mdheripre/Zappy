/*
** EPITECH PROJECT, 2025
** server
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_
    #include <stdio.h>
    #include <stdarg.h>
    #include <time.h>
    #define COLOR_INFO "\033[36m"
    #define COLOR_SUCCESS "\033[32m"
    #define COLOR_WARNING "\033[33m"
    #define COLOR_ERROR "\033[31m"
    #define COLOR_RESET "\033[0m"

typedef enum log_level_e {
    LOG_INFO,
    LOG_SUCCESS,
    LOG_WARNING,
    LOG_ERROR
} log_level_t;

void console_log(log_level_t level, const char *format, ...);
#endif /* !UTILS_H_ */
