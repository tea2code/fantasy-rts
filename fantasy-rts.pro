# Qt/qmake related settings.
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Compiler features.
QMAKE_CXXFLAGS += -std=c++11

# Activate warnings.
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Werror

# Deactivate some unnecessary warnings. Best to use "-Wno-error=..." and keep warnings.
QMAKE_CXXFLAGS += -Wno-error=unused-parameter

# Includes.
INCLUDEPATH += $$PWD/../libraries/boost_1_55_0
INCLUDEPATH += $$PWD/../libraries/yaml-cpp/include

# Libs.
LIBS += -L$$PWD/../libraries/yaml-cpp -lyaml-cpp

# Headers and sources.
include(src/configuration/configuration.pri)
SOURCES += src/main.cpp

HEADERS += \
    IteratorWrapper.h
