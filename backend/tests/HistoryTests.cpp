#include "history/HistoryManager.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    HistoryManager history;

    // Start from a clean state.
    history.clearHistory();

    assert(history.empty());
    assert(history.size() == 0);

    // Add first record.
    history.addRecord("+", 10.0, 5.0, 15.0);

    assert(!history.empty());
    assert(history.size() == 1);

    const auto& records = history.getRecords();

    assert(records.size() == 1);
    assert(records[0].id == 1);
    assert(records[0].operation == "+");
    assert(std::abs(records[0].firstOperand - 10.0) < 1e-9);
    assert(std::abs(records[0].secondOperand - 5.0) < 1e-9);
    assert(std::abs(records[0].result - 15.0) < 1e-9);

    // Add second record.
    history.addRecord("*", 4.0, 3.0, 12.0);

    assert(history.size() == 2);

    assert(records[1].id == 2);
    assert(records[1].operation == "*");
    assert(std::abs(records[1].result - 12.0) < 1e-9);

    // Clear history.
    history.clearHistory();

    assert(history.empty());
    assert(history.size() == 0);
    assert(history.getRecords().empty());

    std::cout << "History tests passed.\n";

    return 0;
}
