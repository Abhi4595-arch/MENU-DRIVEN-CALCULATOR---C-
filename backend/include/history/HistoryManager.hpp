#ifndef HISTORY_MANAGER_HPP
#define HISTORY_MANAGER_HPP

#include "database/Database.hpp"
#include "models/Calculation.hpp"

#include <string>
#include <vector>

class HistoryManager {
public:
    HistoryManager();

    void addRecord(
        const std::string& operation,
        double firstOperand,
        double secondOperand,
        double result
    );

    void displayHistory() const;

    void clearHistory();

    bool empty() const;

    std::size_t size() const;
    const std::vector<CalculationRecord>& getRecords() const;

private:
    std::vector<CalculationRecord> records;
    Database database;
    int nextId;

    void loadFromDatabase();
};

#endif