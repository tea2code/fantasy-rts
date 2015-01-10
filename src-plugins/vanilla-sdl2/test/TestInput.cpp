#include <catch.hpp>

#include <input/KeyToSdl2Key.h>
#include <input/StringToSdl2Key.h>
#include <input/impl/SelectionDataImpl.h>

#include <shared/impl/IdImpl.h>


TEST_CASE("KeyToSdl2Key.", "[input]")
{
    REQUIRE(frts::keyToSdl2Key(frts::Key::Number0) == SDLK_0);
}

TEST_CASE("StringToSdl2Key.", "[input]")
{
    REQUIRE(frts::stringToSdl2Key("Number0") == SDLK_0);
    REQUIRE(frts::stringToSdl2Key("number0") == SDLK_0);
    REQUIRE(frts::stringToSdl2Key("0") == SDLK_0);
    REQUIRE(frts::stringToSdl2Key(",") == SDLK_COMMA);
    REQUIRE(frts::stringToSdl2Key("\\") == SDLK_BACKSLASH);
}

TEST_CASE("SelectionData.", "[input]")
{
    auto sd = frts::makeSelectionData();

    auto id = frts::makeId("test");

    sd->setIsSelecting(true);
    sd->setSelectionEntityId(id);

    REQUIRE(sd->isSelecting());
    REQUIRE(sd->getSelectionEntityId() == id);

    sd->resetSelection();

    REQUIRE_FALSE(sd->isSelecting());
    REQUIRE(sd->getSelectionEntityId() == id);
}
