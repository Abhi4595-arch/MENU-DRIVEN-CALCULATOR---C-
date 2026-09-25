#include "calculator/Calculator.hpp"
#include "api/Server.hpp"
#include "api/Router.hpp"

#include <string>

int main(int argc, char* argv[]) {

    Calculator calculator;

    if (
        argc > 1 &&
        std::string(argv[1]) == "--server"
    ) {
        Router router(calculator);
        Server server(8080, router);

        if (!server.start()) {
            return 1;
        }

        return 0;
    }

    calculator.run();

    return 0;
}