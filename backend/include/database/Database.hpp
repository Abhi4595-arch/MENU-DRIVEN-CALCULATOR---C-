#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "models/Calculation.hpp"

#include <string>
#include <vector>

class Database {
public:
    explicit Database(
        const std::string& filename = "data/calculations.db"
    );

    bool saveRecord(const CalculationRecord& record);

    std::vector<CalculationRecord> loadRecords() const;

    bool clear();

    bool isAvailable() const;

private:
    std::string filename;

    bool ensureDirectory() const;
};

#endif