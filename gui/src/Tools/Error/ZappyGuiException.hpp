/*
** EPITECH PROJECT, 2025
** Project
** File description:
** ZappyGuiException.hpp
*/

#pragma once

#include <stdexcept>
#include <string>

/**
 * @brief Base exception class for all Zappy GUI-related errors.
 */
class ZappyGuiException : public std::runtime_error {
public:
    explicit ZappyGuiException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @brief Exception thrown for rendering-related issues.
 */
class RenderException : public ZappyGuiException {
public:
    explicit RenderException(const std::string& message)
        : ZappyGuiException("[Render] " + message) {}
};

/**
 * @brief Exception thrown when a command is invalid or unrecognized.
 */
class CommandException : public ZappyGuiException {
public:
    explicit CommandException(const std::string& message)
        : ZappyGuiException("[Command] " + message) {}
};

/**
 * @brief Exception thrown for data parsing issues (e.g., token mismatch).
 */
class DataParsingException : public ZappyGuiException {
public:
    explicit DataParsingException(const std::string& message)
        : ZappyGuiException("[Parsing] " + message) {}
};

/**
 * @brief Exception thrown for game state-related issues.
 */
class GameStateException : public ZappyGuiException {
public:
    explicit GameStateException(const std::string& message)
        : ZappyGuiException("[GameState] " + message) {}
};

/**
 * @brief Exception thrown for entity-related issues (Trantorian, Egg, etc.).
 */
class EntityException : public ZappyGuiException {
public:
    explicit EntityException(const std::string& message)
        : ZappyGuiException("[Entity] " + message) {}
};