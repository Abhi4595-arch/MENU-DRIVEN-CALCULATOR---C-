#include "analytics/AnalyticsEngine.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    AnalyticsEngine analytics;

    // Initial state
    assert(analytics.getTotalCalculations() == 0);
    assert(analytics.getSuccessfulCalculations() == 0);
    assert(analytics.getFailedCalculations() == 0);
    assert(std::abs(analytics.getSuccessRate() - 0.0) < 1e-9);
    assert(analytics.getMostUsedOperation() == "None");

    // Successful operations
    analytics.recordSuccess("+");
    analytics.recordSuccess("+");
    analytics.recordSuccess("/");
    analytics.recordSuccess("sqrt");

    assert(analytics.getTotalCalculations() == 4);
    assert(analytics.getSuccessfulCalculations() == 4);
    assert(analytics.getFailedCalculations() == 0);

    assert(analytics.getAdditionCount() == 2);
    assert(analytics.getDivisionCount() == 1);
    assert(analytics.getSquareRootCount() == 1);

    assert(
        std::abs(analytics.getSuccessRate() - 100.0) < 1e-9
    );

    assert(
        analytics.getMostUsedOperation() == "Addition"
    );

    // Failed operation
    analytics.recordFailure();

    assert(analytics.getTotalCalculations() == 5);
    assert(analytics.getSuccessfulCalculations() == 4);
    assert(analytics.getFailedCalculations() == 1);

    assert(
        std::abs(analytics.getSuccessRate() - 80.0) < 1e-9
    );

    // Reset
    analytics.reset();

    assert(analytics.getTotalCalculations() == 0);
    assert(analytics.getSuccessfulCalculations() == 0);
    assert(analytics.getFailedCalculations() == 0);

    assert(analytics.getAdditionCount() == 0);
    assert(analytics.getDivisionCount() == 0);
    assert(analytics.getSquareRootCount() == 0);

    assert(std::abs(analytics.getSuccessRate()) < 1e-9);
    assert(analytics.getMostUsedOperation() == "None");

    std::cout << "Analytics tests passed.\n";

    return 0;
}
