cmake_minimum_required(VERSION 3.20)
project(shapes_demo VERSION 1.0.0 LANGUAGES CXX)

option(SHAPES_ENABLE_SANITIZERS "Enable address, leak, and undefined-behavior sanitizers" OFF)
option(SHAPES_BUILD_TESTS "Build the GoogleTest suite" ON)
option(SHAPES_ENABLE_COVERAGE "Instrument the library for gcov/lcov code coverage" OFF)

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

if(SHAPES_ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(shapes PUBLIC --coverage -O0 -g)
    target_link_options(shapes PUBLIC --coverage)
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

    if(SHAPES_ENABLE_COVERAGE)
        find_program(LCOV_EXECUTABLE lcov REQUIRED)
        find_program(GENHTML_EXECUTABLE genhtml REQUIRED)

        # lcov 2.x treats unmatched --remove patterns and gcc line mismatches as errors.
        execute_process(COMMAND ${LCOV_EXECUTABLE} --version OUTPUT_VARIABLE LCOV_VERSION_OUTPUT)
        string(REGEX MATCH "[0-9]+\\.[0-9]+" LCOV_VERSION "${LCOV_VERSION_OUTPUT}")
        set(LCOV_EXTRA_ARGS "")
        if(LCOV_VERSION VERSION_GREATER_EQUAL 2.0)
            set(LCOV_EXTRA_ARGS --ignore-errors mismatch,unused)
        endif()

        set(COVERAGE_INFO ${CMAKE_BINARY_DIR}/coverage.info)
        set(COVERAGE_HTML ${CMAKE_BINARY_DIR}/coverage)

        add_custom_target(coverage
            COMMAND ${LCOV_EXECUTABLE} --zerocounters --directory ${CMAKE_BINARY_DIR}
            COMMAND ${CMAKE_CTEST_COMMAND} --test-dir ${CMAKE_BINARY_DIR} --output-on-failure
            COMMAND ${LCOV_EXECUTABLE} --capture --directory ${CMAKE_BINARY_DIR}
                    --base-directory ${CMAKE_SOURCE_DIR} --output-file ${COVERAGE_INFO} ${LCOV_EXTRA_ARGS}
            COMMAND ${LCOV_EXECUTABLE} --remove ${COVERAGE_INFO} "/usr/*" "*/_deps/*" "*/tests/*"
                    --output-file ${COVERAGE_INFO} ${LCOV_EXTRA_ARGS}
            COMMAND ${LCOV_EXECUTABLE} --list ${COVERAGE_INFO}
            COMMAND ${GENHTML_EXECUTABLE} ${COVERAGE_INFO} --output-directory ${COVERAGE_HTML}
                    --title "Shapes Demo" --legend ${LCOV_EXTRA_ARGS}
            COMMAND ${CMAKE_COMMAND} -E echo "Coverage report: ${COVERAGE_HTML}/index.html"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            DEPENDS shapes_tests
            COMMENT "Running tests and generating lcov coverage report"
            VERBATIM
        )
    endif()
endif()