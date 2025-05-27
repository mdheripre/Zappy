/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** CommandManager.cpp
*/

#include "CommandManager.hpp"

bool tools::CommandManager::handleCommand(const std::vector<std::string> &args)
{
    std::vector<std::string> lowArgs;

    for (auto &i : args) {
        std::string lowArg = i;
        std::transform(lowArg.begin(), lowArg.end(), lowArg.begin(),
        [](unsigned char c) { return std::tolower(c); });
        lowArgs.push_back(lowArg);
    }
    if (args.empty())
        return false;
    auto it = _commands.find(lowArgs[0]);
    if (it != _commands.end()) {
        it->second(lowArgs);
        return true;
    }
    return false;
}

void tools::CommandManager::addCommand(std::string key, std::function<void(const std::vector<std::string> &)> value)
{
    _commands[key] = value;
}
