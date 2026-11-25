# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.14)

# Project's name
project(everydo CXX C)
enable_testing()

# Set a default build type if none was specified
set(CMAKE_BUILD_TYPE "Debug")

# Set defines
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR "io_uring requires a Linux environment!")
endif ()

# Configure optional linking
include(CheckIPOSupported)
check_ipo_supported(RESULT lto_supported OUTPUT error)

if(lto_supported)
    message(STATUS "IPO / LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Let build executables load the selected GCC's C++ runtime.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_CROSSCOMPILING)
    execute_process(
        COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libstdc++.so.6
        RESULT_VARIABLE libstdcxx_result
        OUTPUT_VARIABLE libstdcxx_path
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if(libstdcxx_result STREQUAL "0" AND IS_ABSOLUTE "${libstdcxx_path}"
       AND EXISTS "${libstdcxx_path}")
        get_filename_component(libstdcxx_path "${libstdcxx_path}" REALPATH)
        get_filename_component(libstdcxx_dir "${libstdcxx_path}" DIRECTORY)
        if(NOT libstdcxx_dir MATCHES "^(/usr)?/lib(32|64|x32)?(/[^/]+-linux-[^/]+)?$")
            list(APPEND CMAKE_BUILD_RPATH "${libstdcxx_dir}")
        endif()
    endif()
endif()

include(FetchContent)

# Boost
FetchContent_Declare(
        Boost
        GIT_REPOSITORY "https://github.com/boostorg/boost.git"
        GIT_TAG "boost-1.92.0"
        GIT_PROGRESS TRUE
)
set(FETCHCONTENT_QUIET OFF)
message(STATUS "Preparing Boost (the first configure clones Boost and its submodules)")
set(BOOST_INCLUDE_LIBRARIES log)
FetchContent_MakeAvailable(Boost)
message(STATUS "Boost is ready")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(URING REQUIRED IMPORTED_TARGET liburing)

add_library(libeverydo STATIC "src/sqlite3.c" "src/everydo.hh" "src/everydo.cc" "src/exceptions.h")
target_link_libraries(libeverydo PUBLIC Boost::log)

add_executable(everydo_tests src/everydo_tests.cc)
target_link_libraries(everydo_tests PRIVATE libeverydo PkgConfig::URING)
add_test(NAME everydo_tests COMMAND everydo_tests)
