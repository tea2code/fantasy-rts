#include <catch.hpp>

#include <entity/impl/EntityImpl.h>
#include <event/ModelEventIds.h>
#include <event/impl/EntityEventValueBuilder.h>
#include <event/impl/PointEventValueBuilder.h>
#include <region/impl/PointImpl.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("EventValues.", "[event]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    SECTION("EntityEventValue")
    {
        auto type = shared->makeId(frts::ModelEventIds::entityEventValue());
        auto eventValueBuilder = frts::makeEntityEventValueBuilder(type);
        auto eventValue = std::static_pointer_cast<frts::EntityEventValue>(eventValueBuilder->build(shared));
        REQUIRE(eventValue != nullptr);
        REQUIRE(eventValue->getType()->toString() == frts::ModelEventIds::entityEventValue());

        auto entity = frts::makeEntity();
        eventValue->setValue(entity);
        REQUIRE(eventValue->getValue() == entity);
    }

    SECTION("PointEventValue")
    {
        auto type = shared->makeId(frts::ModelEventIds::pointEventValue());
        auto eventValueBuilder = frts::makePointEventValueBuilder(type);
        auto eventValue = std::static_pointer_cast<frts::PointEventValue>(eventValueBuilder->build(shared));
        REQUIRE(eventValue != nullptr);
        REQUIRE(eventValue->getType()->toString() == frts::ModelEventIds::pointEventValue());

        auto point = frts::makePoint(1, 2, 3);
        eventValue->setValue(point);
        REQUIRE(eventValue->getValue() == point);
    }
}
