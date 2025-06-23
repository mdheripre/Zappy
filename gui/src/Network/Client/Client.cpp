/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Client.cpp
*/

#include "Client.hpp"
#include "Tools/Error/Error.hpp"

void net::Client::sendMessage(const std::string &message) const
{
    struct pollfd pfd;
    pfd.fd = this->_sock->getFd();
    pfd.events = POLLOUT;

    std::cout << "Message " << message << std::endl;
    if (poll(&pfd, 1, 100) <= 0 || (pfd.revents & POLLHUP) || !(pfd.revents & POLLOUT))
        throw NetworkError("Socket isn't ready or has been closed");
    if (write(this->_sock->getFd(), message.c_str(), message.length()) < 0)
        throw NetworkError("Impossible to send message");
}

bool net::Client::readCommand()
{
    struct pollfd pfd;
    pfd.fd = this->_sock->getFd();
    pfd.events = POLLIN;
    char buffer[1024];

    if (poll(&pfd, 1, 0) <= 0)
        return false;

    if (pfd.revents & POLLIN) {
        ssize_t bytes_read = read(this->_sock->getFd(), buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
            throw NetworkError("Read failed or connection closed");

        this->_commandBuffer += std::string(buffer, bytes_read);;
        manageBuffer();
    }
    return !_commands.empty();
}

void net::Client::manageBuffer()
{
    size_t pos = this->_commandBuffer.find('\n');

    while (pos != std::string::npos) {
        std::string cmd = this->_commandBuffer.substr(0, pos);
        this->_commandBuffer.erase(0, pos + 1);
        this->_commands.push(cmd);
        pos = this->_commandBuffer.find('\n');
    }
}

std::string net::Client::getCommand()
{
    if (_commands.empty())
        return "";
    std::string cmd = _commands.front();
    _commands.pop();
    return cmd;
}

