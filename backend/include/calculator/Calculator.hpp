#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "history/HistoryManager.hpp"
#include "analytics/AnalyticsEngine.hpp"

#include <string>

struct CalculationResult {
    bool success;
    std::string operation;
    double firstOperand;
    double secondOperand;
    double result;
    std::string error;
};

class Calculator {
public:
    void run();

    HistoryManager& getHistoryManager();
    const HistoryManager& getHistoryManager() const;

    const AnalyticsEngine& getAnalyticsEngine() const;

    void clearCalculationHistory();

    CalculationResult calculate(
        const std::string& operation,
        double firstOperand,
        double secondOperand
    );

private:
    void displayMenu() const;
    void processChoice(int choice);

    void performAddition();
    void performSubtraction();
    void performMultiplication();
    void performDivision();
    void performModulus();

    void performPower();
    void performSquareRoot();
    void performAbsolute();
    void performSquare();
    void performCube();

    void performFactorial();
    void performReciprocal();
    void performPercentage();

    void viewHistory() const;
    void clearHistory();
    void viewAnalytics() const;

    double readNumber(const char* prompt);
    int readChoice();

    HistoryManager historyManager;
    AnalyticsEngine analyticsEngine;
};

#endif