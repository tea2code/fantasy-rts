#include <catch.hpp>

#include <configuration/ConfigError.h>
#include <configuration/yaml/YamlConfigParser.h>


TEST_CASE("Parse YAML configuration file.", "[configuration]")
{
    frts::YamlConfigParser parser;

    SECTION("The YAML file exists.")
    {
        frts::ConfigNodePtr node = parser.parseFile("configuration.yaml");
        REQUIRE(node.get() != nullptr);
    }

    SECTION("The YAML file does not exists.")
    {
        REQUIRE_THROWS_AS(parser.parseFile("notexist.yaml"), frts::FileNotFoundError);
    }
}


TEST_CASE("Parse YAML configuration node.", "[configuration]")
{

    frts::YamlConfigParser parser;
    frts::ConfigNodePtr node = parser.parseFile("configuration.yaml");
    REQUIRE(node.get() != nullptr);

    SECTION("Iterate sub nodes.")
    {
        frts::ConfigNodePtr subNode = node->getNode("nodes");
        int num = 1;
        for(const auto& subSubNode : *subNode)
        {
            REQUIRE(subSubNode->getInt("node") == num);
            num += 1;
        }
    }

    SECTION("Read boolean value.")
    {
        REQUIRE(node->getBool("boolValueTrue") == true);
        REQUIRE(node->getBool("boolValueFalse") == false);
        REQUIRE(node->getBool("notExistingKey", true) == true);
        REQUIRE(node->getBool("notExistingKey", false) == false);
        REQUIRE_THROWS_AS(node->getBool("floatValue12"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getBool("floatValue12", false), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getBool("notExistingKey"), frts::MissingValueError);
    }

    SECTION("Read float value.")
    {
        REQUIRE(node->getFloat("floatValue12") == Approx(1.2));
        REQUIRE(node->getFloat("floatValue00") == Approx(0.0));
        REQUIRE(node->getFloat("notExistingKey", 2.56) == Approx(2.56));
        REQUIRE_THROWS_AS(node->getFloat("boolValueTrue"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getFloat("notExistingKey"), frts::MissingValueError);
    }

    SECTION("Read integer value.")
    {
        REQUIRE(node->getInt("intValue0") == 0);
        REQUIRE(node->getInt("intValue35") == 35);
        REQUIRE(node->getInt("notExistingKey", 256) == 256);
        REQUIRE_THROWS_AS(node->getInt("boolValueTrue"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getInt("notExistingKey"), frts::MissingValueError);
    }

    SECTION("Read sub node.")
    {
        frts::ConfigNodePtr subNode = node->getNode("node");
        REQUIRE(subNode.get() != nullptr);
        REQUIRE(subNode->getInt("test") == 1);
    }

    SECTION("Read string value.")
    {
        REQUIRE(node->getString("stringValueAbc") == "abc");
        REQUIRE(node->getString("stringValueSentence") == "Hello World");
        REQUIRE(node->getString("stringValueSentenceQuoted") == "Hello World");
        REQUIRE(node->getString("notExistingKey", "Test") == "Test");
        REQUIRE_THROWS_AS(node->getString("boolValueTrue"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getString("notExistingKey"), frts::MissingValueError);
    }

    SECTION("Check if node has value.")
    {
        REQUIRE(node->has("boolValueTrue"));
        REQUIRE_FALSE(node->has("notExistingKey"));
    }
}
