set(BACKEND_NAME menu_calculator)

add_executable(${BACKEND_NAME}
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