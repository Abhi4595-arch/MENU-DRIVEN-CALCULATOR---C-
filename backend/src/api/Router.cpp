#include "api/Router.hpp"
#include "api/Controllers.hpp"
#include "calculator/Calculator.hpp"

Router::Router(Calculator& calculator)
    : calculator(calculator) {
}

HttpResponse Router::handleRequest(
    const HttpRequest& request
) {
    if (request.method == "OPTIONS") {
    HttpResponse response;

    response.statusCode = 204;
    response.contentType = "text/plain";
    response.body = "";

    return response;
   }
    if (
        request.method == "GET" &&
        request.path == "/api/health"
    ) {
        return health();
    }

    if (
        request.method == "POST" &&
        request.path == "/api/calculate"
    ) {
        return calculate(request);
    }

    if (
        request.method == "GET" &&
        request.path == "/api/history"
    ) {
        return history(request);
    }

    if (
        request.method == "DELETE" &&
        request.path == "/api/history/clear"
    ) {
        return clearHistory();
    }

    if (
    request.method == "GET" &&
    request.path == "/api/analytics"
) {
    return analytics();
}

    return notFound();
}

HttpResponse Router::health() {
    return Controllers::health();
}

HttpResponse Router::calculate(
    const HttpRequest& request
) {
    return Controllers::calculate(
        calculator,
        request
    );
}

HttpResponse Router::history(
    const HttpRequest& request
) {
    return Controllers::history(calculator);
}

HttpResponse Router::clearHistory() {
    return Controllers::clearHistory(calculator);
}
HttpResponse Router::analytics() {
    return Controllers::analytics(calculator);
}
HttpResponse Router::notFound() {
    HttpResponse response;

    response.statusCode = 404;
    response.contentType = "application/json";

    response.body =
        "{"
        "\"success\":false,"
        "\"error\":\"Endpoint not found\""
        "}";

    return response;
}