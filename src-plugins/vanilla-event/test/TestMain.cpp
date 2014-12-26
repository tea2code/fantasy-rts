#include <catch.hpp>

#include <main/EventError.h>
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


TEST_CASE("Event.", "[main]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto eventManager = frts::makeEventManager();
    eventManager->init(shared);

    auto eventId = shared->makeId("test.event");
    auto event = eventManager->makeEvent(eventId, shared);

    REQUIRE(event != nullptr);
    REQUIRE(event->getType() == eventId);

    auto eventValue1 = frts::makeEventValue<frts::IntegerEventValue>(eventManager, frts::EventIds::integerEventValue(), shared);
    REQUIRE(eventValue1 != nullptr);
    eventValue1->setValue(123);
    auto eventValueId1 = shared->makeId("test.event.value.1");
    event->setValue(eventValueId1, eventValue1);

    auto eventValue2 = frts::makeEventValue<frts::StringEventValue>(eventManager, frts::EventIds::stringEventValue(), shared);
    REQUIRE(eventValue2 != nullptr);
    eventValue2->setValue("test");
    auto eventValueId2 = shared->makeId("test.event.value.2");
    event->setValue(eventValueId2, eventValue2);

    auto eventValueId3 = shared->makeId("test.event.value.3");

    REQUIRE(event->hasValue(eventValueId1));
    REQUIRE(event->hasValue(eventValueId2));
    REQUIRE_FALSE(event->hasValue(eventValueId3));

    REQUIRE(frts::getEventValue<frts::IntegerEventValue>(event, eventValueId1)->getValue() == 123);
    REQUIRE(frts::getEventValue<frts::StringEventValue>(event, eventValueId2)->getValue() == "test");
    REQUIRE_THROWS_AS(frts::getEventValue<frts::IntegerEventValue>(event, eventValueId3), frts::EventValueNotFoundError);
}

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
