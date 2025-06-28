/*
** EPITECH PROJECT, 2025
** B-YEP-400-LIL-4-1-zappy-nicolas.dumetz
** File description:
** main
*/

#include "Core/Core.hpp"
#include <iostream>

int main(int, char **av, char **env)
{
    std::vector<std::string> args;

    for (int i = 1; av[i]; i++)
        args.push_back(av[i]);
    try
    {
        gui::Core core(args, env);
        core.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}