/*
** EPITECH PROJECT, 2025
** Project
** File description:
** MessageQueue.hpp
*/

#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

namespace tools {
    class MessageQueue {
        public:
            MessageQueue() = default;
            ~MessageQueue() = default;
            void push(const std::string& message);
            bool tryPop(std::string& result);
        private:
            std::queue<std::string> _queue;
            std::mutex _mutex;
            std::condition_variable _cond;
    };
} // namespace shared
