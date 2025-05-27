/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Network.hpp
*/

#pragma once
#include "Network/Client/Client.hpp"
#include "Tools/MessageQueue/MessageQueue.hpp"
#include <stdexcept>
#include <memory>
#include <thread>

namespace net
{
    class Network
    {
    private:
        std::unique_ptr<Client> _client;
        std::shared_ptr<tools::MessageQueue> _incoming;
        std::shared_ptr<tools::MessageQueue> _outgoing;
        bool _running;
    public:
        Network(std::shared_ptr<tools::MessageQueue> incoming,
            std::shared_ptr<tools::MessageQueue> outgoing,
            int port,
            std::string addr);
        ~Network() = default;
        void stopLoop() {_running = false;}
        void startLoop();
    };
} // namespace net
