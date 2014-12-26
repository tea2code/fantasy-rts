#include <catch.hpp>

#include <main/EventIds.h>
#include <main/impl/EventManagerImpl.h>
#include <main/StringEventValue.h>
#include <main/IntegerEventValue.h>
#include <main/FloatEventValue.h>
#include <main/BooleanEventValue.h>
#include <main/IdEventValue.h>

#include <frts/shared>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("EventValues.", "[main]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto eventManager = frts::makeEventManager();
    eventManager->init(shared);

    SECTION("StringEventValue")
    {
        auto eventValue = frts::makeEventValue<frts::StringEventValue>(eventManager, frts::EventIds::stringEventValue(), shared);
        REQUIRE(eventValue != nullptr);
        REQUIRE(eventValue->getType()->toString() == frts::EventIds::stringEventValue());

        eventValue->setValue("test");
        REQUIRE(eventValue->getValue() == "test");
    }

    SECTION("IntegerEventValue")
    {
        auto eventValue = frts::makeEventValue<frts::IntegerEventValue>(eventManager, frts::EventIds::integerEventValue(), shared);
        REQUIRE(eventValue != nullptr);
        REQUIRE(eventValue->getType()->toString() == frts::EventIds::integerEventValue());

        eventValue->setValue(123);
        REQUIRE(eventValue->getValue() == 123);
    }

    SECTION("FloatEventValue")
    {
        auto eventValue = frts::makeEventValue<frts::FloatEventValue>(eventManager, frts::EventIds::floatEventValue(), shared);
        REQUIRE(eventValue != nullptr);
        REQUIRE(eventValue->getType()->toString() == frts::EventIds::floatEventValue());

        eventValue->setValue(0.53);
        REQUIRE(eventValue->getValue() == Approx(0.53));
    }

    SECTION("BooleanEventValue")
    {
        auto eventValue = frts::makeEventValue<frts::BooleanEventValue>(eventManager, frts::EventIds::booleanEventValue(), shared);
        REQUIRE(eventValue != nullptr);
        REQUIRE(eventValue->getType()->toString() == frts::EventIds::booleanEventValue());

        eventValue->setValue(true);
        REQUIRE(eventValue->getValue() == true);

        eventValue->setValue(false);
        REQUIRE(eventValue->getValue() == false);
    }

    SECTION("IdEventValue")
    {
        auto eventValue = frts::makeEventValue<frts::IdEventValue>(eventManager, frts::EventIds::idEventValue(), shared);
        REQUIRE(eventValue != nullptr);
        REQUIRE(eventValue->getType()->toString() == frts::EventIds::idEventValue());

        eventValue->setValue(shared->makeId("test"));
        REQUIRE(eventValue->getValue()->toString() == "test");
    }
}
