HEADERS += \ 
    $$PWD/VanillaJobPlugin.h \
    $$PWD/Job.h \
    $$PWD/JobIds.h \
    $$PWD/JobHandler.h \
    $$PWD/JobManager.h \
    $$PWD/impl/JobManagerImpl.h \
    $$PWD/JobMarker.h \
    $$PWD/impl/JobMarkerImpl.h \
    $$PWD/impl/JobMarkerBuilder.h

SOURCES += \ 
    main/main.cpp \
    $$PWD/VanillaJobPlugin.cpp \
    $$PWD/JobHandler.cpp \
    $$PWD/impl/JobManagerImpl.cpp \
    $$PWD/impl/JobMarkerImpl.cpp \
    $$PWD/impl/JobMarkerBuilder.cpp
