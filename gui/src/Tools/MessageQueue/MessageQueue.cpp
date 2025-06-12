/*
** EPITECH PROJECT, 2025
** Project
** File description:
** MessageQueue.cpp
*/

#include "MessageQueue.hpp"
#include <iostream>

void tools::MessageQueue::push(const std::string &message)
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::cout<<message<< std::endl;
    _queue.push(message);
    _cond.notify_one();
}

bool tools::MessageQueue::tryPop(std::string &result)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_queue.empty())
        return false;
    result = _queue.front();
    _queue.pop();
    return true;
}

