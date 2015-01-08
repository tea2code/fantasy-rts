#ifndef FRTS_JOBIDS
#define FRTS_JOBIDS

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of job ID strings.
     */
    class JobIds
    {
    public:
        static std::string entityEventValue()
        {
            return "frts.vanillajob.event.value.entity";
        }

        static std::string jobCanceledEvent()
        {
            return "frts.vanillajob.event.job.canceled";
        }

        static std::string jobFinishedEvent()
        {
            return "frts.vanillajob.event.job.finished";
        }

        static std::string jobHandler()
        {
            return "frts::JobHandler";
        }

        static std::string jobManager()
        {
            return "frts::JobManager";
        }

        static std::string jobStoppedEvent()
        {
            return "frts.vanillajob.event.job.stopped";
        }
    };
}

#endif // FRTS_JOBIDS

