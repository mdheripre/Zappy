/*
** EPITECH PROJECT, 2025
** Project
** File description:
** CommandManager
*/

#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace tools {
    class CommandManager {
    public:
        CommandManager() = default;

        bool handleCommand(const std::vector<std::string> &args);
        void addCommand(std::string, std::function<void(const std::vector<std::string>&)>);
    private:
        std::unordered_map<std::string, std::function<void(const std::vector<std::string>&)>> _commands;
    };
}