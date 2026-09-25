#include "analytics/AnalyticsEngine.hpp"

#include <iostream>
#include <iomanip>

void AnalyticsEngine::recordSuccess(
    const std::string& operation
) {
    ++totalCalculations;
    ++successfulCalculations;

    if (operation == "+") {
        ++additionCount;
    }
    else if (operation == "-") {
        ++subtractionCount;
    }
    else if (operation == "*") {
        ++multiplicationCount;
    }
    else if (operation == "/") {
        ++divisionCount;
    }
    else if (operation == "%") {
        ++modulusCount;
    }
    else if (operation == "^") {
        ++powerCount;
    }
    else if (operation == "sqrt") {
        ++squareRootCount;
    }
    else if (operation == "abs") {
        ++absoluteCount;
    }
    else if (operation == "sq") {
        ++squareCount;
    }
    else if (operation == "cube") {
        ++cubeCount;
    }
    else if (operation == "!") {
        ++factorialCount;
    }
    else if (operation == "1/x") {
        ++reciprocalCount;
    }
    else if (operation == "percent") {
        ++percentageCount;
    }
}

void AnalyticsEngine::recordFailure() {
    ++totalCalculations;
    ++failedCalculations;
}

void AnalyticsEngine::reset() {
    totalCalculations = 0;
    successfulCalculations = 0;
    failedCalculations = 0;

    additionCount = 0;
    subtractionCount = 0;
    multiplicationCount = 0;
    divisionCount = 0;
    modulusCount = 0;

    powerCount = 0;
    squareRootCount = 0;
    absoluteCount = 0;
    squareCount = 0;
    cubeCount = 0;
    factorialCount = 0;
    reciprocalCount = 0;
    percentageCount = 0;
}

int AnalyticsEngine::getTotalCalculations() const {
    return totalCalculations;
}

int AnalyticsEngine::getSuccessfulCalculations() const {
    return successfulCalculations;
}

int AnalyticsEngine::getFailedCalculations() const {
    return failedCalculations;
}

int AnalyticsEngine::getAdditionCount() const {
    return additionCount;
}

int AnalyticsEngine::getSubtractionCount() const {
    return subtractionCount;
}

int AnalyticsEngine::getMultiplicationCount() const {
    return multiplicationCount;
}

int AnalyticsEngine::getDivisionCount() const {
    return divisionCount;
}

int AnalyticsEngine::getModulusCount() const {
    return modulusCount;
}

int AnalyticsEngine::getPowerCount() const {
    return powerCount;
}

int AnalyticsEngine::getSquareRootCount() const {
    return squareRootCount;
}

int AnalyticsEngine::getAbsoluteCount() const {
    return absoluteCount;
}

int AnalyticsEngine::getSquareCount() const {
    return squareCount;
}

int AnalyticsEngine::getCubeCount() const {
    return cubeCount;
}

int AnalyticsEngine::getFactorialCount() const {
    return factorialCount;
}

int AnalyticsEngine::getReciprocalCount() const {
    return reciprocalCount;
}

int AnalyticsEngine::getPercentageCount() const {
    return percentageCount;
}

double AnalyticsEngine::getSuccessRate() const {
    if (totalCalculations == 0) {
        return 0.0;
    }

    return (
        static_cast<double>(successfulCalculations)
        / totalCalculations
    ) * 100.0;
}

std::string AnalyticsEngine::getMostUsedOperation() const {
    int highestCount = 0;
    std::string operation = "None";

    if (additionCount > highestCount) {
        highestCount = additionCount;
        operation = "Addition";
    }

    if (subtractionCount > highestCount) {
        highestCount = subtractionCount;
        operation = "Subtraction";
    }

    if (multiplicationCount > highestCount) {
        highestCount = multiplicationCount;
        operation = "Multiplication";
    }

    if (divisionCount > highestCount) {
        highestCount = divisionCount;
        operation = "Division";
    }

    if (modulusCount > highestCount) {
        highestCount = modulusCount;
        operation = "Modulus";
    }

    if (powerCount > highestCount) {
        highestCount = powerCount;
        operation = "Power";
    }

    if (squareRootCount > highestCount) {
        highestCount = squareRootCount;
        operation = "Square Root";
    }

    if (absoluteCount > highestCount) {
        highestCount = absoluteCount;
        operation = "Absolute Value";
    }

    if (squareCount > highestCount) {
        highestCount = squareCount;
        operation = "Square";
    }

    if (cubeCount > highestCount) {
        highestCount = cubeCount;
        operation = "Cube";
    }

    if (factorialCount > highestCount) {
        highestCount = factorialCount;
        operation = "Factorial";
    }

    if (reciprocalCount > highestCount) {
        highestCount = reciprocalCount;
        operation = "Reciprocal";
    }

    if (percentageCount > highestCount) {
        highestCount = percentageCount;
        operation = "Percentage";
    }

    return operation;
}

void AnalyticsEngine::displayAnalytics() const {
    std::cout << "\n";
    std::cout
        << "================ CALCULATOR ANALYTICS ================\n";

    std::cout
        << "Total calculations     : "
        << totalCalculations
        << "\n";

    std::cout
        << "Successful calculations: "
        << successfulCalculations
        << "\n";

    std::cout
        << "Failed calculations    : "
        << failedCalculations
        << "\n";

    std::cout << std::fixed << std::setprecision(2);

    std::cout
        << "Success rate           : "
        << getSuccessRate()
        << "%\n";

    std::cout << "\nOperation usage:\n";

    std::cout
        << "  Addition             : "
        << additionCount
        << "\n";

    std::cout
        << "  Subtraction          : "
        << subtractionCount
        << "\n";

    std::cout
        << "  Multiplication       : "
        << multiplicationCount
        << "\n";

    std::cout
        << "  Division             : "
        << divisionCount
        << "\n";

    std::cout
        << "  Modulus              : "
        << modulusCount
        << "\n";

    std::cout
        << "  Power                : "
        << powerCount
        << "\n";

    std::cout
        << "  Square Root          : "
        << squareRootCount
        << "\n";

    std::cout
        << "  Absolute Value       : "
        << absoluteCount
        << "\n";

    std::cout
        << "  Square               : "
        << squareCount
        << "\n";

    std::cout
        << "  Cube                 : "
        << cubeCount
        << "\n";

    std::cout
        << "  Factorial            : "
        << factorialCount
        << "\n";

    std::cout
        << "  Reciprocal           : "
        << reciprocalCount
        << "\n";

    std::cout
        << "  Percentage           : "
        << percentageCount
        << "\n";

    std::cout
        << "\nMost used operation   : "
        << getMostUsedOperation()
        << "\n";

    std::cout
        << "=======================================================\n";
}