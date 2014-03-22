# Development

This document describes the steps necessary to work on the source code and compile everything.

## Compile

The application is developed using [Qt Creator](https://qt-project.org/) and [MinGW-w64](http://mingw-w64.sourceforge.net/) on Windows. It should be possible to compile it with other compilers (especially [GCC](http://gcc.gnu.org/)) on any os but changing the IDE may require recreating the project/make file. Currently .pro and .pri files are used with qmake. 

The compiler is executed with support for C++11 (`-std=c++11`) and all warnings (`-pedantic -Wall -Wextra`). Warnings are considered errors (`-Werror`). Only exception are some minor problems which are kept as warnings (`-Wno-error=unused-parameter`).

### Dependencies

If not stated otherwise always use the most up to date version. It is considered a bug if the application cannot compile and run with it. Of course this doesn't include unstable/nightly builds of any library.

The .pro file assumes that all dependencies are put into a directory *dependency* in the project root. For the naming of the individual directories of every dependency see the .pro file.

- [Boost](http://www.boost.org/)
- [yaml-cpp](https://code.google.com/p/yaml-cpp/): Must be compiled statically.
- [Catch](https://github.com/philsquared/Catch)

### Deployment

The deployment step should include copying the *plugins* directory to the build directory.

## Code Style

There is no particular code style enfored. Just some simple recommendations which might help.

### Namespace

The application core uses the namespace *frts* while plugins should use their own. Any namespace should be short but descriptive.

### Order of Includes

Based on recommendations from [stackoverflow.com](http://stackoverflow.com/q/2762568/1931663).

    #include "header-of-cpp.h"

    #include "internal-header-same-directory.h"
    #include <other-internal-header.h"

    #include <external-dependencies.h>

    #include <stl-header>

### Blank Lines

Separate functions, classes... by one line. The only exception are `#include` which should have two blank lines between the last `#include` and the following code (for example `class`).

## Unit Tests

Unit tests are implemented using Catch which allows fast and easy creation of a huge number of test cases. To prevent problems with normal builds the directory *test* is only included into the build if qmake was executed with the parameters `DEFINES+=UNIT_TEST CONFIG+=UNIT_TEST`.