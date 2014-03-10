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

# Headers and sources.
include(src/configuration/configuration.pri)
SOURCES += src/main.cpp
