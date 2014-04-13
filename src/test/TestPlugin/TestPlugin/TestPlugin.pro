# Qt/qmake related settings.
TEMPLATE = lib
CONFIG -= app_bundle
CONFIG -= qt

# Compiler features.
QMAKE_CXXFLAGS += -std=c++11

# Activate warnings.
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Werror

# Deactivate some unnecessary warnings. Best to use "-Wno-error=..." and keep warnings.
QMAKE_CXXFLAGS += -Wno-error=unused-parameter

# Includes.
INCLUDEPATH += $$PWD/../../..

# Headers and sources.
SOURCES += \
    Plugin.cpp \
    Module.cpp

HEADERS += \
    Plugin.h \
    Module.h