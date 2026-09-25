#include "calculator/Calculator.hpp"
#include "calculator/Operations.hpp"

#include <iostream>
#include <stdexcept>
#include <limits>

CalculationResult Calculator::calculate(
    const std::string& operation,
    double firstOperand,
    double secondOperand
) {
    CalculationResult response{};

    response.success = false;
    response.operation = operation;
    response.firstOperand = firstOperand;
    response.secondOperand = secondOperand;
    response.result = 0.0;
    response.error = "";

    try {
        if (operation == "+") {
            response.result =
                CalculatorOperations::add(
                    firstOperand,
                    secondOperand
                );
        }
        else if (operation == "-") {
            response.result =
                CalculatorOperations::subtract(
                    firstOperand,
                    secondOperand
                );
        }
        else if (operation == "*") {
            response.result =
                CalculatorOperations::multiply(
                    firstOperand,
                    secondOperand
                );
        }
        else if (operation == "/") {
            response.result =
                CalculatorOperations::divide(
                    firstOperand,
                    secondOperand
                );
        }
        else if (operation == "%") {
            long long first =
                static_cast<long long>(firstOperand);

            long long second =
                static_cast<long long>(secondOperand);

            response.result =
                static_cast<double>(
                    CalculatorOperations::modulus(
                        first,
                        second
                    )
                );
        }
        else if (operation == "^") {
            response.result =
                CalculatorOperations::power(
                    firstOperand,
                    secondOperand
                );
        }
        else if (operation == "sqrt") {
            response.result =
                CalculatorOperations::squareRoot(
                    firstOperand
                );
        }
        else if (operation == "abs") {
            response.result =
                CalculatorOperations::absolute(
                    firstOperand
                );
        }
        else if (operation == "sq") {
            response.result =
                CalculatorOperations::square(
                    firstOperand
                );
        }
        else if (operation == "cube") {
            response.result =
                CalculatorOperations::cube(
                    firstOperand
                );
        }
        else if (operation == "!") {
            response.result =
                CalculatorOperations::factorial(
                    firstOperand
                );
        }
        else if (operation == "1/x") {
            response.result =
                CalculatorOperations::reciprocal(
                    firstOperand
                );
        }
        else if (operation == "percent") {
            response.result =
                CalculatorOperations::percentage(
                    firstOperand,
                    secondOperand
                );
        }
        else {
            response.error =
                "Unsupported operation.";

            analyticsEngine.recordFailure();

            return response;
        }

        historyManager.addRecord(
            operation,
            firstOperand,
            secondOperand,
            response.result
        );

        analyticsEngine.recordSuccess(operation);

        response.success = true;

        return response;
    }
    catch (const std::exception& exception) {
        response.error = exception.what();

        analyticsEngine.recordFailure();

        return response;
    }
}

void Calculator::displayMenu() const {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "       MENU DRIVEN CALCULATOR\n";
    std::cout << "========================================\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Subtraction\n";
    std::cout << "3. Multiplication\n";
    std::cout << "4. Division\n";
    std::cout << "5. Modulus\n";
    std::cout << "6. Power\n";
    std::cout << "7. Square Root\n";
    std::cout << "8. Absolute Value\n";
    std::cout << "9. Square\n";
    std::cout << "10. Cube\n";
    std::cout << "11. Factorial\n";
    std::cout << "12. Reciprocal\n";
    std::cout << "13. Percentage\n";
    std::cout << "14. View History\n";
    std::cout << "15. Clear History\n";
    std::cout << "16. View Analytics\n";
    std::cout << "17. Exit\n";
    std::cout << "========================================\n";
}

