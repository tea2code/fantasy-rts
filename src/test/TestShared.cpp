#include <catch.hpp>

#include <log/Log.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <shared/DataValue.h>
#include <shared/FrameImpl.h>
#include <shared/IdImpl.h>
#include <shared/SharedError.h>
#include <shared/SharedManagerImpl.h>

#include <algorithm>
#include <string>
#include <vector>


TEST_CASE("Create and use frame data.", "[shared]")
{
    double deltaTime = 0.002145;
    unsigned long long number = 4098353456392489llu;
    double runTime = 254121.54123;
    frts::FramePtr frame = frts::FramePtr(new frts::FrameImpl(deltaTime, number, runTime));

    REQUIRE(frame->getDeltaTime() == Approx(deltaTime));
    REQUIRE(frame->getNumber() == number);
    REQUIRE(frame->getRunTime() == Approx(runTime));
}


TEST_CASE("Create and use id.", "[shared]")
{
    std::string str1 = "test";
    frts::IdPtr id1 = frts::IdPtr(new frts::IdImpl(str1));
    frts::IdPtr id2 = frts::IdPtr(new frts::IdImpl(str1));

    std::string str2 = "testtest";
    frts::IdPtr id3 = frts::IdPtr(new frts::IdImpl(str2));

    REQUIRE(id1->toString() == str1);
    REQUIRE(id2->toString() == str1);
    REQUIRE(id3->toString() == str2);
    REQUIRE(*id1 == *id2);
    REQUIRE(*id1 != *id3);
    REQUIRE(*id2 != *id3);
}


namespace frts
{
    class TestLog : public Log
    {
    public:
        TestLog() {}
        ~TestLog() {}
        void debug(const std::string&, const std::string&) noexcept {}
        void error(const std::string&, const std::string&) noexcept {}
        void info(const std::string&, const std::string&) noexcept {}
        void warning(const std::string&, const std::string&) noexcept {}
    };

    class TestDataValue : public DataValue
    {
    public:
        ~TestDataValue() {}
        std::string getName() const noexcept { return "TestDataValue"; }
    };

    class TestTickable : public Tickable
    {
    public:
        TestTickable() {}
        ~TestTickable() {}
        void createData(SharedManagerPtr) {}
        std::string getName() const { return "TestTickable"; }
        std::vector<std::string> getSupportedConfig() { return std::vector<std::string>(); }
        void init(SharedManagerPtr) {}
        void parseConfig(ConfigNodePtr, SharedManagerPtr) {}
        void tick(SharedManagerPtr) {}
        void validateData(SharedManagerPtr) {}
        void validateModules(SharedManagerPtr) {}
    };

    class TestUtility : public Utility
    {
    public:
        TestUtility() {}
        ~TestUtility() {}
        void createData(SharedManagerPtr) {}
        std::string getName() const { return "TestUtility"; }
        std::vector<std::string> getSupportedConfig() { return std::vector<std::string>(); }
        void init(SharedManagerPtr) {}
        void parseConfig(ConfigNodePtr, SharedManagerPtr) {}
        void validateData(SharedManagerPtr) {}
        void validateModules(SharedManagerPtr) {}
    };
}

TEST_CASE("Create and use shared manager.", "[shared]")
{
    frts::LogPtr log = frts::LogPtr(new frts::TestLog());

    frts::TickablePtr tickable1 = frts::TickablePtr(new frts::TestTickable());
    frts::TickablePtr tickable2 = frts::TickablePtr(new frts::TestTickable());
    frts::TickablePtr tickable3 = frts::TickablePtr(new frts::TestTickable());
    std::vector<frts::TickablePtr> renderModules = {tickable1, tickable2};
    std::vector<frts::TickablePtr> updateModules = {tickable3};

    frts::SharedManagerImplPtr sharedImpl = frts::SharedManagerImplPtr(
                new frts::SharedManagerImpl(log, renderModules, updateModules));

    sharedImpl->setFrame(frts::FramePtr(new frts::FrameImpl(0.01, 124, 1.24)));

    frts::IdPtr notExistId = frts::IdPtr(new frts::IdImpl("notExistId"));

    frts::IdPtr dataValueId = frts::IdPtr(new frts::IdImpl("dataValueId"));
    frts::DataValuePtr dataValue1 = frts::DataValuePtr(new frts::TestDataValue());
    frts::DataValuePtr dataValue2 = frts::DataValuePtr(new frts::TestDataValue());
    sharedImpl->setValue(dataValueId, dataValue1);

    frts::UtilityPtr utility = frts::UtilityPtr(new frts::TestUtility());
    frts::IdPtr utilityId = frts::IdPtr(new frts::IdImpl(utility->getName()));
    sharedImpl->setUtility(utilityId, utility);

    frts::SharedManagerPtr shared = sharedImpl;

    REQUIRE(shared->getLog() == log);
    REQUIRE(std::distance(shared->renderModulesBegin(), shared->renderModulesEnd()) == 2);
    REQUIRE(std::distance(shared->updateModulesBegin(), shared->updateModulesEnd()) == 1);
    REQUIRE(shared->getFrame()->getDeltaTime() == Approx(0.01));
    REQUIRE(shared->getFrame()->getNumber() == 124);
    REQUIRE(shared->getFrame()->getRunTime() == Approx(1.24));
    REQUIRE(shared->getUtility(utilityId) == utility);
    REQUIRE_THROWS_AS(shared->getUtility(notExistId), frts::IdNotFoundError);

    REQUIRE(shared->getDataValue(dataValueId) == dataValue1);
    REQUIRE(shared->getDataValue(dataValueId) != dataValue2);
    REQUIRE_THROWS_AS(shared->getDataValue(notExistId), frts::IdNotFoundError);

    shared->setValue(dataValueId, dataValue2);
    REQUIRE(shared->getDataValue(dataValueId) != dataValue1);
    REQUIRE(shared->getDataValue(dataValueId) == dataValue2);
    REQUIRE_THROWS_AS(shared->getDataValue(notExistId), frts::IdNotFoundError);
}
