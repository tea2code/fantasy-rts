#include "configuration/yaml/YamlConfigNode.h"
#include "configuration/yaml/YamlConfigNodeItr.h"
#include "configuration/yaml/YamlConfigParser.h"

#include <iostream>
#include <memory>

int main()
{
    frts::ConfigNodePtr node =  std::make_shared<frts::YamlConfigNode>();
    std::cin.ignore();
    return 0;
}

