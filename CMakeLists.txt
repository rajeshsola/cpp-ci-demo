cmake_minimum_required(VERSION 3.20)
project(shapes_demo VERSION 1.0.0 LANGUAGES CXX)

option(SHAPES_ENABLE_SANITIZERS "Enable address, leak, and undefined-behavior sanitizers" OFF)
option(SHAPES_BUILD_TESTS "Build the GoogleTest suite" ON)

add_library(shapes
    src/circle.cpp
    src/triangle.cpp
)
target_include_directories(shapes PUBLIC include)
target_compile_features(shapes PUBLIC cxx_std_20)
target_compile_options(shapes PRIVATE -Wall -Wextra -Wpedantic -Werror)

if(SHAPES_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(shapes PUBLIC -fsanitize=address,leak,undefined -fno-omit-frame-pointer)
    target_link_options(shapes PUBLIC -fsanitize=address,leak,undefined -fno-omit-frame-pointer)
endif()

if(SHAPES_BUILD_TESTS)
    include(CTest)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(shapes_tests tests/shapes_test.cpp)
    target_link_libraries(shapes_tests PRIVATE shapes GTest::gtest_main)
    target_compile_options(shapes_tests PRIVATE -Wall -Wextra -Wpedantic -Werror)

    include(GoogleTest)
    gtest_discover_tests(shapes_tests)
endif()