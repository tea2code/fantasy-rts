HEADERS += \
    graphic/Renderable.h \
    graphic/impl/RenderableImpl.h \
    graphic/impl/RenderableBuilder.h \
    graphic/FpsManager.h \
    graphic/Drawer.h \
    graphic/Sdl2Renderer.h \
    graphic/impl/FpsManagerImpl.h \
    $$PWD/impl/Sprite.h \
    $$PWD/impl/SpriteManager.h \
    $$PWD/impl/SpritePoint.h
    

SOURCES += \
    graphic/impl/RenderableImpl.cpp \
    graphic/impl/RenderableBuilder.cpp \
    graphic/impl/FpsManagerImpl.cpp \
    $$PWD/impl/Sprite.cpp \
    $$PWD/impl/SpriteManager.cpp \
    $$PWD/impl/SpritePoint.cpp
