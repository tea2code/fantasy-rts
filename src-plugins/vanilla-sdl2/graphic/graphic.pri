HEADERS += \
    graphic/Renderable.h \
    graphic/impl/RenderableImpl.h \
    graphic/impl/RenderableBuilder.h \
    graphic/FpsManager.h \
    graphic/Drawer.h \
    graphic/Sdl2Renderer.h \
    $$PWD/impl/Sprite.h \
    $$PWD/impl/SpriteManager.h \
    $$PWD/impl/SpritePoint.h
    

SOURCES += \
    graphic/impl/RenderableImpl.cpp \
    graphic/impl/RenderableBuilder.cpp \
    $$PWD/impl/Sprite.cpp \
    $$PWD/impl/SpriteManager.cpp \
    $$PWD/impl/SpritePoint.cpp \
    $$PWD/FpsManager.cpp \
    $$PWD/Sdl2Renderer.cpp \
    $$PWD/Drawer.cpp
