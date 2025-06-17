/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP
    #define CLIENT_HPP
    #include "../Socket/Socket.hpp"
    #include <map>
    #include <poll.h>
    #include <memory>
    #include "Network/Socket/Socket.hpp"
    #include <queue>

namespace net
{
    class Client {
        private:
        std::unique_ptr<Socket> _sock;
        std::string _commandBuffer;
        std::queue<std::string> _commands;
        public:
            Client(std::unique_ptr<Socket> sock) : _sock(std::move(sock)) {}
            ~Client() {_sock->closeSocket();}
            void sendMessage(const std::string &message) const;
            std::string getCommand();
            bool readCommand();
            void manageBuffer();
    }; 
} // namespace net


#endif // CLIENT_HPP