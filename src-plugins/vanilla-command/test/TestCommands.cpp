#include <catch.hpp>

#include <command/QuitCommand.h>
#include <commandbuilder/QuitCommandBuilder.h>
#include <main/impl/CommandFactoryImpl.h>
#include <main/CommandIds.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("QuitCommand.", "[command]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeQuitCommandBuilder(shared->makeId("command.id"));
    auto command = builder->build(shared);
    REQUIRE(command != nullptr);

    REQUIRE_FALSE(shared->isQuitApplication());

    command->execute(shared);
    REQUIRE(shared->isQuitApplication());

    command->undo(shared);
    REQUIRE_FALSE(shared->isQuitApplication());
}

TEST_CASE("UndoCommand.", "[command]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto commandFactory = frts::makeCommandFactory();
    commandFactory->createData(shared);
    commandFactory->init(shared);

    shared->setUtility(shared->makeId(frts::CommandIds::commandFactory()), commandFactory);

    auto quitCommand = commandFactory->makeCommand(shared->makeId(frts::CommandIds::quit()), shared);
    REQUIRE(quitCommand != nullptr);

    REQUIRE_FALSE(shared->isQuitApplication());

    quitCommand->execute(shared);
    commandFactory->addToUndo(quitCommand, shared);
    REQUIRE(shared->isQuitApplication());

    auto undoCommand = commandFactory->makeCommand(shared->makeId(frts::CommandIds::undo()), shared);
    REQUIRE(undoCommand != nullptr);

    undoCommand->execute(shared);
    REQUIRE_FALSE(shared->isQuitApplication());
}
