# Qt/qmake related settings.
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Compiler features.
QMAKE_CXXFLAGS += -std=c++14

# Activate warnings.
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Werror -Wdeprecated

# Deactivate some unnecessary warnings. Best to use "-Wno-error=..." and keep warnings.
QMAKE_CXXFLAGS += -Wno-error=unused-parameter -Wno-error=unused-variable -Wno-error=unused-but-set-variable

# Optimization flags.
OPTIMIZE {
    DEFINES += NDEBUG
    QMAKE_CXXFLAGS += -O3
}

# Includes.
INCLUDEPATH += $$PWD/dependency/Catch/single_include
INCLUDEPATH += $$PWD/dependency/boost
INCLUDEPATH += $$PWD/dependency/yaml-cpp/include
INCLUDEPATH += $$PWD/dependency/easyloggingpp/src
INCLUDEPATH += $$PWD/../src-helper

# Libs.
LIBS += -L$$PWD/dependency/yaml-cpp/build -lyaml-cpp
LINUX_LDL {
    # Necessary on Linux if compiler throws "undefined reference to dlerror"...
    # errors. See documentation "Development.md".
    LIBS += -ldl
}

# Headers and sources.
UNIT_TEST {
    include(test/test.pri)
}
include(configuration/configuration.pri)
include(log/log.pri)
include(frts/frts.pri)
include(main/main.pri)
include(module/module.pri)
include(plugin/plugin.pri)
include(shared/shared.pri)
