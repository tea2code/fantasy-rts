HEADERS += \
    input/Key.h \
    input/StringToSdl2Key.h \
    input/KeyToSdl2Key.h \
    input/Sdl2EventHandler.h \
    input/InputHandler.h \
    input/impl/InputHandlerImpl.h \
    $$PWD/SelectionData.h \
    $$PWD/impl/SelectionDataImpl.h \
    $$PWD/impl/SelectionHelper.h \
    $$PWD/impl/SelectCommand.h \
    $$PWD/impl/SelectCommandBuilder.h

    

SOURCES += \
    input/KeyToSdl2Key.cpp \
    input/StringToSdl2Key.cpp \
    input/impl/InputHandlerImpl.cpp \
    input/Sdl2EventHandler.cpp \
    $$PWD/impl/SelectionDataImpl.cpp \
    $$PWD/impl/SelectionHelper.cpp \
    $$PWD/impl/SelectCommand.cpp \
    $$PWD/impl/SelectCommandBuilder.cpp
