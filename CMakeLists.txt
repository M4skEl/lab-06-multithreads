cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
        SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)


project(lab-06-multithreads VERSION 0.1.0)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(Boost COMPONENTS log thread)
find_package(Boost CONFIG REQUIRED log thread)
hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(lab-06-multithreads STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp
        sources/HashData.cpp include/HashData.h)

add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )

add_executable(main
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.cpp)

target_link_libraries(lab-06-multithreads  Boost::log Boost::thread)
target_link_libraries(tests Boost::log Boost::thread)
target_link_libraries(main Boost::log Boost::thread)

target_include_directories(lab-06-multithreads
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_include_directories(tests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_include_directories(main
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_link_libraries(tests GTest::gtest_main lab-06-multithreads)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third-party/PicoSHA2/)
enable_testing()
add_test(NAME unit_tests COMMAND tests)

if (BUILD_COVERAGE)
    function(ENABLE_PROJECT_COVERAGE PROJECT)
        target_compile_options(${PROJECT} INTERFACE -O0 -g --coverage)
        if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
            target_link_options(${PROJECT} INTERFACE --coverage)
        else ()
            target_link_libraries(${PROJECT} INTERFACE --coverage)
        endif ()
    endfunction()

    set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/CMake-codecov/cmake")
    find_package(codecov)
    enable_project_coverage(lab-06-multithreads)
    enable_project_coverage(tests)
    list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
    coverage_evaluate()
endif ()
