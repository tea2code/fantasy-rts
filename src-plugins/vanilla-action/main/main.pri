HEADERS += \ 
    $$PWD/VanillaActionPlugin.h \
    $$PWD/Action.h \
    $$PWD/ActionManager.h \
    $$PWD/ActionIds.h \
    $$PWD/impl/ActionManagerImpl.h \
    $$PWD/impl/StopActionCommand.h \
    $$PWD/impl/StopActionCommandBuilder.h \
    $$PWD/impl/StopActionOrQuitCommand.h \
    $$PWD/impl/StopActionOrQuitCommandBuilder.h \
    $$PWD/ActionHandler.h

SOURCES += \ 
    main/main.cpp \
    $$PWD/VanillaActionPlugin.cpp \
    $$PWD/impl/ActionManagerImpl.cpp \
    $$PWD/impl/StopActionCommand.cpp \
    $$PWD/impl/StopActionCommandBuilder.cpp \
    $$PWD/impl/StopActionOrQuitCommand.cpp \
    $$PWD/impl/StopActionOrQuitCommandBuilder.cpp \
    $$PWD/ActionHandler.cpp
