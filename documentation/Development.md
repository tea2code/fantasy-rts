# Development

This document describes the steps necessary to work on the source code and compile everything.

## Compile

The application is developed using [Qt Creator](https://qt-project.org/) and [MinGW-w64](http://mingw-w64.sourceforge.net/) on Windows. It should be possible to compile it with other compilers (especially [GCC](http://gcc.gnu.org/)) on any os but changing the IDE may require recreating the project/make file. Currently .pro and .pri files are used with qmake. 

The compiler is executed with support for C++11 (`-std=c++11`) and all warnings (`-pedantic -Wall -Wextra  -Wdeprecated`). Warnings are considered errors (`-Werror`). Only exception are some minor problems which are kept as warnings (`-Wno-error=unused-parameter`).

### Dependencies

If not stated otherwise always use the most up to date version. It is considered a bug if the application cannot compile and run with it. Of course this doesn't include unstable/nightly builds of any library.

The .pro file assumes that all dependencies are put into a directory *dependency* in the project root. For the naming of the individual directories of every dependency see the .pro file.

- [Boost](http://www.boost.org/)
- [yaml-cpp](https://code.google.com/p/yaml-cpp/): Must be compiled statically.
- [Catch](https://github.com/philsquared/Catch)
- [Easylogging++](http://easylogging.org/)

### Deployment

The deployment step should include copying the *plugins* and *log* directories to the build directory.

### Example configuration

Following settings are for Qt Creator. Building/deployment steps marked with `code highlighting` are custom steps where the first line is the command, second are arguments and third is the working directory.

If you're using gcc it is recommended to build with make argument `-j` (Windows) or `-j<number-of-jobs>` (Linux) to benefit from multi core building.

#### Kernel

Release and debug builds use standard settings. For testing create variants of both and add `DEFINES+=UNIT_TEST CONFIG+=UNIT_TEST` to the additional arguments of qmake. Executing these builds will execute all unit tests.

For optimization add `DEFINES+=OPTIMIZE` to the additional arguments of qmake.

On Linux it may be necessary to add `CONFIG+=LINUX_LDL` to the additional arguments of qmake. This is only necessary if you see compiler errors like `undefined reference to dlerror`, `undefined reference to dlsym`... (mostly on Ubuntu based distributions).

Running includes three custom steps to copy assets into the working directory:

##### Windows

    xcopy
    %{sourceDir}\..\plugins %{buildDir}\plugins /seyi
    %{buildDir}

    xcopy
    %{sourceDir}\..\log %{buildDir}\log /seyi
    %{buildDir}

    xcopy
    %{sourceDir}\test\TestPlugin\TestPlugin.dll %{buildDir}\ /eiy
    %{buildDir}

#### Linux

    cp
    -R %{sourceDir}/../plugins %{buildDir}/plugins
    %{buildDir}

    cp
    -R %{sourceDir}/../log %{buildDir}/log
    %{buildDir}

    cp
    %{sourceDir}/test/TestPlugin/libTestPlugin.so %{buildDir}
    %{buildDir}

#### TestPlugin

The project of this plugin exists in the test directory of the kernel. It's sole purpose is for the unit tests of kernel.

Default compile settings with additional copy step after making:

##### Windows

    xcopy
    %{buildDir}\release\TestPlugin.dll %{buildDir}\..\..\ /eiy
    %{buildDir}

#### Linux

    cp
    %{buildDir}/libTestPlugin.so %{buildDir}/../../
    %{buildDir}

#### Real plugins

The following settings apply to all plugins created in *src-plugins* with the build directory also under *src-plugins*. For example:

    src-plugins/
        vanilla-demo/
            ...
        vanilla-demo-build/
            ....

Default compile settings with additional copy step after making:

##### Windows

    xcopy
    %{buildDir}\release\plugin-name.dll %{buildDir}\..\..\..\plugins\plugin-name\ /eiy
    %{buildDir}

#### Linux

    cp
    %{buildDir}/libplugin-name.so %{buildDir}/../../../plugins/plugin-name\
    %{buildDir}

## Code Style

There is no particular code style enfored. Just some simple recommendations which might help.

### Namespace

The application core uses the namespace *frts* while plugins should use their own. Any namespace should be short but descriptive.

### Order of Includes

Based on recommendations from [stackoverflow.com](http://stackoverflow.com/q/2762568/1931663).

    #include "header-of-cpp.h"

    #include "internal-header-same-directory.h"
    #include <other-internal-header.h>

    #include <external-dependencies.h>

    #include <stl-header>

### Blank Lines

Separate functions, classes... by one line. The only exception are `#include` which should have two blank lines between the last `#include` and the following code (for example `class`).

## Unit Tests

Unit tests are implemented using Catch which allows fast and easy creation of a huge number of test cases. To prevent problems with normal builds the directory *test* is only included into the build if qmake was executed with the parameters `DEFINES+=UNIT_TEST CONFIG+=UNIT_TEST`.

This principle can be also applied to plugins. Additionally it is necessary to build the plugins in test mode as applications instead of libraries.