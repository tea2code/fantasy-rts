#include <catch.hpp>

#include <main/impl/CommandFactoryImpl.h>
#include <main/CommandIds.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("CommandFactory.", "[main]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

    frts::CommandFactoryPtr commandFactory = frts::makeCommandFactory();
    commandFactory->createData(shared);
    commandFactory->init(shared);

    frts::IdPtr id = shared->makeId(frts::CommandIds::quit());
    REQUIRE(commandFactory->makeCommand(id, shared) != nullptr);
}
