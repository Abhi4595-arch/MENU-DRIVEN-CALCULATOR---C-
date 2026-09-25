#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <string>

class Calculator;

struct HttpRequest {
    std::string method;
    std::string path;
    std::string body;
};

struct HttpResponse {
    int statusCode;
    std::string contentType;
    std::string body;
};

class Router {
public:
    explicit Router(Calculator& calculator);

    HttpResponse handleRequest(
        const HttpRequest& request
    );

private:
    Calculator& calculator;

    HttpResponse health();

    HttpResponse calculate(
        const HttpRequest& request
    );

    HttpResponse history(
        const HttpRequest& request
    );

    HttpResponse clearHistory();
HttpResponse analytics();
HttpResponse notFound();
};

#endif