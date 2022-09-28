# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.14)

# Project's name
project(everydo CXX C)
enable_testing()

# Set a default build type if none was specified
set(CMAKE_BUILD_TYPE "Debug")

include(FetchContent)

# Catch2
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
        GIT_TAG "v3.1.0"
)
FetchContent_MakeAvailable(Catch2)

# Boost
FetchContent_Declare(
        Boost
        GIT_REPOSITORY "https://github.com/boostorg/boost.git"
        GIT_TAG "boost-1.80.0"
)
FetchContent_MakeAvailable(Boost)

# Configure optional linking
include(CheckIPOSupported)
check_ipo_supported(RESULT lto_supported OUTPUT error)

if(lto_supported)
    message(STATUS "IPO / LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Set defines
set(CMAKE_CXX_STANDARD 20)

add_library(libeverydo STATIC "src/sqlite3.c" "src/everydo.hh" "src/everydo.cc" "src/exceptions.h"
        "${Boost_INCLUDE_DIRS}")

add_executable(testexecuter "src/testexecuter.cc")
target_link_libraries(testexecuter libeverydo Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(testexecuter)