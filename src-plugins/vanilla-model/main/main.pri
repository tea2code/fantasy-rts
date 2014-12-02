HEADERS += \
    main/VanillaModelPlugin.h \
    main/ModelFactory.h \
    main/impl/ModelFactoryImpl.h \
    main/ModelError.h \
    main/RegionManager.h \
    main/impl/RegionManagerImpl.h \
    main/ModelReseter.h \
    $$PWD/ModelIds.h \
    $$PWD/ModelData.h \
    $$PWD/impl/ModelDataImpl.h

SOURCES += \ 
    main/main.cpp \
    main/VanillaModelPlugin.cpp \
    main/impl/ModelFactoryImpl.cpp \
    main/impl/RegionManagerImpl.cpp \
    main/ModelReseter.cpp \
    $$PWD/impl/ModelDataImpl.cpp