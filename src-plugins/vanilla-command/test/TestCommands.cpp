#include <catch.hpp>

#include <command/QuitCommand.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("QuitCommand.", "[command]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

    frts::CommandPtr command = frts::makeQuitCommand();

    REQUIRE_FALSE(shared->isQuitApplication());

    command->execute(shared);
    REQUIRE(shared->isQuitApplication());

    command->undo(shared);
    REQUIRE_FALSE(shared->isQuitApplication());
}