int Calculator::readChoice() {
    int choice;

    while (true) {
        std::cout << "Enter your choice: ";

        if (std::cin >> choice) {
            return choice;
        }

        std::cout
            << "Invalid input. Please enter a valid menu number.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

double Calculator::readNumber(const char* prompt) {
    double number;

    while (true) {
        std::cout << prompt;

        if (std::cin >> number) {
            return number;
        }

        std::cout
            << "Invalid number. Please try again.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

void Calculator::performAddition() {
    double a = readNumber("Enter first number: ");
    double b = readNumber("Enter second number: ");

    double result =
        CalculatorOperations::add(a, b);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord("+", a, b, result);
    analyticsEngine.recordSuccess("+");
}

void Calculator::performSubtraction() {
    double a = readNumber("Enter first number: ");
    double b = readNumber("Enter second number: ");

    double result =
        CalculatorOperations::subtract(a, b);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord("-", a, b, result);
    analyticsEngine.recordSuccess("-");
}

void Calculator::performMultiplication() {
    double a = readNumber("Enter first number: ");
    double b = readNumber("Enter second number: ");

    double result =
        CalculatorOperations::multiply(a, b);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord("*", a, b, result);
    analyticsEngine.recordSuccess("*");
}

void Calculator::performDivision() {
    double a = readNumber("Enter first number: ");
    double b = readNumber("Enter second number: ");

    double result =
        CalculatorOperations::divide(a, b);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord("/", a, b, result);
    analyticsEngine.recordSuccess("/");
}

void Calculator::performModulus() {
    double first =
        readNumber("Enter first integer: ");

    double second =
        readNumber("Enter second integer: ");

    long long a =
        static_cast<long long>(first);

    long long b =
        static_cast<long long>(second);

    long long result =
        CalculatorOperations::modulus(a, b);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "%",
        a,
        b,
        result
    );

    analyticsEngine.recordSuccess("%");
}

void Calculator::performPower() {
    double a =
        readNumber("Enter base: ");

    double b =
        readNumber("Enter exponent: ");

    double result =
        CalculatorOperations::power(a, b);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "^",
        a,
        b,
        result
    );

    analyticsEngine.recordSuccess("^");
}

void Calculator::performSquareRoot() {
    double a =
        readNumber("Enter number: ");

    double result =
        CalculatorOperations::squareRoot(a);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "sqrt",
        a,
        0.0,
        result
    );

    analyticsEngine.recordSuccess("sqrt");
}

void Calculator::performAbsolute() {
    double a =
        readNumber("Enter number: ");

    double result =
        CalculatorOperations::absolute(a);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "abs",
        a,
        0.0,
        result
    );

    analyticsEngine.recordSuccess("abs");
}

void Calculator::performSquare() {
    double a =
        readNumber("Enter number: ");

    double result =
        CalculatorOperations::square(a);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "sq",
        a,
        0.0,
        result
    );

    analyticsEngine.recordSuccess("sq");
}

void Calculator::performCube() {
    double a =
        readNumber("Enter number: ");

    double result =
        CalculatorOperations::cube(a);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "cube",
        a,
        0.0,
        result
    );

    analyticsEngine.recordSuccess("cube");
}

void Calculator::performFactorial() {
    double a =
        readNumber("Enter a non-negative integer: ");

    double result =
        CalculatorOperations::factorial(a);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "!",
        a,
        0.0,
        result
    );

    analyticsEngine.recordSuccess("!");
}

void Calculator::performReciprocal() {
    double a =
        readNumber("Enter number: ");

    double result =
        CalculatorOperations::reciprocal(a);

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "1/x",
        a,
        0.0,
        result
    );

    analyticsEngine.recordSuccess("1/x");
}

void Calculator::performPercentage() {
    double percentage =
        readNumber("Enter percentage: ");

    double number =
        readNumber("Enter number: ");

    double result =
        CalculatorOperations::percentage(
            percentage,
            number
        );

    std::cout << "Result: " << result << "\n";

    historyManager.addRecord(
        "percent",
        percentage,
        number,
        result
    );

    analyticsEngine.recordSuccess("percent");
}

void Calculator::viewHistory() const {
    historyManager.displayHistory();
}

void Calculator::clearHistory() {
    historyManager.clearHistory();
    analyticsEngine.reset();
    std::cout
        << "\nCalculation history cleared.\n";
}

void Calculator::viewAnalytics() const {
    analyticsEngine.displayAnalytics();
}

void Calculator::processChoice(int choice) {
    try {
        switch (choice) {
            case 1:
                performAddition();
                break;

            case 2:
                performSubtraction();
                break;

            case 3:
                performMultiplication();
                break;

            case 4:
                performDivision();
                break;

            case 5:
                performModulus();
                break;

            case 6:
                performPower();
                break;

            case 7:
                performSquareRoot();
                break;

            case 8:
                performAbsolute();
                break;

            case 9:
                performSquare();
                break;

            case 10:
                performCube();
                break;

            case 11:
                performFactorial();
                break;

            case 12:
                performReciprocal();
                break;

            case 13:
                performPercentage();
                break;

            case 14:
                viewHistory();
                break;

            case 15:
                clearHistory();
                break;

            case 16:
                viewAnalytics();
                break;

            case 17:
                std::cout
                    << "Exiting calculator...\n";
                break;

            default:
                std::cout
                    << "Invalid choice. Please select 1-17.\n";
                break;
        }
    }
    catch (const std::exception& exception) {
        analyticsEngine.recordFailure();

        std::cout
            << "Error: "
            << exception.what()
            << "\n";
    }
}

void Calculator::run() {
    int choice;

    do {
        displayMenu();

        choice = readChoice();

        processChoice(choice);

    } while (choice != 17);

    std::cout
        << "Thank you for using MENU DRIVEN CALCULATOR.\n";
}

HistoryManager& Calculator::getHistoryManager() {
    return historyManager;
}

const HistoryManager& Calculator::getHistoryManager() const {
    return historyManager;
}

const AnalyticsEngine& Calculator::getAnalyticsEngine() const {
    return analyticsEngine;
}

void Calculator::clearCalculationHistory() {
    clearHistory();
}