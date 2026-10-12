# Shapes Demo

[![Tests](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/tests.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/tests.yml)
[![Static Analysis](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/static-analysis.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/static-analysis.yml)
[![Memory Check](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/memory-check.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/memory-check.yml)
[![Documentation](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/docs.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/docs.yml)
[![Coverage](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/coverage.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/coverage.yml)
![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?logo=cplusplus)
![CMake 3.20+](https://img.shields.io/badge/CMake-3.20%2B-064F8C?logo=cmake)

A small C++ library that models circles and triangles through a shared `Shape` interface. Constructors reject non-finite or non-positive dimensions, and triangles also enforce the triangle inequality.

## CI status

- [![Tests](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/tests.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/tests.yml) — Builds the library and runs the GoogleTest suite with `ctest`.
- [![Static Analysis](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/static-analysis.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/static-analysis.yml) — Runs clang-tidy over the library sources using the checks in `.clang-tidy`.
- [![Memory Check](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/memory-check.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/memory-check.yml) — Runs the tests under AddressSanitizer, LeakSanitizer, and UndefinedBehaviorSanitizer; fails on any leak or memory error.
- [![Documentation](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/docs.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/docs.yml) — Generates the Doxygen API docs; any Doxygen warning fails the build.
- [![Coverage](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/coverage.yml/badge.svg)](https://github.com/rajeshsola/cpp-ci-demo/actions/workflows/coverage.yml) — Builds with gcov instrumentation, runs the tests, and uploads an lcov HTML coverage report as a workflow artifact.

## Build and test

Requirements: CMake 3.20+, a C++20 compiler, and network access on the first configure so CMake can fetch GoogleTest.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

To run tests with AddressSanitizer, LeakSanitizer, and UndefinedBehaviorSanitizer:

```sh
cmake -S . -B build-sanitized -DCMAKE_BUILD_TYPE=Debug -DSHAPES_ENABLE_SANITIZERS=ON
cmake --build build-sanitized --parallel
ASAN_OPTIONS=detect_leaks=1 ctest --test-dir build-sanitized --output-on-failure
```

## Code coverage

Install lcov (for example `sudo apt-get install lcov`), then build with coverage instrumentation and run the `coverage` target:

```sh
cmake -S . -B build-coverage -DCMAKE_BUILD_TYPE=Debug -DSHAPES_ENABLE_COVERAGE=ON
cmake --build build-coverage --parallel
cmake --build build-coverage --target coverage
```

The `coverage` target resets the counters, runs the test suite, captures the results with lcov (excluding system headers, GoogleTest, and the tests themselves), and prints a per-file summary. The HTML report is generated at `build-coverage/coverage/index.html` and the raw tracefile at `build-coverage/coverage.info`.

## API documentation

Install Doxygen, then run `doxygen Doxyfile`. The HTML API reference is generated at `docs/api/html/index.html`.

## UML

The class diagram source is [uml/shapes.puml](uml/shapes.puml). Render it with PlantUML using `plantuml -tpng diagrams/shapes.puml`.

You can find a rendered UML Diagram like this

![Alt text](uml/shapes.png "Shapes Demo")


## Continuous integration

GitHub Actions runs GoogleTest, sanitizer-backed memory checks, `clang-tidy` static analysis, lcov code coverage, and a Doxygen generation check on pushes and pull requests.
