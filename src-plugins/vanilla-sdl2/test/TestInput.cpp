#include <catch.hpp>

#include <input/StringToSdl2Key.h>


TEST_CASE("StringToSdl2Key.", "[input]")
{
    REQUIRE(frts::stringToSdl2Key("Number0") == SDLK_0);
    REQUIRE(frts::stringToSdl2Key("number0") == SDLK_0);
    REQUIRE(frts::stringToSdl2Key("0") == SDLK_0);
    REQUIRE(frts::stringToSdl2Key(",") == SDLK_COMMA);
    REQUIRE(frts::stringToSdl2Key("\\") == SDLK_BACKSLASH);
}
