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
        static std::string userActionFactory()
        {
            return "frts::UserActionFactory";
        }
    };
}

#endif // FRTS_USERACTIONIDS

