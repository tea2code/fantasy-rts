#include <catch.hpp>

#include <main/Job.h>
#include <main/JobHandler.h>
#include <main/JobIds.h>
#include <main/impl/JobManagerImpl.h>

#include <frts/shared>
#include <frts/vanillamodel>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>
#include <shared/impl/FrameImpl.h>
#include <entity/impl/EntityImpl.h>
#include <entity/impl/CurriculumImpl.h>

#include <queue>


namespace test
{
    class TestJob : public frts::Job
    {
    public:
        TestJob(int doNumExecutions, int doNumStops, std::queue<frts::Frame::time> dueTimes, std::vector<frts::IdPtr> requirements = {})
            : doNumExecutions{doNumExecutions}, doNumStops{doNumStops}, dueTimes{dueTimes}, requirements{requirements}
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
            return requirements;
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

        std::vector<frts::IdPtr> requirements;
    };
}


TEST_CASE("JobHandler.", "[main]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto jobHandler = frts::makeJobHandler();

    SECTION("2 executions 0 stops.")
    {
        int doNumExecutions = 2;
        int doNumStops = 0;
        std::queue<frts::Frame::time> dueTimes;
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

    SECTION("0 execution 3 stops.")
    {
        int doNumExecutions = 0;
        int doNumStops = 3;
        std::queue<frts::Frame::time> dueTimes;
        dueTimes.push(frts::fromMilliseconds(3));
        dueTimes.push(frts::fromMilliseconds(4));
        auto job = std::make_shared<test::TestJob>(doNumExecutions, doNumStops, dueTimes);
        jobHandler->runJob(job);

        jobHandler->stopJob(job);

        auto num = 2;
        auto frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 0);
        REQUIRE(job->getNumStops() == 1);

        num = 3;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 0);
        REQUIRE(job->getNumStops() == 2);

        num = 4;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 0);
        REQUIRE(job->getNumStops() == 3);

        num = 5;
        frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
        shared->setFrame(frame);
        jobHandler->tick(shared);
        REQUIRE(job->getNumExecutions() == 0);
        REQUIRE(job->getNumStops() == 3);
    }
}

TEST_CASE("Job manager.", "[main]")
{
    auto log = frts::makeNoLog();
    auto shared = frts::makeSharedManager(log);

    auto jobHandler = frts::makeJobHandler();
    auto jobManager = frts::makeJobManager(jobHandler);

    int num = 1;
    auto frame = frts::makeFrame(frts::fromMilliseconds(num),num, frts::fromMilliseconds(num));
    shared->setFrame(frame);

    int doNumExecutions = 1;
    int doNumStops = 0;
    std::queue<frts::Frame::time> dueTimes;

    auto ability1 = shared->makeId("requirement.1");
    std::vector<frts::IdPtr> requirements1 = {ability1};
    auto job1 = std::make_shared<test::TestJob>(doNumExecutions, doNumStops, dueTimes, requirements1);

    auto ability2 = shared->makeId("requirement.2");
    std::vector<frts::IdPtr> requirements2 = {ability2};
    auto job2 = std::make_shared<test::TestJob>(doNumExecutions, doNumStops, dueTimes, requirements2);

    auto entity = frts::makeEntity();
    auto curriculum = frts::makeCurriculum(shared->makeId(frts::ComponentIds::curriculum()));
    curriculum->addAbility(ability1);
    entity->addComponent(curriculum);

    jobManager->addJob(job2);
    jobHandler->tick(shared);
    REQUIRE(job1->getNumExecutions() == 0);
    REQUIRE(job2->getNumExecutions() == 0);

    bool employed = jobManager->employEntity(entity, shared);
    jobHandler->tick(shared);
    REQUIRE_FALSE(employed);
    REQUIRE(job1->getNumExecutions() == 0);
    REQUIRE(job2->getNumExecutions() == 0);

    jobManager->addJob(job1);
    jobHandler->tick(shared);
    REQUIRE(job1->getNumExecutions() == 0);
    REQUIRE(job2->getNumExecutions() == 0);

    jobManager->stopJob(job1);
    jobHandler->tick(shared);
    REQUIRE(job1->getNumExecutions() == 0);
    REQUIRE(job2->getNumExecutions() == 0);

    employed = jobManager->employEntity(entity, shared);
    jobHandler->tick(shared);
    REQUIRE_FALSE(employed);
    REQUIRE(job1->getNumExecutions() == 0);
    REQUIRE(job2->getNumExecutions() == 0);

    jobManager->addJob(job1);
    jobHandler->tick(shared);
    REQUIRE(job1->getNumExecutions() == 0);
    REQUIRE(job2->getNumExecutions() == 0);

    employed = jobManager->employEntity(entity, shared);
    jobHandler->tick(shared);
    REQUIRE(employed);
    REQUIRE(job1->getNumExecutions() == 1);
    REQUIRE(job2->getNumExecutions() == 0);
}