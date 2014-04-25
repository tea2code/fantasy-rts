# Qt/qmake related settings.
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Compiler features.
QMAKE_CXXFLAGS += -std=c++11

# Activate warnings.
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Werror -Wdeprecated

# Deactivate some unnecessary warnings. Best to use "-Wno-error=..." and keep warnings.
QMAKE_CXXFLAGS += -Wno-error=unused-parameter

# Optimization flags.
OPTIMIZE {
    QMAKE_CXXFLAGS += -O3
}

# Includes.
INCLUDEPATH += $$PWD/dependency/Catch/single_include
INCLUDEPATH += $$PWD/dependency/boost
INCLUDEPATH += $$PWD/dependency/yaml-cpp/include
INCLUDEPATH += $$PWD/dependency/easyloggingpp/src

# Libs.
LIBS += -L$$PWD/dependency/yaml-cpp/build -lyaml-cpp

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
