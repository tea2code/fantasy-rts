#ifndef UNIT_TEST

#include "configuration/yaml/YamlConfigNode.h"
#include "configuration/yaml/YamlConfigNodeItr.h"
#include "configuration/yaml/YamlConfigParser.h"

#include <iostream>
#include <memory>


int main()
{
    frts::ConfigNodePtr node =  std::unique_ptr<frts::YamlConfigNode>(
                new frts::YamlConfigNode());

    std::cin.ignore();
    return 0;
}

#else

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#endif
