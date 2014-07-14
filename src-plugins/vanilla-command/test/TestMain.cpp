#include <catch.hpp>

#include <main/impl/CommandFactoryImpl.h>
#include <main/CommandIds.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("CommandFactory.", "[main]")
{
    frts::LogPtr log = frts::makeNoLog();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);

    frts::CommandFactoryPtr commandFactory = frts::makeCommandFactory();
    commandFactory->createData(shared);
    commandFactory->init(shared);

    frts::IdPtr id = shared->makeId(frts::CommandIds::quit());
    REQUIRE(commandFactory->makeCommand(id, shared) != nullptr);
}
