#include "history/HistoryManager.hpp"

#include <iostream>

HistoryManager::HistoryManager()
    : nextId(1) {
    loadFromDatabase();
}

void HistoryManager::loadFromDatabase() {
    records = database.loadRecords();

    if (!records.empty()) {
        nextId = records.back().id + 1;
    }
}

void HistoryManager::addRecord(
    const std::string& operation,
    double firstOperand,
    double secondOperand,
    double result
) {
    CalculationRecord record;

    record.id = nextId++;
    record.operation = operation;
    record.firstOperand = firstOperand;
    record.secondOperand = secondOperand;
    record.result = result;

    records.push_back(record);

    if (!database.saveRecord(record)) {
        std::cerr << "Warning: Failed to persist calculation.\n";
    }
}

void HistoryManager::displayHistory() const {
    if (records.empty()) {
        std::cout << "\nNo calculation history available.\n";
        return;
    }

    std::cout << "\n";
    std::cout << "================ CALCULATION HISTORY ================\n";

    for (const CalculationRecord& record : records) {
        std::cout << "["
                  << record.id
                  << "] "
                  << record.firstOperand
                  << " "
                  << record.operation
                  << " "
                  << record.secondOperand
                  << " = "
                  << record.result
                  << "\n";
    }

    std::cout << "======================================================\n";
}

void HistoryManager::clearHistory() {
    records.clear();
    nextId = 1;

    if (!database.clear()) {
        std::cerr << "Warning: Failed to clear persistent history.\n";
    }
}

bool HistoryManager::empty() const {
    return records.empty();
}

std::size_t HistoryManager::size() const {
    return records.size();
}
const std::vector<CalculationRecord>&
HistoryManager::getRecords() const {
    return records;
}