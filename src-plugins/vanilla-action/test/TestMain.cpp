#include <catch.hpp>

#include <main/Action.h>

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
