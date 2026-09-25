#ifndef CALCULATION_HPP
#define CALCULATION_HPP

#include <string>
#include "models/Calculation.hpp"

struct CalculationRecord {
    int id;
    std::string operation;
    double firstOperand;
    double secondOperand;
    double result;
};

#endif