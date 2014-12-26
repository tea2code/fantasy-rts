HEADERS += \
    main/VanillaEventPlugin.h \
    $$PWD/EventManager.h \
    $$PWD/impl/EventManagerImpl.h \
    $$PWD/EventIds.h \
    $$PWD/EventValue.h \
    $$PWD/EventValueBuilder.h \
    $$PWD/EventError.h \
    $$PWD/StringEventValue.h \
    $$PWD/impl/StringEventValueImpl.h \
    $$PWD/impl/StringEventValueBuilder.h \
    $$PWD/impl/BaseEventValue.h \
    $$PWD/impl/BaseEventValueBuilder.h \
    $$PWD/IntegerEventValue.h \
    $$PWD/FloatEventValue.h \
    $$PWD/BooleanEventValue.h \
    $$PWD/IdEventValue.h \
    $$PWD/impl/BooleanEventValueImpl.h \
    $$PWD/impl/FloatEventValueImpl.h \
    $$PWD/impl/IdEventValueImpl.h \
    $$PWD/impl/IntegerEventValueImpl.h \
    $$PWD/impl/BooleanEventValueBuilder.h \
    $$PWD/impl/FloatEventValueBuilder.h \
    $$PWD/impl/IdEventValueBuilder.h \
    $$PWD/impl/IntegerEventValueBuilder.h \
    $$PWD/Event.h \
    $$PWD/impl/EventImpl.h \
    $$PWD/EventObserver.h

SOURCES += \ 
    main/main.cpp \
    main/VanillaEventPlugin.cpp \
    $$PWD/impl/EventManagerImpl.cpp \
    $$PWD/impl/StringEventValueImpl.cpp \
    $$PWD/impl/StringEventValueBuilder.cpp \
    $$PWD/impl/BooleanEventValueImpl.cpp \
    $$PWD/impl/FloatEventValueImpl.cpp \
    $$PWD/impl/IdEventValueImpl.cpp \
    $$PWD/impl/IntegerEventValueImpl.cpp \
    $$PWD/impl/BooleanEventValueBuilder.cpp \
    $$PWD/impl/FloatEventValueBuilder.cpp \
    $$PWD/impl/IdEventValueBuilder.cpp \
    $$PWD/impl/IntegerEventValueBuilder.cpp \
    $$PWD/impl/EventImpl.cpp
