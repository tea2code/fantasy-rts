# Qt/qmake related settings.
TEMPLATE = lib
UNIT_TEST {
    TEMPLATE = app
    CONFIG += console
}
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
INCLUDEPATH += $$PWD/../../src
INCLUDEPATH += $$PWD/../../src/dependency/Catch/single_include
INCLUDEPATH += $$PWD/../../src/dependency/boost
#INCLUDEPATH += $$PWD/../vanilla-model
INCLUDEPATH += $$PWD/dependency/SDL2/include

# Libs.
LIBS += -lmingw32 -mwindows -mconsole
LIBS += -L$$PWD/dependency/SDL2/build -L$$PWD/dependency/SDL2/build/.libs
LIBS += -lSDL2main -lSDL2

# Headers and sources.
#UNIT_TEST {
#    include(test/test.pri)
#}
SOURCES += main.cpp \
    VanillaSdl2Plugin.cpp \
    VanillaSdl2Tickable.cpp

HEADERS += \
    VanillaSdl2Plugin.h \
    VanillaSdl2Tickable.h
