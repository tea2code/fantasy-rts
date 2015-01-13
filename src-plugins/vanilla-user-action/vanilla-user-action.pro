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
QMAKE_CXXFLAGS += -Wno-error=unused-parameter -Wno-error=unused-variable -Wno-error=unused-but-set-variable

# Optimization flags.
OPTIMIZE {
    DEFINES += NDEBUG
    QMAKE_CXXFLAGS += -O3
}

# Includes.
INCLUDEPATH += $$PWD/../../src
INCLUDEPATH += $$PWD/../../src/dependency/Catch/single_include
INCLUDEPATH += $$PWD/../../src/dependency/boost
INCLUDEPATH += $$PWD/../../src-helper/
INCLUDEPATH += $$PWD/../vanilla-action
INCLUDEPATH += $$PWD/../vanilla-command
INCLUDEPATH += $$PWD/../vanilla-event
INCLUDEPATH += $$PWD/../vanilla-job
INCLUDEPATH += $$PWD/../vanilla-model
INCLUDEPATH += $$PWD/../vanilla-sdl2

# Headers and sources.
UNIT_TEST {
    # Necessary for tests.
    HEADERS += \
        $$PWD/../../src/log/NoLog.h \
        $$PWD/../../src/shared/impl/IdImpl.h \
        $$PWD/../../src/shared/impl/SharedManagerImpl.h
    SOURCES += \
        $$PWD/../../src/shared/impl/IdImpl.cpp \
        $$PWD/../../src/shared/impl/SharedManagerImpl.cpp

    include(test/test.pri)
}
include(building/building.pri)
include(frts/frts.pri)
include(gathering/gathering.pri)
include(harvesting/harvesting.pri)
include(main/main.pri)
include(production/production.pri)
include(special/special.pri)
