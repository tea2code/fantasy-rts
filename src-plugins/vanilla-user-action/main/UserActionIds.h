#ifndef FRTS_USERACTIONIDS
#define FRTS_USERACTIONIDS

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of user-action ID strings.
     */
    class UserActionIds
    {
    public:
        static std::string carve()
        {
            return "frts.vanillauseraction.useraction.carve";
        }

        static std::string harvest()
        {
            return "frts.vanillauseraction.useraction.harvest";
        }

        static std::string stopJobs()
        {
            return "frts.vanillauseraction.useraction.stopjobs";
        }

        static std::string userActionFactory()
        {
            return "frts::UserActionFactory";
        }
    };
}

#endif // FRTS_USERACTIONIDS

