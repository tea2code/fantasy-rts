HEADERS += \
    main/VanillaCommandPlugin.h \
    main/Command.h \
    main/CommandFactory.h \
    main/CommandError.h \
    main/CommandBuilder.h \
    main/impl/CommandFactoryImpl.h \
    main/CommandIds.h \
    $$PWD/CommandConfig.h \
    $$PWD/impl/CommandConfigImpl.h


SOURCES += \ 
    main/main.cpp \
    main/VanillaCommandPlugin.cpp \
    main/impl/CommandFactoryImpl.cpp \
    $$PWD/impl/CommandConfigImpl.cpp
