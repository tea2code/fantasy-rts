HEADERS += \
    input/Key.h \
    input/MouseButton.h \
    input/StringToSdl2Key.h \
    input/StringToSdl2MouseButton.h \
    input/KeyToSdl2Key.h \
    input/MouseButtonToSdl2MouseButton.h \
    input/Sdl2EventHandler.h \
    input/InputHandler.h \
    input/impl/InputHandlerImpl.h \
    $$PWD/SelectionData.h \
    $$PWD/impl/SelectionDataImpl.h \
    $$PWD/impl/SelectionHelper.h \
    $$PWD/impl/SelectCommand.h \
    $$PWD/impl/SelectCommandBuilder.h \
    $$PWD/impl/CloseContextCommand.h \
    $$PWD/impl/CloseContextCommandBuilder.h

    

SOURCES += \
    input/KeyToSdl2Key.cpp \
    input/MouseButtonToSdl2MouseButton.cpp \
    input/StringToSdl2Key.cpp \
    input/StringToSdl2MouseButton.cpp \
    input/impl/InputHandlerImpl.cpp \
    input/Sdl2EventHandler.cpp \
    $$PWD/impl/SelectionDataImpl.cpp \
    $$PWD/impl/SelectionHelper.cpp \
    $$PWD/impl/SelectCommand.cpp \
    $$PWD/impl/SelectCommandBuilder.cpp \
    $$PWD/impl/CloseContextCommand.cpp \
    $$PWD/impl/CloseContextCommandBuilder.cpp
