HEADERS += src/configuration/ConfigParser.h \
    src/configuration/ConfigNode.h \
    src/configuration/ConfigNodeItr.h \
    src/configuration/ConfigError.h \
    src/configuration/yaml/YamlConfigParser.h \
    src/configuration/yaml/YamlConfigNode.h \
    src/configuration/yaml/YamlConfigNodeItr.h

SOURCES += \
    src/configuration/yaml/YamlConfigParser.cpp \
    src/configuration/yaml/YamlConfigNode.cpp \
    src/configuration/yaml/YamlConfigNodeItr.cpp
