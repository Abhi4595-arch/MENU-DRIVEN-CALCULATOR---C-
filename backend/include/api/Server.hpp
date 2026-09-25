#ifndef SERVER_HPP
#define SERVER_HPP

#include <winsock2.h>

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
    SOCKET serverSocket;

    void acceptConnections();
};

#endif