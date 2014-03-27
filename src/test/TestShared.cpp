#include <catch.hpp>

#include <log/Log.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <shared/DataValue.h>
#include <shared/FrameImpl.h>
#include <shared/IdImpl.h>
#include <shared/SharedManagerImpl.h>

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

    frts::IdPtr id1 = frts::IdPtr(new frts::IdImpl("1"));
    frts::IdPtr id2 = frts::IdPtr(new frts::IdImpl("2"));
    frts::DataValuePtr dataValue = frts::DataValuePtr(new frts::TestDataValue());
    sharedImpl->setValue(id1, dataValue);

    frts::UtilityPtr utility = frts::UtilityPtr(new frts::TestUtility());
    frts::IdPtr utilityId = frts::IdPtr(new frts::IdImpl(utility->getName()));

    frts::SharedManagerPtr shared = frts::SharedManagerPtr(sharedImpl.get());


}
