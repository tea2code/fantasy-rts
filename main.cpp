#ifndef UNIT_TEST

#include "configuration/yaml/YamlConfigNode.h"
#include "configuration/yaml/YamlConfigNodeItr.h"
#include "configuration/yaml/YamlConfigParser.h"

#include <iostream>
#include <memory>


int main()
{
    std::cin.ignore();
    return 0;
}

#else

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#endif
