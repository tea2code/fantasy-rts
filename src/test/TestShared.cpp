#include <catch.hpp>

#include <log/Log.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <shared/DataValue.h>
#include <shared/impl/FrameImpl.h>
#include <shared/impl/IdImpl.h>
#include <shared/SharedError.h>
#include <shared/impl/SharedManagerImpl.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>


TEST_CASE("Create and use frame data.", "[shared]")
{
    double deltaTime = 0.002145;
    unsigned long long number = 4098353456392489llu;
    double runTime = 254121.54123;
    frts::FramePtr frame = std::make_shared<frts::FrameImpl>(deltaTime, number, runTime);

    REQUIRE(frame->getDeltaTime() == Approx(deltaTime));
    REQUIRE(frame->getNumber() == number);
    REQUIRE(frame->getRunTime() == Approx(runTime));
}


TEST_CASE("Create and use id.", "[shared]")
{
    std::string str1 = "test";
    frts::IdPtr id1 = frts::makeId(str1);
    frts::IdPtr id2 = frts::makeId(str1);

    std::string str2 = "testtest";
    frts::IdPtr id3 = frts::makeId(str2);

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
        void debug(const std::string&, const std::string&) {}
        void error(const std::string&, const std::string&) {}
        void info(const std::string&, const std::string&) {}
        void warning(const std::string&, const std::string&) {}
    };

    class TestDataValue : public DataValue
    {
    public:
        ~TestDataValue() {}
        std::string getName() const { return "TestDataValue"; }
    };

    class TestTickable : public Tickable
    {
    public:
        TestTickable() {}
        ~TestTickable() {}
        void createData(SharedManagerPtr) {}
        std::string getName() const { return "TestTickable"; }
        std::vector<std::string> getSupportedConfig() { return std::vector<std::string>(); }
        int getVersion() const { return 1; }
        void init(SharedManagerPtr) {}
        void parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr) {}
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
        int getVersion() const { return 1; }
        void init(SharedManagerPtr) {}
        void parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr) {}
        void validateData(SharedManagerPtr) {}
        void validateModules(SharedManagerPtr) {}
    };
}

TEST_CASE("Create and use shared manager.", "[shared]")
{
    frts::LogPtr log = std::make_shared<frts::TestLog>();

    frts::SharedManagerImplPtr sharedImpl = std::make_shared<frts::SharedManagerImpl>(log);

    sharedImpl->setFrame(std::make_shared<frts::FrameImpl>(0.01, 124, 1.24));

    frts::IdPtr notExistId = frts::makeId("notExistId");

    frts::IdPtr dataValueId1 = frts::makeId("dataValueId");
    frts::IdPtr dataValueId2 = frts::makeId("dataValueId");
    frts::DataValuePtr dataValue1 = std::make_shared<frts::TestDataValue>();
    frts::DataValuePtr dataValue2 = std::make_shared<frts::TestDataValue>();
    sharedImpl->setDataValue(dataValueId1, dataValue1);

    frts::TickablePtr tickable1 = std::make_shared<frts::TestTickable>();
    frts::TickablePtr tickable2 = std::make_shared<frts::TestTickable>();
    frts::TickablePtr tickable3 = std::make_shared<frts::TestTickable>();
    std::vector<frts::TickablePtr> renderModules = {tickable1, tickable2};
    std::vector<frts::TickablePtr> updateModules = {tickable3};
    sharedImpl->setRenderModules(renderModules);
    sharedImpl->setUpdateModules(updateModules);

    frts::UtilityPtr utility = std::make_shared<frts::TestUtility>();
    frts::IdPtr utilityId = frts::makeId(utility->getName());
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

    REQUIRE_FALSE(shared->isQuitApplication() );
    shared->setQuitApplication(true);
    REQUIRE(shared->isQuitApplication());

    REQUIRE(shared->getDataValue(dataValueId1) == dataValue1);
    REQUIRE(shared->getDataValue(dataValueId2) == dataValue1);
    REQUIRE(shared->getDataValue(dataValueId1) != dataValue2);
    REQUIRE_THROWS_AS(shared->getDataValue(notExistId), frts::IdNotFoundError);

    shared->setDataValue(dataValueId1, dataValue2);
    REQUIRE(shared->getDataValue(dataValueId1) != dataValue1);
    REQUIRE(shared->getDataValue(dataValueId1) == dataValue2);
    REQUIRE(shared->getDataValue(dataValueId2) == dataValue2);
    REQUIRE_THROWS_AS(shared->getDataValue(notExistId), frts::IdNotFoundError);
}
