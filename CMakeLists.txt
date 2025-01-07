cmake_minimum_required(VERSION 3.25)
project(BlockBreaker3000 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0)
FetchContent_MakeAvailable(SFML)

set(BUILD_TESTS ON CACHE BOOL "Includes tests to build process")

add_subdirectory(src)

if(BUILD_TESTS)
    add_subdirectory(unit_tests)
endif()

install(TARGETS BlockBreaker3000)