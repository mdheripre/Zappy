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
            while (true) {
                std::string message;
                if (!_outgoing->tryPop(message))
                    break;
                allMessage += message;
            }

            if (_client->readCommand())
                _incoming->push(_client->getCommand());

            if (!allMessage.empty()) {
                _client->sendMessage(allMessage);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(15));
        }
        catch (const std::exception& e) {
            std::cerr << "Network " << e.what() << std::endl;
            _running = false;
        }
    }
}
