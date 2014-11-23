HEADERS += \
    graphic/Renderable.h \
    graphic/impl/RenderableImpl.h \
    graphic/impl/RenderableBuilder.h \
    graphic/FpsManager.h \
    graphic/Drawer.h \
    graphic/Sdl2Renderer.h \
    $$PWD/impl/Sprite.h \
    $$PWD/impl/SpriteManager.h \
    $$PWD/impl/SpritePoint.h \
    $$PWD/GraphicData.h \
    $$PWD/impl/GraphicDataImpl.h \
    $$PWD/impl/MoveScreenCommand.h \
    $$PWD/impl/MoveScreenCommandBuilder.h \
    $$PWD/impl/GraphicUtility.h \
    $$PWD/impl/MoveCursorCommand.h \
    $$PWD/impl/MoveCursorCommandBuilder.h
    

SOURCES += \
    graphic/impl/RenderableImpl.cpp \
    graphic/impl/RenderableBuilder.cpp \
    $$PWD/impl/Sprite.cpp \
    $$PWD/impl/SpriteManager.cpp \
    $$PWD/impl/SpritePoint.cpp \
    $$PWD/FpsManager.cpp \
    $$PWD/Sdl2Renderer.cpp \
    $$PWD/Drawer.cpp \
    $$PWD/impl/GraphicDataImpl.cpp \
    $$PWD/impl/MoveScreenCommand.cpp \
    $$PWD/impl/MoveScreenCommandBuilder.cpp \
    $$PWD/impl/GraphicUtility.cpp \
    $$PWD/impl/MoveCursorCommand.cpp \
    $$PWD/impl/MoveCursorCommandBuilder.cpp
