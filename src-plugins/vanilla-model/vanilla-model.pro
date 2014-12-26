# Qt/qmake related settings.
TEMPLATE = lib
UNIT_TEST {
    TEMPLATE = app
    CONFIG += console
}
CONFIG -= app_bundle
CONFIG -= qt

# Compiler features.
QMAKE_CXXFLAGS += -std=c++14 #-Weffc++

# Activate warnings.
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Werror -Wdeprecated

# Deactivate some unnecessary warnings. Best to use "-Wno-error=..." and keep warnings.
QMAKE_CXXFLAGS += -Wno-error=unused-parameter -Wno-error=unused-variable

# Optimization flags.
OPTIMIZE {
    QMAKE_CXXFLAGS += -O3
}

# Includes.
INCLUDEPATH += $$PWD/../../src/
INCLUDEPATH += $$PWD/../../src/dependency/Catch/single_include
INCLUDEPATH += $$PWD/../../src/dependency/boost
INCLUDEPATH += $$PWD/../../src/dependency/easyloggingpp/src
INCLUDEPATH += $$PWD/../../src-helper/
INCLUDEPATH += $$PWD/../vanilla-event

# Headers and sources.
UNIT_TEST {
    # Necessary for tests.
    HEADERS += \
        $$PWD/../../src/log/NoLog.h \
        $$PWD/../../src/shared/impl/IdImpl.h \
        $$PWD/../../src/shared/impl/SharedManagerImpl.h \
        $$PWD/../../src/shared/impl/MainDataImpl.h
    SOURCES += \
        $$PWD/../../src/shared/impl/IdImpl.cpp \
        $$PWD/../../src/shared/impl/SharedManagerImpl.cpp \
        $$PWD/../../src/shared/impl/MainDataImpl.cpp

    include(test/test.pri)
}
include(entity/entity.pri)
include(event/event.pri)
include(frts/frts.pri)
include(main/main.pri)
include(pathfinding/pathfinding.pri)
include(region/region.pri)
include(regiongenerator/regiongenerator.pri)
include(resource/resource.pri)

# Necessary for event.
HEADERS += \
    $$PWD/../vanilla-event/main/impl/BaseEventValue.h \
    $$PWD/../vanilla-event/main/impl/BaseEventValueBuilder.h \
