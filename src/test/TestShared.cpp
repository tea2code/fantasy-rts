#include <catch.hpp>

#include <log/Log.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <shared/DataValue.h>
#include <shared/impl/FrameImpl.h>
#include <shared/impl/IdImpl.h>
#include <shared/SharedError.h>
#include <shared/impl/MainDataImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>


namespace TestShared
{
    class TestLog : public frts::Log
    {
    public:
        TestLog() {}
        void debug(const std::string&, const std::string&) override {}
        void error(const std::string&, const std::string&) override {}
        void info(const std::string&, const std::string&) override {}
        void warning(const std::string&, const std::string&) override {}
    };

    class TestDataValue : public frts::DataValue
    {
    public:
        std::string getName() const override { return "TestDataValue"; }
        std::string getTypeName() const override { return getName(); }
        int getTypeVersion() const override { return getVersion(); }
        int getVersion() const override { return 1; }
    };

    class TestTickable : public frts::Tickable
    {
    public:
        TestTickable() {}
        void checkRequiredData(const frts::SharedManagerPtr&) override {}
        bool createData(const frts::SharedManagerPtr&) override { return false; }
        std::string getName() const override { return "TestTickable"; }
        std::vector<std::string> getSupportedConfig() override { return {}; }
        std::string getTypeName() const override { return getName(); }
        int getTypeVersion() const override { return getVersion(); }
        int getVersion() const override { return 1; }
        bool init(const frts::SharedManagerPtr&) override { return false; }
        bool isInitialized() const override { return false; }
        bool isPreInitialized() const override { return false; }
        void parseConfig(const std::string&, const frts::ConfigNodePtr&, const frts::SharedManagerPtr&) override {}
        bool preInit(const frts::SharedManagerPtr&) override { return false; }
        void tick(const frts::SharedManagerPtr&) override {}
        void validateData(const frts::SharedManagerPtr&) override {}
        void validateModules(const frts::SharedManagerPtr&) override {}
    };

    class TestUtility : public frts::Utility
    {
    public:
        TestUtility() {}
        void checkRequiredData(const frts::SharedManagerPtr&) override {}
        bool createData(const frts::SharedManagerPtr&) override { return false; }
        std::string getName() const override { return "TestUtility"; }
        std::vector<std::string> getSupportedConfig() override { return {}; }
        std::string getTypeName() const override { return getName(); }
        int getTypeVersion() const override { return getVersion(); }
        int getVersion() const override { return 1; }
        bool init(const frts::SharedManagerPtr&) override { return false; }
        bool isInitialized() const override { return false; }
        bool isPreInitialized() const override { return false; }
        void parseConfig(const std::string&, const frts::ConfigNodePtr&, const frts::SharedManagerPtr&) override {}
        bool preInit(const frts::SharedManagerPtr&) override { return false; }
        void validateData(const frts::SharedManagerPtr&) override {}
        void validateModules(const frts::SharedManagerPtr&) override {}
    };
}

TEST_CASE("Create and use frame data.", "[shared]")
{
    frts::Frame::time deltaTime = frts::fromMilliseconds(2);
    frts::Frame::ticks number = 4098353456392489llu;
    frts::Frame::time runTime = frts::fromMilliseconds(254121541);
    frts::FramePtr frame = std::make_shared<frts::FrameImpl>(deltaTime, number, runTime);

    REQUIRE(frame->getDeltaTime() == deltaTime);
    REQUIRE(frame->getNumber() == number);
    REQUIRE(frame->getRunTime() == runTime);
}

TEST_CASE("Create and use id.", "[shared]")
{
    frts::IdPtr id1 = frts::makeId("test");
    frts::IdPtr id2 = frts::makeId("test");

    frts::IdPtr id3 = frts::makeId("testtest");

    REQUIRE(id1->toString() == "test");
    REQUIRE(id2->toString() == "test");
    REQUIRE(id3->toString() == "testtest");
    REQUIRE(id1 == id2);
    REQUIRE(id1 != id3);
    REQUIRE(id2 != id3);
    REQUIRE_FALSE(id1 < id2);
    REQUIRE_FALSE(id2 < id1);
    REQUIRE(id1 < id3);
    REQUIRE(id2 < id3);
    REQUIRE_FALSE(id3 < id1);
    REQUIRE_FALSE(id3 < id2);
}

TEST_CASE("Create and use shared manager.", "[shared]")
{
    frts::LogPtr log = std::make_shared<TestShared::TestLog>();

    frts::SharedManagerImplPtr sharedImpl = frts::makeSharedManager(log);

    frts::Frame::time deltaTime = frts::fromMilliseconds(10);
    frts::Frame::ticks numberFrames = 124llu;
    frts::Frame::time runTime = frts::fromMilliseconds(1240);
    sharedImpl->setFrame(std::make_shared<frts::FrameImpl>(deltaTime, numberFrames, runTime));

    frts::IdPtr notExistId = frts::makeId("notExistId");

    frts::IdPtr dataValueId1 = frts::makeId("dataValueId");
    frts::IdPtr dataValueId2 = frts::makeId("dataValueId");
    frts::DataValuePtr dataValue1 = std::make_shared<TestShared::TestDataValue>();
    frts::DataValuePtr dataValue2 = std::make_shared<TestShared::TestDataValue>();
    sharedImpl->setDataValue(dataValueId1, dataValue1);

    frts::TickablePtr tickable1 = std::make_shared<TestShared::TestTickable>();
    frts::TickablePtr tickable2 = std::make_shared<TestShared::TestTickable>();
    frts::TickablePtr tickable3 = std::make_shared<TestShared::TestTickable>();
    std::vector<frts::TickablePtr> renderModules = {tickable1, tickable2};
    std::vector<frts::TickablePtr> updateModules = {tickable3};
    sharedImpl->setRenderModules(renderModules);
    sharedImpl->setUpdateModules(updateModules);

    frts::UtilityPtr utility = std::make_shared<TestShared::TestUtility>();
    frts::IdPtr utilityId = frts::makeId(utility->getName());
    sharedImpl->setUtility(utilityId, utility);

    frts::SharedManagerPtr shared = sharedImpl;

    REQUIRE(shared->getLog() == log);
    REQUIRE(std::distance(shared->renderModulesBegin(), shared->renderModulesEnd()) == 2);
    REQUIRE(std::distance(shared->updateModulesBegin(), shared->updateModulesEnd()) == 1);
    REQUIRE(shared->getFrame()->getDeltaTime() == deltaTime);
    REQUIRE(shared->getFrame()->getNumber() == numberFrames);
    REQUIRE(shared->getFrame()->getRunTime() == runTime);
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

TEST_CASE("MainData", "[shared]")
{
    frts::MainDataPtr mainData = frts::makeMainData("plugins/", frts::fromMilliseconds(10));

    REQUIRE(mainData->getPluginPath() == "plugins/");
}
