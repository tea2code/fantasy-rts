#ifndef FRTS_STOPJOBSACTION_H
#define FRTS_STOPJOBSACTION_H

#include <frts/vanillaaction>
#include <frts/vanillaevent>
#include <frts/vanillamodel>


namespace frts
{
    class StopJobsAction : public Action, public EventObserver, public std::enable_shared_from_this<EventObserver>
    {
    public:
        StopJobsAction(const IdUnorderedSet& jobs, const IdUnorderedSet& types);
        ~StopJobsAction();

        State execute(const SharedManagerPtr& shared) override;
        void notify(const EventPtr& event, const SharedManagerPtr& shared) override;
        State stop(const SharedManagerPtr& shared) override;

    private:
        /**
         * @brief Internal state of action.
         */
        enum class ActionState
        {
            FirstExecution,
            WaitingForSelection,
            SelectionReceived,
            Finished,
            Stopped
        };

    private:
        const std::string name = "frts::StopJobsAction";

        ActionState actionState = ActionState::FirstExecution;

        IdUnorderedSet jobs;
        IdUnorderedSet types;

        PointVector selection;
    };

    /**
     * @brief Create new StopJobsAction.
     * @param jobs List of job ids.
     * @param type List of type ids.
     * @return The action.
     */
    inline ActionPtr makeStopJobsAction(const IdUnorderedSet& jobs, const IdUnorderedSet& types)
    {
        return std::make_shared<StopJobsAction>(jobs, types);
    }
}

#endif // FRTS_STOPJOBSACTION_H
