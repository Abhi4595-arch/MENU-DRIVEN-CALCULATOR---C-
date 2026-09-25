#include "api/Controllers.hpp"
#include "calculator/Calculator.hpp"

#include <sstream>
#include <string>

namespace {

bool extractJsonValue(
    const std::string& json,
    const std::string& key,
    std::string& value
) {
    const std::string quotedPattern =
        "\"" + key + "\"";

    std::size_t keyPos =
        json.find(quotedPattern);

    if (keyPos == std::string::npos) {
        return false;
    }

    std::size_t colonPos =
        json.find(':', keyPos + quotedPattern.size());

    if (colonPos == std::string::npos) {
        return false;
    }

    std::size_t start =
        colonPos + 1;

    while (
        start < json.size() &&
        (
            json[start] == ' ' ||
            json[start] == '\t' ||
            json[start] == '\r' ||
            json[start] == '\n'
        )
    ) {
        ++start;
    }

    if (start >= json.size()) {
        return false;
    }

    /*
     * String value.
     *
     * Example:
     * "operation":"+"
     */
    if (json[start] == '"') {

        ++start;

        std::size_t end =
            json.find('"', start);

        if (end == std::string::npos) {
            return false;
        }

        value =
            json.substr(
                start,
                end - start
            );

        return true;
    }

    /*
     * Numeric value.
     *
     * Example:
     * "a":10
     */
    std::size_t end = start;

    while (
        end < json.size() &&
        json[end] != ',' &&
        json[end] != '}'
    ) {
        ++end;
    }

    value =
        json.substr(
            start,
            end - start
        );

    while (
        !value.empty() &&
        (
            value.back() == ' ' ||
            value.back() == '\t' ||
            value.back() == '\r' ||
            value.back() == '\n'
        )
    ) {
        value.pop_back();
    }

    return !value.empty();
}

std::string escapeJson(
    const std::string& value
) {
    std::string result;

    for (char character : value) {

        if (character == '"') {
            result += "\\\"";
        }
        else if (character == '\\') {
            result += "\\\\";
        }
        else {
            result += character;
        }
    }

    return result;
}

}

// ============================================================
// HEALTH
// ============================================================

HttpResponse Controllers::health() {

    HttpResponse response;

    response.statusCode = 200;
    response.contentType = "application/json";

    response.body =
        "{"
        "\"success\":true,"
        "\"service\":\"MENU DRIVEN CALCULATOR\","
        "\"status\":\"online\""
        "}";

    return response;
}

// ============================================================
// CALCULATE
// ============================================================

HttpResponse Controllers::calculate(
    Calculator& calculator,
    const HttpRequest& request
) {
    HttpResponse response;

    response.contentType =
        "application/json";

    std::string operation;
    std::string firstText;
    std::string secondText;

    bool operationFound =
        extractJsonValue(
            request.body,
            "operation",
            operation
        );

    bool firstFound =
        extractJsonValue(
            request.body,
            "a",
            firstText
        );

    bool secondFound =
        extractJsonValue(
            request.body,
            "b",
            secondText
        );

    /*
     * Operation and first operand are required.
     */
    if (
        !operationFound ||
        !firstFound
    ) {
        response.statusCode = 400;

        response.body =
            "{"
            "\"success\":false,"
            "\"error\":\"Invalid request. Required fields: operation and a\""
            "}";

        return response;
    }

    /*
     * Unary operations.
     */
    bool unaryOperation =
        operation == "sqrt" ||
        operation == "abs" ||
        operation == "sq" ||
        operation == "cube" ||
        operation == "!" ||
        operation == "1/x";

    /*
     * All binary operations require b.
     */
    if (
        !unaryOperation &&
        !secondFound
    ) {
        response.statusCode = 400;

        response.body =
            "{"
            "\"success\":false,"
            "\"error\":\"Invalid request. This operation requires fields: a and b\""
            "}";

        return response;
    }

    try {

        double first =
            std::stod(firstText);

        double second = 0.0;

        if (secondFound) {
            second =
                std::stod(secondText);
        }

        CalculationResult result =
            calculator.calculate(
                operation,
                first,
                second
            );

        if (!result.success) {

            response.statusCode = 400;

            response.body =
                "{"
                "\"success\":false,"
                "\"error\":\"" +
                escapeJson(result.error) +
                "\""
                "}";

            return response;
        }

        response.statusCode = 200;

        std::ostringstream body;

        body
            << "{"
            << "\"success\":true,"
            << "\"operation\":\""
            << escapeJson(result.operation)
            << "\","
            << "\"a\":"
            << result.firstOperand
            << ","
            << "\"b\":"
            << result.secondOperand
            << ","
            << "\"result\":"
            << result.result
            << "}";

        response.body =
            body.str();

        return response;
    }
    catch (const std::exception&) {

        response.statusCode = 400;

        response.body =
            "{"
            "\"success\":false,"
            "\"error\":\"Invalid numeric values\""
            "}";

        return response;
    }
}

