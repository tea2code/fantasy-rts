# Qt/qmake related settings.
TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt

# Compiler features.
QMAKE_CXXFLAGS += -std=c++14

# Activate warnings.
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Werror -Wdeprecated

# Deactivate some unnecessary warnings. Best to use "-Wno-error=..." and keep warnings.
QMAKE_CXXFLAGS += -Wno-error=unused-parameter

# Includes.
INCLUDEPATH += $$PWD/../../..
INCLUDEPATH += $$PWD/../../../../src-helper

# Headers and sources.
SOURCES += \
    Plugin.cpp \
    Tickable.cpp \
    Utility.cpp \
    DataValue.cpp

HEADERS += \
    Plugin.h \
    Tickable.h \
    Utility.h \
    DataValue.h
