#ifndef FRTS_ACTION
#define FRTS_ACTION

#include <frts/shared>

#include <memory>


namespace frts
{
    class Action;

    /**
     * @brief Pointer to Action.
     */
    using ActionPtr = std::shared_ptr<Action>;

    /**
     * @brief Interface for actions.
     */
    class Action
    {
    public:
        /**
         * @brief Result of action methods. Handled by action manager.
         *        Cancel: Indicates that this action wants to cancel its execution.
         *        Finished: Indicates that execution is complete.
         *        Running: Indicates that more executions are necessary to complete.
         */
        enum class State
        {
            Cancel,
            Finished,
            Running
        };

    public:
        virtual ~Action() {}

        /**
         * @brief Execute this action. Will be called while it returns "Running".
         * @param shared The shared manager.
         * @return Current state of this execution.
         */
        virtual State execute(SharedManagerPtr shared) = 0;

        /**
         * @brief Initialize this action.
         * @param shared The shared manager.
         */
        virtual void init(SharedManagerPtr shared) = 0;

        /**
         * @brief Stop this action. Will be called while it returns "Running".
         * @param shared The shared manager.
         * @return Current state of the stopping process.
         */
        virtual State stop(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_ACTION