// ============================================================
// HISTORY
// ============================================================

HttpResponse Controllers::history(
    Calculator& calculator
) {
    HttpResponse response;

    response.statusCode = 200;
    response.contentType = "application/json";

    const HistoryManager& historyManager =
        calculator.getHistoryManager();

    std::ostringstream body;

    body << "{";

    body << "\"success\":true,";

    body
        << "\"count\":"
        << historyManager.size()
        << ",";

    body << "\"history\":[";

    const std::vector<CalculationRecord>& records =
        historyManager.getRecords();

    for (
        std::size_t i = 0;
        i < records.size();
        ++i
    ) {
        const CalculationRecord& record =
            records[i];

        if (i > 0) {
            body << ",";
        }

        body << "{";

        body
            << "\"id\":"
            << record.id
            << ",";

        body
            << "\"operation\":\""
            << escapeJson(record.operation)
            << "\",";

        body
            << "\"a\":"
            << record.firstOperand
            << ",";

        body
            << "\"b\":"
            << record.secondOperand
            << ",";

        body
            << "\"result\":"
            << record.result;

        body << "}";
    }

    body << "]";

    body << "}";

    response.body =
        body.str();

    return response;
}

// ============================================================
// CLEAR HISTORY
// ============================================================

HttpResponse Controllers::clearHistory(
    Calculator& calculator
) {
    HttpResponse response;

    response.statusCode = 200;
    response.contentType = "application/json";

    calculator.clearCalculationHistory();

    response.body =
        "{"
        "\"success\":true,"
        "\"message\":\"Calculation history cleared\""
        "}";

    return response;
}

// ============================================================
// ANALYTICS
// ============================================================

HttpResponse Controllers::analytics(
    Calculator& calculator
) {
    HttpResponse response;

    response.statusCode = 200;
    response.contentType = "application/json";

    const AnalyticsEngine& analyticsEngine =
        calculator.getAnalyticsEngine();

    std::ostringstream body;

    body << "{";

    body << "\"success\":true,";

    body << "\"analytics\":{";

    body
        << "\"totalCalculations\":"
        << analyticsEngine.getTotalCalculations()
        << ",";

    body
        << "\"successfulCalculations\":"
        << analyticsEngine.getSuccessfulCalculations()
        << ",";

    body
        << "\"failedCalculations\":"
        << analyticsEngine.getFailedCalculations()
        << ",";

    body
        << "\"successRate\":"
        << analyticsEngine.getSuccessRate()
        << ",";

    body
        << "\"additionCount\":"
        << analyticsEngine.getAdditionCount()
        << ",";

    body
        << "\"subtractionCount\":"
        << analyticsEngine.getSubtractionCount()
        << ",";

    body
        << "\"multiplicationCount\":"
        << analyticsEngine.getMultiplicationCount()
        << ",";

    body
        << "\"divisionCount\":"
        << analyticsEngine.getDivisionCount()
        << ",";

    body
        << "\"modulusCount\":"
        << analyticsEngine.getModulusCount()
        << ",";

    body
        << "\"powerCount\":"
        << analyticsEngine.getPowerCount()
        << ",";

    body
        << "\"squareRootCount\":"
        << analyticsEngine.getSquareRootCount()
        << ",";

    body
        << "\"absoluteCount\":"
        << analyticsEngine.getAbsoluteCount()
        << ",";

    body
        << "\"squareCount\":"
        << analyticsEngine.getSquareCount()
        << ",";

    body
        << "\"cubeCount\":"
        << analyticsEngine.getCubeCount()
        << ",";

    body
        << "\"factorialCount\":"
        << analyticsEngine.getFactorialCount()
        << ",";

    body
        << "\"reciprocalCount\":"
        << analyticsEngine.getReciprocalCount()
        << ",";

    body
        << "\"percentageCount\":"
        << analyticsEngine.getPercentageCount()
        << ",";

    body
        << "\"mostUsedOperation\":\""
        << escapeJson(
            analyticsEngine.getMostUsedOperation()
        )
        << "\"";

    body << "}";

    body << "}";

    response.body =
        body.str();

    return response;
}