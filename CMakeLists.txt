cmake_minimum_required(VERSION 3.14)
project(json_parser VERSION 1.0.0 LANGUAGES CXX)

# ============================================
# C++ Standard
# ============================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================
# Include directories
# ============================================
include_directories(${PROJECT_SOURCE_DIR}/include)

# ============================================
# Library (all parser logic, no main)
# ============================================

# Collect source files (exclude main.cpp)
file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_library(json_parser_lib ${SOURCES})

target_include_directories(json_parser_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# ============================================
# Executable (CLI)
# ============================================

add_executable(json_parser src/main.cpp)
target_link_libraries(json_parser json_parser_lib)

# ============================================
# Google Test
# ============================================

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# Prevent MSVC runtime conflicts
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ============================================
# Tests
# ============================================

file(GLOB_RECURSE TEST_SOURCES "${PROJECT_SOURCE_DIR}/tests/*.cpp")

add_executable(json_parser_tests ${TEST_SOURCES})

target_link_libraries(json_parser_tests
    json_parser_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(json_parser_tests)

# ============================================
# Convenience target
# ============================================

add_custom_target(run_tests
    COMMAND json_parser_tests
    DEPENDS json_parser_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
