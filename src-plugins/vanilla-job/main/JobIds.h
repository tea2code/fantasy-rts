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
        static std::string jobManager()
        {
            return "frts::JobManager";
        }
    };
}

#endif // FRTS_JOBIDS

