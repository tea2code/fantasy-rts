# Qt/qmake related settings.
TEMPLATE = lib
UNIT_TEST {
    TEMPLATE = app
    CONFIG += console
}
CONFIG -= app_bundle
CONFIG -= qt

# Compiler features.
QMAKE_CXXFLAGS += -std=c++14

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
INCLUDEPATH += $$PWD/../../src-helper
INCLUDEPATH += $$PWD/../../src/dependency/Catch/single_include
INCLUDEPATH += $$PWD/../../src/dependency/boost
INCLUDEPATH += $$PWD/../vanilla-model
INCLUDEPATH += $$PWD/../vanilla-command
INCLUDEPATH += $$PWD/../vanilla-sdl2

# Headers and sources.
# Important this plugin needs a block implementation and takes the one provided
# by VanillaModel.
SOURCES += \
    main.cpp \
    VanillaDemoTickable.cpp \
    VanillaDemoPlugin.cpp \
    $$PWD/../vanilla-model/region/impl/BlockImpl.cpp

HEADERS += \
    VanillaDemoTickable.h \
    VanillaDemoPlugin.h \
    $$PWD/../vanilla-model/region/impl/BlockImpl.h
