cmake_minimum_required(VERSION 3.20)

project(MenuDrivenCalculator
    VERSION 1.0.0
    DESCRIPTION "Menu Driven Calculator with C++ Backend and SaaS Web Interface"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Enable CTest
enable_testing()

# Backend
add_subdirectory(backend)