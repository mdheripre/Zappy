/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Network.hpp
*/

#include "Network.hpp"

net::Network::Network(std::shared_ptr<tools::MessageQueue> incoming,
    std::shared_ptr<tools::MessageQueue> outgoing,
    int port,
    std::string addr): _incoming(incoming), _outgoing(outgoing)
{
    std::unique_ptr<Socket> sock = std::make_unique<Socket>(port, false);

    sock->connectSocket(addr);
    _client = std::make_unique<Client>(std::move(sock));
}

void net::Network::startLoop()
{
    while (_running) {
        try {
            std::string allMessage;
            std::string message;
            while (_outgoing->tryPop(message))
                allMessage += message;

            if (!allMessage.empty())
                _client->sendMessage(allMessage);

            while (_client->readCommand()) {
                std::string command = _client->getCommand();
                while (!command.empty())
                {
                    _incoming->push(command);
                    command = _client->getCommand();
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Network " << e.what() << std::endl;
            _running = false;
        }
    }
}

