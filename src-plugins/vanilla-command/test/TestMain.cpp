#include <catch.hpp>

#include <main/impl/CommandConfigImpl.h>
#include <main/impl/CommandFactoryImpl.h>
#include <main/CommandIds.h>

#include <frts/shared>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("CommandFactory.", "[main]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto commandFactory = frts::makeCommandFactory();
    commandFactory->createData(shared);
    commandFactory->init(shared);

    auto id = shared->makeId(frts::CommandIds::quit());
    REQUIRE(commandFactory->makeCommand(id, shared) != nullptr);
}

TEST_CASE("CommandConfig.", "[main]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto commandConfig = frts::makeCommandConfig();

    frts::IdUnorderedSet commands {
        shared->makeId("command.id.1"),
        shared->makeId("command.id.2")
    };
    commandConfig->setNotUndoableCommands(commands);
    commandConfig->setNumUndo(1);

    REQUIRE(commandConfig->getNotUndoableCommands().size() == 2);
    REQUIRE(commandConfig->getNumUndo() == 1);
}
