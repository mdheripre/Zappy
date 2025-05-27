/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Client.cpp
*/

#include "Client.hpp"

void net::Client::sendMessage(const std::string &message) const
{
    struct pollfd pfd;
    pfd.fd = this->_sock->getFd();
    pfd.events = POLLOUT;

    if (poll(&pfd, 1, 0) <= 0 || (pfd.revents & POLLHUP) || !(pfd.revents & POLLOUT))
        throw std::runtime_error("Socket isn't ready or has been closed");
    if (write(this->_sock->getFd(), message.c_str(), message.length()) < 0)
        throw std::runtime_error("Impossible to send message");
}

bool net::Client::readCommand()
{
    struct pollfd pfd;
    pfd.fd = this->_sock->getFd();
    pfd.events = POLLIN;
    char buffer[1024];
    size_t pos;

    if (poll(&pfd, 1, -1) < 0)
        throw std::runtime_error("Error during readCommand call (poll failed)");
    if (pfd.revents & POLLIN) {
        ssize_t bytes_read = read(this->_sock->getFd(), buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
            throw std::runtime_error("Error in readCommand: unable to read command or connection closed");
        buffer[bytes_read] = '\0';
        this->_commandBuffer += buffer;
        pos = this->_commandBuffer.find("\n");
        if (pos != std::string::npos) {
            this->_command = this->_commandBuffer.substr(0, pos);
            this->_commandBuffer.erase(0, pos + 2);
            return true;
        }
    }
    return false;
}

