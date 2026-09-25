#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdint>

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
    std::intptr_t serverSocket;

    void acceptConnections();
};

#endif