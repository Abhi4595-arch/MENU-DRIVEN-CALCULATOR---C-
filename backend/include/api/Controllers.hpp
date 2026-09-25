#ifndef CONTROLLERS_HPP
#define CONTROLLERS_HPP

#include "api/Router.hpp"

class Calculator;

class Controllers {
public:
    static HttpResponse health();

    static HttpResponse calculate(
        Calculator& calculator,
        const HttpRequest& request
    );

    static HttpResponse history(
        Calculator& calculator
    );

    static HttpResponse clearHistory(
        Calculator& calculator
    );

    static HttpResponse analytics(
        Calculator& calculator
    );
};

#endif