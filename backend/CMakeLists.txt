set(BACKEND_NAME menu_calculator)

set(BACKEND_SOURCES
    src/main.cpp

    src/calculator/Calculator.cpp
    src/calculator/Operations.cpp
    src/calculator/OperationRegistry.cpp

    src/validation/Validator.cpp

    src/history/HistoryManager.cpp

    src/analytics/AnalyticsEngine.cpp

    src/database/Database.cpp

    src/api/Server.cpp
    src/api/Router.cpp
    src/api/Controllers.cpp

    src/logging/Logger.cpp

    src/models/Calculation.cpp
    src/models/ApiResponse.cpp
)

add_executable(${BACKEND_NAME}
    ${BACKEND_SOURCES}
)

target_include_directories(${BACKEND_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    target_link_libraries(${BACKEND_NAME}
        PRIVATE
            ws2_32
    )
endif()


# ============================================================
# TESTS
# ============================================================

enable_testing()

set(TEST_COMMON_SOURCES
    src/calculator/Calculator.cpp
    src/calculator/Operations.cpp
    src/calculator/OperationRegistry.cpp

    src/validation/Validator.cpp

    src/history/HistoryManager.cpp

    src/analytics/AnalyticsEngine.cpp

    src/database/Database.cpp

    src/logging/Logger.cpp

    src/models/Calculation.cpp
    src/models/ApiResponse.cpp
)


# ============================================================
# CALCULATOR TESTS
# ============================================================

add_executable(calculator_tests
    tests/CalculatorTests.cpp
    ${TEST_COMMON_SOURCES}
)

target_include_directories(calculator_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    target_link_libraries(calculator_tests
        PRIVATE
            ws2_32
    )
endif()

add_test(
    NAME CalculatorTests
    COMMAND calculator_tests
)


# ============================================================
# HISTORY TESTS
# ============================================================

add_executable(history_tests
    tests/HistoryTests.cpp
    ${TEST_COMMON_SOURCES}
)

target_include_directories(history_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    target_link_libraries(history_tests
        PRIVATE
            ws2_32
    )
endif()

add_test(
    NAME HistoryTests
    COMMAND history_tests
)


# ============================================================
# ANALYTICS TESTS
# ============================================================

add_executable(analytics_tests
    tests/AnalyticsTests.cpp
    ${TEST_COMMON_SOURCES}
)

target_include_directories(analytics_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(WIN32)
    target_link_libraries(analytics_tests
        PRIVATE
            ws2_32
    )
endif()

add_test(
    NAME AnalyticsTests
    COMMAND analytics_tests
)