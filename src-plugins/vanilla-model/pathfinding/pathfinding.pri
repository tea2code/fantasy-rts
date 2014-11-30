HEADERS += \
    $$PWD/PathFinder.h \
    $$PWD/DistanceAlgorithm.h \
    $$PWD/impl/EuclideanDistance.h \
    $$PWD/impl/AStar.h \
    $$PWD/impl/ManhattanDistance.h \
    $$PWD/Path.h \
    $$PWD/impl/PathImpl.h
    
SOURCES += \
    $$PWD/impl/EuclideanDistance.cpp \
    $$PWD/impl/AStar.cpp \
    $$PWD/impl/ManhattanDistance.cpp \
    $$PWD/impl/PathImpl.cpp
