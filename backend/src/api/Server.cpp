#include "api/Server.hpp"
#include "api/Router.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <sstream>
#include <string>

namespace {

std::string createHttpResponse(
    const HttpResponse& response
) {
    std::ostringstream output;

    output << "HTTP/1.1 "
           << response.statusCode;

    if (response.statusCode == 200) {
    output << " OK\r\n";
}
else if (response.statusCode == 204) {
    output << " No Content\r\n";
}
else if (response.statusCode == 400) {
    output << " Bad Request\r\n";
}
else if (response.statusCode == 404) {
    output << " Not Found\r\n";
}
else {
    output << "\r\n";
}

    output << "Content-Type: "
           << response.contentType
           << "\r\n";

    output << "Content-Length: "
           << response.body.size()
           << "\r\n";

    output << "Access-Control-Allow-Origin: *\r\n";
output << "Access-Control-Allow-Methods: GET, POST, DELETE, OPTIONS\r\n";
output << "Access-Control-Allow-Headers: Content-Type\r\n";

    output << "Connection: close\r\n";
    output << "\r\n";

    output << response.body;

    return output.str();
}

std::size_t findHeaderEnd(
    const std::string& request
) {
    return request.find("\r\n\r\n");
}

std::size_t getContentLength(
    const std::string& request
) {
    const std::string header =
        "Content-Length:";

    std::size_t position =
        request.find(header);

    if (position == std::string::npos) {
        return 0;
    }

    position += header.length();

    while (
        position < request.size() &&
        (request[position] == ' ' ||
         request[position] == '\t')
    ) {
        ++position;
    }

    std::size_t end =
        request.find("\r\n", position);

    if (end == std::string::npos) {
        return 0;
    }

    try {
        return static_cast<std::size_t>(
            std::stoul(
                request.substr(
                    position,
                    end - position
                )
            )
        );
    }
    catch (...) {
        return 0;
    }
}

HttpRequest parseHttpRequest(
    const std::string& rawRequest
) {
    HttpRequest request;

    std::size_t headerEnd =
        findHeaderEnd(rawRequest);

    std::string headers;

    if (headerEnd != std::string::npos) {
        headers =
            rawRequest.substr(
                0,
                headerEnd
            );
    }
    else {
        headers = rawRequest;
    }

    std::istringstream stream(headers);

    std::string requestLine;

    std::getline(
        stream,
        requestLine
    );

    if (
        !requestLine.empty() &&
        requestLine.back() == '\r'
    ) {
        requestLine.pop_back();
    }

    std::istringstream requestLineStream(
        requestLine
    );

    requestLineStream
        >> request.method
        >> request.path;

    if (headerEnd != std::string::npos) {
        request.body =
            rawRequest.substr(
                headerEnd + 4
            );
    }

    return request;
}

}

Server::Server(
    int port,
    Router& router
)
    : port(port),
      router(router),
      running(false),
      serverSocket(INVALID_SOCKET) {
}

Server::~Server() {
    stop();
}

bool Server::start() {

    WSADATA wsaData;

    int result =
        WSAStartup(
            MAKEWORD(2, 2),
            &wsaData
        );

    if (result != 0) {
        std::cerr
            << "WSAStartup failed.\n";

        return false;
    }

    serverSocket =
        socket(
            AF_INET,
            SOCK_STREAM,
            IPPROTO_TCP
        );

    if (
        serverSocket ==
        INVALID_SOCKET
    ) {
        std::cerr
            << "Failed to create server socket.\n";

        WSACleanup();

        return false;
    }

    sockaddr_in serverAddress{};

    serverAddress.sin_family =
        AF_INET;

    serverAddress.sin_addr.s_addr =
        htonl(INADDR_ANY);

    serverAddress.sin_port =
        htons(
            static_cast<u_short>(port)
        );

    if (
        bind(
            serverSocket,
            reinterpret_cast<sockaddr*>(
                &serverAddress
            ),
            sizeof(serverAddress)
        ) == SOCKET_ERROR
    ) {
        std::cerr
            << "Failed to bind port "
            << port
            << ".\n";

        closesocket(serverSocket);
        WSACleanup();

        return false;
    }

    if (
        listen(
            serverSocket,
            SOMAXCONN
        ) == SOCKET_ERROR
    ) {
        std::cerr
            << "Failed to listen on port "
            << port
            << ".\n";

        closesocket(serverSocket);
        WSACleanup();

        return false;
    }

    running = true;

    std::cout
        << "\n========================================\n"
        << "       MENU DRIVEN CALCULATOR API\n"
        << "========================================\n"
        << "Server running on port "
        << port
        << "\n"
        << "Health endpoint:\n"
        << "http://localhost:"
        << port
        << "/api/health\n"
        << "========================================\n";

    acceptConnections();

    return true;
}

void Server::acceptConnections() {

    while (running) {

        SOCKET clientSocket =
            accept(
                serverSocket,
                nullptr,
                nullptr
            );

        if (
            clientSocket ==
            INVALID_SOCKET
        ) {
            if (running) {
                std::cerr
                    << "Failed to accept connection.\n";
            }

            continue;
        }

        std::string rawRequest;

        char buffer[4096];

        /*
         * Read the HTTP request.
         *
         * We cannot assume that the complete
         * request arrives in one recv() call.
         */
        while (true) {

            int bytesReceived =
                recv(
                    clientSocket,
                    buffer,
                    sizeof(buffer),
                    0
                );

            if (bytesReceived <= 0) {
                break;
            }

            rawRequest.append(
                buffer,
                bytesReceived
            );

            std::size_t headerEnd =
                findHeaderEnd(rawRequest);

            if (
                headerEnd == std::string::npos
            ) {
                continue;
            }

            std::size_t contentLength =
                getContentLength(
                    rawRequest
                );

            std::size_t bodyStart =
                headerEnd + 4;

            std::size_t bodySize =
                rawRequest.size() -
                bodyStart;

            /*
             * For GET requests there is normally
             * no body.
             */
            if (contentLength == 0) {
                break;
            }

            /*
             * Continue receiving until the complete
             * HTTP body has arrived.
             */
            if (bodySize >= contentLength) {
                break;
            }
        }

        if (!rawRequest.empty()) {

            HttpRequest request =
                parseHttpRequest(
                    rawRequest
                );

            HttpResponse response =
                router.handleRequest(
                    request
                );

            std::string httpResponse =
                createHttpResponse(
                    response
                );

            send(
                clientSocket,
                httpResponse.c_str(),
                static_cast<int>(
                    httpResponse.size()
                ),
                0
            );
        }

        closesocket(
            clientSocket
        );
    }
}

void Server::stop() {

    if (
        !running &&
        serverSocket ==
            INVALID_SOCKET
    ) {
        return;
    }

    running = false;

    if (
        serverSocket !=
        INVALID_SOCKET
    ) {
        closesocket(
            serverSocket
        );

        serverSocket =
            INVALID_SOCKET;
    }

    WSACleanup();
}