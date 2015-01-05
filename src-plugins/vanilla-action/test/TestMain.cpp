#include <catch.hpp>

#include <main/Action.h>
#include <main/ActionHandler.h>

#include <frts/shared>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


namespace test
{
    class TestAction : public frts::Action
    {
    public:
        TestAction(int doNumExecutions, int doNumStops)
            : doNumExecutions{doNumExecutions}, doNumStops{doNumStops}
        {}

        State execute(frts::SharedManagerPtr) override
        {
            numExecutions += 1;
            if (numExecutions >= doNumExecutions)
            {
                return State::Finished;
            }
            else
            {
                return State::Running;
            }
        }

        State stop(frts::SharedManagerPtr) override
        {
            numStops += 1;
            if (numStops >= doNumStops)
            {
                return State::Finished;
            }
            else
            {
                return State::Running;
            }
        }

        int getNumExecutions()
        {
            return numExecutions;
        }

        int getNumStops()
        {
            return numStops;
        }

    private:
        int doNumExecutions;
        int doNumStops;

        int numExecutions = 0;
        int numStops = 0;
    };
}


TEST_CASE("ActionManager.", "[main]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto actionManager = frts::makeActionHandler();

    SECTION("2, 0, 4, 0")
    {
        int doNumExecutions = 2;
        int doNumStops = 0;
        int doExecute = 4;
        int doStop = 0;
        auto action = std::make_shared<test::TestAction>(doNumExecutions, doNumStops);
        actionManager->newAction(action, shared);
        for (int i = 0; i < doExecute; ++i)
        {
            actionManager->tick(shared);
        }
        actionManager->stopAction(shared);
        for (int i = 0; i < doStop; ++i)
        {
            actionManager->tick(shared);
        }
        REQUIRE(action->getNumExecutions() == doNumExecutions);
        REQUIRE(action->getNumStops() == doNumStops);
    }

    SECTION("0, 2, 0, 4")
    {
        int doNumExecutions = 0;
        int doNumStops = 2;
        int doExecute = 0;
        int doStop = 2;
        auto action = std::make_shared<test::TestAction>(doNumExecutions, doNumStops);
        actionManager->newAction(action, shared);
        actionManager->stopAction(shared);
        for (int i = 0; i < doStop; ++i)
        {
            actionManager->tick(shared);
        }
        REQUIRE(action->getNumExecutions() == doNumExecutions);
        REQUIRE(action->getNumStops() == doNumStops);
    }

    SECTION("2, 1, 3, 4, 2")
    {
        int doNumExecutions = 2;
        int doNumStops = 1;
        int doExecute = 3;
        int doStop = 4;
        int ignoreExecutions = 2;
        auto action = std::make_shared<test::TestAction>(doNumExecutions, doNumStops);
        actionManager->newAction(action, shared);
        for (int i = 0; i < doExecute - ignoreExecutions; ++i)
        {
            actionManager->tick(shared);
        }
        actionManager->stopAction(shared);
        for (int i = 0; i < doStop; ++i)
        {
            actionManager->tick(shared);
        }
        REQUIRE(action->getNumExecutions() == doExecute - ignoreExecutions);
        REQUIRE(action->getNumStops() == doNumStops);
    }
}
