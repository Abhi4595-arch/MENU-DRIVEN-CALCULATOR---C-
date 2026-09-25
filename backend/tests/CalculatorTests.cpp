#include "calculator/Calculator.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

bool nearlyEqual(double a, double b) {
    return std::abs(a - b) < 1e-9;
}

int main() {
    Calculator calculator;

    calculator.clearCalculationHistory();

    // Addition
    auto addition = calculator.calculate("+", 10.0, 5.0);
    assert(addition.success);
    assert(nearlyEqual(addition.result, 15.0));

    // Subtraction
    auto subtraction = calculator.calculate("-", 10.0, 5.0);
    assert(subtraction.success);
    assert(nearlyEqual(subtraction.result, 5.0));

    // Multiplication
    auto multiplication = calculator.calculate("*", 10.0, 5.0);
    assert(multiplication.success);
    assert(nearlyEqual(multiplication.result, 50.0));

    // Division
    auto division = calculator.calculate("/", 10.0, 5.0);
    assert(division.success);
    assert(nearlyEqual(division.result, 2.0));

    // Division by zero
    auto divisionByZero = calculator.calculate("/", 10.0, 0.0);
    assert(!divisionByZero.success);
    assert(!divisionByZero.error.empty());

    // Modulus
    auto modulus = calculator.calculate("%", 10.0, 3.0);
    assert(modulus.success);
    assert(nearlyEqual(modulus.result, 1.0));

    // Power
    auto power = calculator.calculate("^", 2.0, 3.0);
    assert(power.success);
    assert(nearlyEqual(power.result, 8.0));

    // Square root
    auto squareRoot = calculator.calculate("sqrt", 25.0, 0.0);
    assert(squareRoot.success);
    assert(nearlyEqual(squareRoot.result, 5.0));

    // Square root of negative number
    auto invalidSquareRoot =
        calculator.calculate("sqrt", -25.0, 0.0);

    assert(!invalidSquareRoot.success);
    assert(!invalidSquareRoot.error.empty());

    // Absolute
    auto absolute = calculator.calculate("abs", -15.0, 0.0);
    assert(absolute.success);
    assert(nearlyEqual(absolute.result, 15.0));

    // Square
    auto square = calculator.calculate("sq", 6.0, 0.0);
    assert(square.success);
    assert(nearlyEqual(square.result, 36.0));

    // Cube
    auto cube = calculator.calculate("cube", 4.0, 0.0);
    assert(cube.success);
    assert(nearlyEqual(cube.result, 64.0));

    // Factorial
    auto factorial = calculator.calculate("!", 5.0, 0.0);
    assert(factorial.success);
    assert(nearlyEqual(factorial.result, 120.0));

    // Invalid factorial
    auto invalidFactorial =
        calculator.calculate("!", 5.5, 0.0);

    assert(!invalidFactorial.success);
    assert(!invalidFactorial.error.empty());

    // Reciprocal
    auto reciprocal = calculator.calculate("1/x", 4.0, 0.0);
    assert(reciprocal.success);
    assert(nearlyEqual(reciprocal.result, 0.25));

    // Reciprocal of zero
    auto invalidReciprocal =
        calculator.calculate("1/x", 0.0, 0.0);

    assert(!invalidReciprocal.success);
    assert(!invalidReciprocal.error.empty());

    // Percentage
    auto percentage =
        calculator.calculate("percent", 25.0, 200.0);

    assert(percentage.success);
    assert(nearlyEqual(percentage.result, 50.0));

    // Unsupported operation
    auto unsupported =
        calculator.calculate("invalid", 10.0, 5.0);

    assert(!unsupported.success);
    assert(!unsupported.error.empty());

    // History should contain only successful calculations.
    const auto& history =
        calculator.getHistoryManager().getRecords();

    assert(history.size() == 13);

    std::cout << "Calculator tests passed.\n";

    return 0;
}
