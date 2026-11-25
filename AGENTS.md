# Everydo contributor guide

Everydo is a C++23 library for desktop file saving with undo and redo.
Its public interface is in `src/everydo.hh`, with implementation in
`src/everydo.cc` and exception types in `src/exceptions.h`.

## Build and test

Use CMake, Git, and C and C++ compilers with C++23 standard library support.
Run these commands from the repository root:

```sh
cmake -S . -B build
cmake --build build --parallel
(cd build && ctest --output-on-failure)
```

Use a separate build directory when switching compilers or CMake generators.
The first configure needs network access to fetch Boost 1.92.0 and its
submodules. CMake selects Boost.Log and its dependencies. Link Boost through
`Boost::log` so its include paths propagate to users of `everydo.hh`.
SQLite is bundled in `src/` and compiled into `libeverydo`.

## Making changes

- Keep changes focused and preserve existing worktree edits.
- Put regression coverage for library behavior in `src/everydo_tests.cc`, which
  CMake registers as `everydo_tests`. Use an in-memory SQLite database when a
  test does not need to exercise persistence.
- Make build changes in the root `CMakeLists.txt`. Keep generated files and
  fetched sources under the build directory out of commits.
