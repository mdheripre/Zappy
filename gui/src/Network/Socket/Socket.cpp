/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Socket.cpp
*/

#include "Socket.hpp"

net::Socket::Socket()
{
    this->cleanSockaddr();
    this->_fd = 0;
}

net::Socket::Socket(int port, bool isListen)
{
    this->cleanSockaddr();
    this->_fd = socket(AF_INET, SOCK_STREAM, 0);
    socklen_t addr_len = sizeof(_in);

    if (this->_fd < 0)
        throw std::runtime_error("Error: Socket creation failed");

    _in.sin_family = AF_INET;
    _in.sin_addr.s_addr = INADDR_ANY;
    _in.sin_port = htons(port);

    if (isListen) {
        if (bind(_fd, (struct sockaddr *)&_in, sizeof(_in)) != 0)
            throw std::runtime_error("Error: Binding failed");
        if (getsockname(this->_fd, (struct sockaddr *)&_in, &addr_len) == -1)
            throw std::runtime_error("Error: getsockname failed");
        if (listen(_fd, SOMAXCONN) != 0)
            throw std::runtime_error("Error: Listen failed");
    }
}

void net::Socket::cleanSockaddr()
{
    if (!memset(&this->_in, 0, sizeof(this->_in)))
        throw std::runtime_error("Error : can't memset addr_in");
}

net::Socket net::Socket::acceptConnection() const
{
    Socket newSocket;
    socklen_t len = sizeof(newSocket._in);

    newSocket._fd = accept(_fd, (sockaddr *)&newSocket._in, &len);
    if (newSocket._fd < 0)
        throw std::runtime_error("Error: Accepting connection failed");
    return newSocket;
}

void net::Socket::connectSocket(const std::string &addr)
{
    struct addrinfo hints{}, *res = nullptr;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(addr.c_str(), getPortR().c_str(), &hints, &res) != 0) {
        throw std::runtime_error("Error: Unable to resolve host: " + addr);
    }
    if (connect(_fd, res->ai_addr, res->ai_addrlen) < 0) {
        freeaddrinfo(res);
        throw std::runtime_error("Error: Can't open data connection.");
    }
    freeaddrinfo(res);
}


void net::Socket::closeSocket()
{
    if (close(this->_fd) < 0)
        throw(std::string("Error : Can't close Socket address: ") +
            inet_ntoa(this->_in.sin_addr));
}

std::ostream &operator<<(std::ostream &os, const net::Socket &sock)
{
    os << "Socket FD: " << sock.getFd();
    os << ", IP: " << sock.getAddrR();
    os << ", Port: " << sock. getPortR();
    return os;
}
