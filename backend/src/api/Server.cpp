#include "api/Server.hpp"
#include "api/Router.hpp"

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using SOCKET = int;

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif

#ifndef SOCKET_ERROR
#define SOCKET_ERROR (-1)
#endif

#endif

namespace {

#ifdef _WIN32

void closeSocket(SOCKET socket) {
    closesocket(socket);
}

#else

void closeSocket(SOCKET socket) {
    close(socket);
}

#endif

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
    std::istringstream stream(request);

    std::string line;

    while (std::getline(stream, line)) {

        if (
            !line.empty() &&
            line.back() == '\r'
        ) {
            line.pop_back();
        }

        std::size_t colon =
            line.find(':');

        if (colon == std::string::npos) {
            continue;
        }

        std::string name =
            line.substr(0, colon);

        std::string value =
            line.substr(colon + 1);

        /*
         * HTTP header names are case-insensitive.
         */
        for (char& character : name) {
            character =
                static_cast<char>(
                    std::tolower(
                        static_cast<unsigned char>(
                            character
                        )
                    )
                );
        }

        if (name != "content-length") {
            continue;
        }

        std::size_t start = 0;

        while (
            start < value.size() &&
            (
                value[start] == ' ' ||
                value[start] == '\t'
            )
        ) {
            ++start;
        }

        try {
            return static_cast<std::size_t>(
                std::stoul(
                    value.substr(start)
                )
            );
        }
        catch (...) {
            return 0;
        }
    }

    return 0;
}

HttpRequest parseHttpRequest(
    const std::string& rawRequest
) {
    HttpRequest request;

    std::size_t headerEnd =
        findHeaderEnd(rawRequest);

    if (headerEnd == std::string::npos) {
        return request;
    }

    std::string headers =
        rawRequest.substr(
            0,
            headerEnd
        );

    std::istringstream stream(headers);

    std::string requestLine;

    if (!std::getline(stream, requestLine)) {
        return request;
    }

    if (
        !requestLine.empty() &&
        requestLine.back() == '\r'
    ) {
        requestLine.pop_back();
    }

    std::istringstream requestLineStream(
        requestLine
    );

    std::string httpVersion;

    requestLineStream
        >> request.method
        >> request.path
        >> httpVersion;

    /*
     * Everything after the HTTP header separator
     * belongs to the request body.
     */
    request.body =
        rawRequest.substr(
            headerEnd + 4
        );

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

#ifdef _WIN32

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

#endif

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

#ifdef _WIN32
        WSACleanup();
#endif

        return false;
    }

    sockaddr_in serverAddress{};

    serverAddress.sin_family =
        AF_INET;

    serverAddress.sin_addr.s_addr =
        htonl(INADDR_ANY);

    serverAddress.sin_port =
        htons(
            static_cast<std::uint16_t>(port)
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

        closeSocket(serverSocket);
        serverSocket = INVALID_SOCKET;

#ifdef _WIN32
        WSACleanup();
#endif

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

        closeSocket(serverSocket);
        serverSocket = INVALID_SOCKET;

#ifdef _WIN32
        WSACleanup();
#endif

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
                headerEnd ==
                std::string::npos
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

            if (contentLength == 0) {
                break;
            }

            if (
                bodySize >=
                contentLength
            ) {
                break;
            }
        }

        if (!rawRequest.empty()) {

            HttpRequest request =
                parseHttpRequest(
                    rawRequest
                );

            std::cerr
                << "\n========== HTTP REQUEST DEBUG ==========\n"
                << "Method: ["
                << request.method
                << "]\n"
                << "Path:   ["
                << request.path
                << "]\n"
                << "Body:   ["
                << request.body
                << "]\n"
                << "Body length: "
                << request.body.size()
                << "\n"
                << "========================================\n";

            HttpResponse response =
                router.handleRequest(
                    request
                );

            std::string httpResponse =
                createHttpResponse(
                    response
                );

            std::size_t totalSent = 0;

            while (
                totalSent <
                httpResponse.size()
            ) {

                int bytesSent =
                    send(
                        clientSocket,
                        httpResponse.c_str() +
                            totalSent,
                        static_cast<int>(
                            httpResponse.size() -
                            totalSent
                        ),
                        0
                    );

                if (bytesSent <= 0) {
                    break;
                }

                totalSent +=
                    static_cast<std::size_t>(
                        bytesSent
                    );
            }
        }

        closeSocket(clientSocket);
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
        closeSocket(
            serverSocket
        );

        serverSocket =
            INVALID_SOCKET;
    }

#ifdef _WIN32

    WSACleanup();

#endif
}