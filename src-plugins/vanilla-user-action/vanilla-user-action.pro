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

# Activate warnings. See http://stackoverflow.com/a/9862800/1931663
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Werror -Wdeprecated
QMAKE_CXXFLAGS += -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization
QMAKE_CXXFLAGS += -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs
QMAKE_CXXFLAGS += -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion
QMAKE_CXXFLAGS += -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default
QMAKE_CXXFLAGS += -Wconversion -Winvalid-pch -Wzero-as-null-pointer-constant -Wuseless-cast

# This throws a lot of errors in constructor initialization. I would like to enable it but this
# would need a lot of refactoring and thinking about new parameter names.
# -Wshadow

# Deactivate some unnecessary warnings. Best to use "-Wno-error=..." and keep warnings.
QMAKE_CXXFLAGS += -Wno-error=unused-parameter -Wno-error=unused-variable -Wno-error=unused-but-set-variable

# Optimization flags.
OPTIMIZE {
    DEFINES += NDEBUG
    QMAKE_CXXFLAGS += -O3
}

# Includes. Faking -isystem using QMAKE_CXXFLAGS to prevent warnings in libraries.
# See http://stackoverflow.com/a/6437710/1931663
QMAKE_CXXFLAGS += -isystem $$PWD/../../src/dependency/boost
QMAKE_CXXFLAGS += -isystem $$PWD/../../src/dependency/Catch/single_include
INCLUDEPATH += $$PWD/../../src
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
include(carve/carve.pri)
include(frts/frts.pri)
include(gathering/gathering.pri)
include(harvesting/harvesting.pri)
include(main/main.pri)
include(production/production.pri)
include(special/special.pri)
