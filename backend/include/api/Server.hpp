#ifndef SERVER_HPP
#define SERVER_HPP

#ifdef _WIN32
#include <winsock2.h>
#else
#include <cstdint>
#endif

class Router;

class Server {
public:
    Server(int port, Router& router);
    ~Server();

    bool start();
    void stop();

private:
    int port;
    Router& router;

    bool running;

#ifdef _WIN32
    SOCKET serverSocket;
#else
    std::intptr_t serverSocket;
#endif

    void acceptConnections();
};

#endif
