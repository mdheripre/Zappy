#pragma once

#include <exception>
#include <string>

/**
 * @brief Base exception class for all Zappy GUI-related errors.
 */
class Error : public std::exception
{
public:
    Error(const std::string &message) : _message(message) {};
    ~Error() = default;

    const char *what() const throw() { return this->_message.c_str(); };

    /**
     * @brief Adds location context to the exception.
     * @param location Where the error occurred (function name, class::method, etc.)
     * @return Reference to this exception for method chaining
     */
    Error& where(const std::string& location) {
        _message += " (at: " + location + ")";
        return *this;
    }

private:
    std::string _message;
};

/**
 * @brief Exception thrown for rendering-related issues.
 */
class RenderError : public Error {
public:
    RenderError(const std::string& message) : Error("[Render] " + message) {}
    
    RenderError& where(const std::string& location) {
        Error::where(location);
        return *this;
    }
};

/**
 * @brief Exception thrown when a command is invalid or unrecognized.
 */
class CommandError : public Error {
public:
    CommandError(const std::string& message) : Error("[Command] " + message) {}
    
    CommandError& where(const std::string& location) {
        Error::where(location);
        return *this;
    }
};

/**
 * @brief Exception thrown for data parsing issues (e.g., token mismatch).
 */
class DataParsingError : public Error {
public:
    DataParsingError(const std::string& message) : Error("[Parsing] " + message) {}
    
    DataParsingError& where(const std::string& location) {
        Error::where(location);
        return *this;
    }
};

/**
 * @brief Exception thrown for game state-related issues.
 */
class GameStateError : public Error {
public:
    GameStateError(const std::string& message) : Error("[GameState] " + message) {}
    
    GameStateError& where(const std::string& location) {
        Error::where(location);
        return *this;
    }
};

/**
 * @brief Exception thrown for entity-related issues (Trantorian, Egg, etc.).
 */
class EntityError : public Error {
public:
    EntityError(const std::string& message) : Error("[Entity] " + message) {}
    
    EntityError& where(const std::string& location) {
        Error::where(location);
        return *this;
    }
};

