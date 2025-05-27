/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** CommandManager.cpp
*/

#include "CommandManager.hpp"

bool tools::CommandManager::handleCommand(const std::vector<std::string> &args)
{
    if (args.empty())
        return false;

    auto it = _commands.find(args[0]);
    if (it != _commands.end()) {
        std::vector<std::string> subargs(args.begin() + 1, args.end());
        it->second(subargs);
        return true;
    }
    return false;
}

void tools::CommandManager::addCommand(std::string key, std::function<void(const std::vector<std::string> &)> value)
{
    _commands[key] = value;
}
