#include <catch.hpp>

#include <main/Job.h>
#include <main/JobHandler.h>
#include <main/JobIds.h>
#include <main/impl/JobManagerImpl.h>

#include <frts/shared>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>
#include <shared/impl/FrameImpl.h>

#include <queue>


namespace test
{
    class TestJob : public frts::Job
    {
    public:
        TestJob(int doNumExecutions, int doNumStops, std::queue<frts::Frame::time> dueTimes)
            : doNumExecutions{doNumExecutions}, doNumStops{doNumStops}, dueTimes{dueTimes}
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

        frts::Frame::time getDueTime() const override
        {
            auto result = dueTimes.front();
            dueTimes.pop();
            return result;
        }

        frts::EntityPtr getExecutingEntity() const override
        {
            return nullptr;
        }

        std::vector<frts::IdPtr> getRequirements() const override
        {
            return {};
        }

        void setExecutingEntity(frts::EntityPtr) override
        {}

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

        // Const cheating.
        mutable std::queue<frts::Frame::time> dueTimes;
    };
}


TEST_CASE("JobHandler.", "[main]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto jobHandler = frts::makeJobHandler();

    SECTION("2 executions.")
    {
        int doNumExecutions = 2;
        int doNumStops = 0;
        std::queue<frts::Frame::time> dueTimes;
        dueTimes.push(frts::fromMilliseconds(1));
        dueTimes.push(frts::fromMilliseconds(3));
        auto job = std::make_shared<test::TestJob>(doNumExecutions, doNumStops, dueTimes);
        jobHandler->runJob(job);

        int num = 1;
        auto frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 1);
        REQUIRE(job->getNumStops() == 0);

        num = 2;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 1);
        REQUIRE(job->getNumStops() == 0);

        num = 3;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 2);
        REQUIRE(job->getNumStops() == 0);

        num = 4;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 2);
        REQUIRE(job->getNumStops() == 0);
    }

    SECTION("1 execution 2 stops.")
    {
        int doNumExecutions = 1;
        int doNumStops = 2;
        std::queue<frts::Frame::time> dueTimes;
        dueTimes.push(frts::fromMilliseconds(1));
        dueTimes.push(frts::fromMilliseconds(3));
        dueTimes.push(frts::fromMilliseconds(4));
        auto job = std::make_shared<test::TestJob>(doNumExecutions, doNumStops, dueTimes);
        jobHandler->runJob(job);

        int num = 1;
        auto frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 1);
        REQUIRE(job->getNumStops() == 0);

        num = 2;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 1);
        REQUIRE(job->getNumStops() == 0);

        num = 3;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 1);
        REQUIRE(job->getNumStops() == 1);

        num = 4;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 1);
        REQUIRE(job->getNumStops() == 2);

        num = 5;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 1);
        REQUIRE(job->getNumStops() == 2);
    }
}
