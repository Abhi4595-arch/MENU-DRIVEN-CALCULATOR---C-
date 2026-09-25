#include "calculator/Calculator.hpp"
#include "api/Server.hpp"
#include "api/Router.hpp"

#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {

    Calculator calculator;

    if (
        argc > 1 &&
        std::string(argv[1]) == "--server"
    ) {
        int port = 8080;

        const char* portEnv = std::getenv("PORT");

        if (portEnv != nullptr) {
            try {
                port = std::stoi(portEnv);
            }
            catch (...) {
                port = 8080;
            }
        }

        Router router(calculator);
        Server server(port, router);

        if (!server.start()) {
            return 1;
        }

        return 0;
    }

    calculator.run();

    return 0;
}