HEADERS += \
    shared/SharedManager.h \
    shared/DataValue.h \
    shared/Frame.h \
    shared/impl/FrameImpl.h \
    shared/Id.h \
    shared/impl/IdImpl.h \
    shared/impl/SharedManagerImpl.h \
    shared/SharedError.h \
    shared/SharedPtr.h \
    $$PWD/impl/MainDataImpl.h \
    $$PWD/MainData.h \
    $$PWD/MainIds.h


SOURCES += \ 
    shared/impl/FrameImpl.cpp \
    shared/impl/IdImpl.cpp \
    shared/impl/SharedManagerImpl.cpp \
    $$PWD/impl/MainDataImpl.cpp
