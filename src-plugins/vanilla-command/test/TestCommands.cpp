#include <catch.hpp>

#include <command/QuitCommand.h>
#include <commandbuilder/QuitCommandBuilder.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("QuitCommand.", "[command]")
{
    frts::LogPtr log = frts::makeNoLog();
    frts::SharedManagerPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

    frts::CommandBuilderPtr builder = frts::makeQuitCommandBuilder();
    frts::CommandPtr command = builder->build(shared);
    REQUIRE(command != nullptr);

    REQUIRE_FALSE(shared->isQuitApplication());

    command->execute(shared);
    REQUIRE(shared->isQuitApplication());

    command->undo(shared);
    REQUIRE_FALSE(shared->isQuitApplication());
}
