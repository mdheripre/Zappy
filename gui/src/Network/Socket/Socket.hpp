/*
** EPITECH PROJECT, 2025
** Projet
** File description:
** Socket.hpp
*/

#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <sstream>
#include <ifaddrs.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <netdb.h>

namespace net
{
    class Socket {
        private:
            sockaddr_in _in;
            int _fd;
        public:
            Socket();
            Socket(int port, bool isListen);
            ~Socket() = default;
            void cleanSockaddr();
            Socket acceptConnection() const;
            void connectSocket(const std::string &addr);
            void closeSocket();
            int getFd() const {return _fd;};
            std::string getAddrR() const {return inet_ntoa(_in.sin_addr);}
            std::string getPortR() const {return std::to_string(ntohs(_in.sin_port));}
    };
}
std::ostream &operator<<(std::ostream &os, const net::Socket &sock);