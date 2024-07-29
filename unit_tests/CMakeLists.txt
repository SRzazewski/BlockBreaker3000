include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(BlockBreaker3000_tests
    tests.cpp
)

target_link_libraries(BlockBreaker3000_tests
    PRIVATE
        GTest::gtest_main
        BlockBreaker3000::BlockBreaker3000_core
)

target_include_directories(BlockBreaker3000_tests
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}
)

include(GoogleTest)
gtest_discover_tests(BlockBreaker3000_tests)