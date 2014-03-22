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
        int count = 0;
        for(const auto& subSubNode : *subNode)
        {
            REQUIRE(subSubNode->getInteger("node") == num);
            num += 1;
            count += 1;
        }
        REQUIRE(count == 4);
    }

    SECTION("Read boolean value.")
    {
        REQUIRE(node->getBool("boolValueTrue") == true);
        REQUIRE(node->getBool("boolValueFalse") == false);
        REQUIRE(node->getBool("boolValueTrue", false) == true);
        REQUIRE(node->getBool("boolValueFalse", true) == false);
        REQUIRE(node->getBool("notExistingKey", true) == true);
        REQUIRE(node->getBool("notExistingKey", false) == false);
        REQUIRE(node->getBool("floatValue12", false) == false);
        REQUIRE(node->getBool("intValue0", false) == false);
        REQUIRE(node->getBool("stringValueAbc", false) == false);
        REQUIRE_THROWS_AS(node->getBool("floatValue12"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getBool("intValue0"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getBool("stringValueAbc"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getBool("notExistingKey"), frts::MissingValueError);
    }

    SECTION("Read float value.")
    {
        REQUIRE(node->getFloat("intValue0") == Approx(0.0));
        REQUIRE(node->getFloat("intValue35") == Approx(35));
        REQUIRE(node->getFloat("floatValue12") == Approx(1.2));
        REQUIRE(node->getFloat("floatValue00") == Approx(0.0));
        REQUIRE(node->getFloat("floatValue00", 2.56) == Approx(0.0));
        REQUIRE(node->getFloat("notExistingKey", 2.56) == Approx(2.56));
        REQUIRE(node->getFloat("boolValueTrue", 2.56) == Approx(2.56));
        REQUIRE(node->getFloat("stringValueAbc", 2.56) == Approx(2.56));
        REQUIRE_THROWS_AS(node->getFloat("boolValueTrue"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getFloat("stringValueAbc"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getFloat("notExistingKey"), frts::MissingValueError);
    }

    SECTION("Read integer value.")
    {
        REQUIRE(node->getInteger("intValue0") == 0);
        REQUIRE(node->getInteger("intValue35") == 35);
        REQUIRE(node->getInteger("intValue35", 256) == 35);
        REQUIRE(node->getInteger("notExistingKey", 256) == 256);
        REQUIRE(node->getInteger("boolValueTrue", 256) == 256);
        REQUIRE(node->getInteger("floatValue00", 256) == 256);
        REQUIRE(node->getInteger("floatValue12", 256) == 256);
        REQUIRE_THROWS_AS(node->getInteger("boolValueTrue"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getInteger("floatValue00"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getInteger("floatValue12"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getInteger("stringValueAbc"), frts::ConversionError);
        REQUIRE_THROWS_AS(node->getInteger("notExistingKey"), frts::MissingValueError);
    }

    SECTION("Read sub node.")
    {
        frts::ConfigNodePtr subNode = node->getNode("node");
        REQUIRE(subNode.get() != nullptr);
        REQUIRE(subNode->getInteger("test") == 1);
    }

    SECTION("Read string value.")
    {
        REQUIRE(node->getString("boolValueTrue") == "true");
        REQUIRE(node->getString("intValue35") == "35");
        REQUIRE(node->getString("floatValue00") == "0.0");
        REQUIRE(node->getString("stringValueAbc") == "abc");
        REQUIRE(node->getString("stringValueSentence") == "Hello World");
        REQUIRE(node->getString("stringValueSentenceQuoted") == "Hello World");
        REQUIRE(node->getString("boolValueTrue", "Test") == "true");
        REQUIRE(node->getString("intValue35", "Test") == "35");
        REQUIRE(node->getString("floatValue00", "Test") == "0.0");
        REQUIRE(node->getString("stringValueAbc", "Test") == "abc");
        REQUIRE(node->getString("notExistingKey", "Test") == "Test");
        REQUIRE_THROWS_AS(node->getString("notExistingKey"), frts::MissingValueError);
    }

    SECTION("Check if node has value.")
    {
        REQUIRE(node->has("boolValueTrue"));
        REQUIRE_FALSE(node->has("notExistingKey"));
    }

    SECTION("Check if node is of a certain type.")
    {
        REQUIRE(node->isBool("boolValueTrue"));
        REQUIRE_FALSE(node->isBool("floatValue00"));
        REQUIRE_FALSE(node->isBool("intValue0"));
        REQUIRE_FALSE(node->isBool("stringValueAbc"));
        REQUIRE_THROWS_AS(node->isBool("notExistingKey"), frts::MissingValueError);

        REQUIRE(node->isFloat("floatValue00"));
        REQUIRE(node->isFloat("intValue0"));
        REQUIRE_FALSE(node->isFloat("boolValueTrue"));
        REQUIRE_FALSE(node->isFloat("stringValueAbc"));
        REQUIRE_THROWS_AS(node->isFloat("notExistingKey"), frts::MissingValueError);

        REQUIRE(node->isInteger("intValue0"));
        REQUIRE_FALSE(node->isInteger("floatValue00"));
        REQUIRE_FALSE(node->isInteger("boolValueTrue"));
        REQUIRE_FALSE(node->isInteger("stringValueAbc"));
        REQUIRE_THROWS_AS(node->isInteger("notExistingKey"), frts::MissingValueError);

        REQUIRE(node->isString("boolValueTrue"));
        REQUIRE(node->isString("floatValue00"));
        REQUIRE(node->isString("intValue0"));
        REQUIRE(node->isString("stringValueAbc"));
        REQUIRE_THROWS_AS(node->isString("notExistingKey"), frts::MissingValueError);
    }
}
