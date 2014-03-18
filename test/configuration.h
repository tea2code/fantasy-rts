#include <catch.hpp>

#include "../src/configuration/yaml/YamlConfigParser.h"

SCENARIO("Parse YAML configuration file", "[configuration]")
{
    GIVEN("A YAML configuration parser")
    {
        frts::YamlConfigParser parser;

        WHEN("the YAML file exists")
        {
            frts::ConfigNodePtr node = parser.parseFile("");

            THEN("the pointer shouldn't be null")
            {
                REQUIRE(node != nullptr);
            }
        }
    }
}
