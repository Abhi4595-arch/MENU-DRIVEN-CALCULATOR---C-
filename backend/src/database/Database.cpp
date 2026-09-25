#include "database/Database.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

Database::Database(const std::string& filename)
    : filename(filename) {
    ensureDirectory();
}

bool Database::ensureDirectory() const {
    try {
        std::filesystem::path path(filename);
        std::filesystem::path directory = path.parent_path();

        if (!directory.empty() &&
            !std::filesystem::exists(directory)) {
            std::filesystem::create_directories(directory);
        }

        return true;
    }
    catch (...) {
        return false;
    }
}

bool Database::saveRecord(const CalculationRecord& record) {
    try {
        if (!ensureDirectory()) {
            return false;
        }

        std::ofstream file(filename, std::ios::app);

        if (!file.is_open()) {
            return false;
        }

        file << record.id << '|'
             << record.operation << '|'
             << record.firstOperand << '|'
             << record.secondOperand << '|'
             << record.result
             << '\n';

        return file.good();
    }
    catch (...) {
        return false;
    }
}

std::vector<CalculationRecord> Database::loadRecords() const {
    std::vector<CalculationRecord> records;

    std::ifstream file(filename);

    if (!file.is_open()) {
        return records;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream stream(line);

        std::string idText;
        std::string operation;
        std::string firstOperandText;
        std::string secondOperandText;
        std::string resultText;

        std::getline(stream, idText, '|');
        std::getline(stream, operation, '|');
        std::getline(stream, firstOperandText, '|');
        std::getline(stream, secondOperandText, '|');
        std::getline(stream, resultText, '|');

        if (
            idText.empty() ||
            operation.empty() ||
            firstOperandText.empty() ||
            secondOperandText.empty() ||
            resultText.empty()
        ) {
            continue;
        }

        try {
            CalculationRecord record;

            record.id = std::stoi(idText);
            record.operation = operation;
            record.firstOperand = std::stod(firstOperandText);
            record.secondOperand = std::stod(secondOperandText);
            record.result = std::stod(resultText);

            records.push_back(record);
        }
        catch (...) {
            // Ignore malformed database records.
        }
    }

    return records;
}

bool Database::clear() {
    try {
        std::ofstream file(filename, std::ios::trunc);

        return file.good();
    }
    catch (...) {
        return false;
    }
}

bool Database::isAvailable() const {
    std::ifstream file(filename);

    return file.good();
}