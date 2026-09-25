#ifndef ANALYTICS_ENGINE_HPP
#define ANALYTICS_ENGINE_HPP

#include <string>

class AnalyticsEngine {
public:
    void recordSuccess(const std::string& operation);
    void recordFailure();
    void reset();

    int getTotalCalculations() const;
    int getSuccessfulCalculations() const;
    int getFailedCalculations() const;

    int getAdditionCount() const;
    int getSubtractionCount() const;
    int getMultiplicationCount() const;
    int getDivisionCount() const;
    int getModulusCount() const;

    int getPowerCount() const;
    int getSquareRootCount() const;
    int getAbsoluteCount() const;
    int getSquareCount() const;
    int getCubeCount() const;
    int getFactorialCount() const;
    int getReciprocalCount() const;
    int getPercentageCount() const;

    double getSuccessRate() const;

    std::string getMostUsedOperation() const;

    void displayAnalytics() const;

private:
    int totalCalculations = 0;
    int successfulCalculations = 0;
    int failedCalculations = 0;

    int additionCount = 0;
    int subtractionCount = 0;
    int multiplicationCount = 0;
    int divisionCount = 0;
    int modulusCount = 0;

    int powerCount = 0;
    int squareRootCount = 0;
    int absoluteCount = 0;
    int squareCount = 0;
    int cubeCount = 0;
    int factorialCount = 0;
    int reciprocalCount = 0;
    int percentageCount = 0;
};

#endif