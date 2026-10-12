# Shapes Demo

A small C++20 library that models circles and triangles through a shared `Shape` interface. Constructors reject non-finite or non-positive dimensions, and triangles also enforce the triangle inequality.

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

## API documentation

Install Doxygen, then run `doxygen Doxyfile`. The HTML API reference is generated at `docs/api/html/index.html`.

## UML

The class diagram source is [diagrams/shapes.puml](diagrams/shapes.puml). Render it with PlantUML using `plantuml -tpng diagrams/shapes.puml`.

## Continuous integration

GitHub Actions runs GoogleTest, sanitizer-backed memory checks, `clang-tidy` static analysis, and a Doxygen generation check on pushes and pull requests.