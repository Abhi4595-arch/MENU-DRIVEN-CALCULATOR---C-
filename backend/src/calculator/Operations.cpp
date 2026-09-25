#include "calculator/Operations.hpp"

#include <cmath>
#include <stdexcept>

namespace CalculatorOperations {

    double add(double a, double b) {
        return a + b;
    }

    double subtract(double a, double b) {
        return a - b;
    }

    double multiply(double a, double b) {
        return a * b;
    }

    double divide(double a, double b) {
        if (b == 0.0) {
            throw std::invalid_argument(
                "Division by zero is not allowed."
            );
        }

        return a / b;
    }

    long long modulus(long long a, long long b) {
        if (b == 0) {
            throw std::invalid_argument(
                "Modulus by zero is not allowed."
            );
        }

        return a % b;
    }

    double power(double a, double b) {
        double result = std::pow(a, b);

        if (!std::isfinite(result)) {
            throw std::out_of_range(
                "Power result is outside the supported numeric range."
            );
        }

        return result;
    }

    double squareRoot(double a) {
        if (a < 0.0) {
            throw std::invalid_argument(
                "Square root of a negative number is not allowed."
            );
        }

        return std::sqrt(a);
    }

    double absolute(double a) {
        return std::fabs(a);
    }

    double square(double a) {
        double result = a * a;

        if (!std::isfinite(result)) {
            throw std::out_of_range(
                "Square result is outside the supported numeric range."
            );
        }

        return result;
    }

    double cube(double a) {
        double result = a * a * a;

        if (!std::isfinite(result)) {
            throw std::out_of_range(
                "Cube result is outside the supported numeric range."
            );
        }

        return result;
    }

    double factorial(double a) {
        if (!std::isfinite(a)) {
            throw std::invalid_argument(
                "Factorial requires a finite number."
            );
        }

        if (a < 0.0) {
            throw std::invalid_argument(
                "Factorial of a negative number is not allowed."
            );
        }

        if (std::floor(a) != a) {
            throw std::invalid_argument(
                "Factorial requires a non-negative integer."
            );
        }

        if (a > 20.0) {
            throw std::out_of_range(
                "Factorial is supported only up to 20."
            );
        }

        double result = 1.0;

        for (long long i = 2; i <= static_cast<long long>(a); ++i) {
            result *= static_cast<double>(i);
        }

        return result;
    }

    double reciprocal(double a) {
        if (a == 0.0) {
            throw std::invalid_argument(
                "Reciprocal of zero is not allowed."
            );
        }

        return 1.0 / a;
    }

    double percentage(double a, double b) {
        double result = (a / 100.0) * b;

        if (!std::isfinite(result)) {
            throw std::out_of_range(
                "Percentage result is outside the supported numeric range."
            );
        }

        return result;
    }

}