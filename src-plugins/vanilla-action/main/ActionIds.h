#ifndef FRTS_ACTIONIDS
#define FRTS_ACTIONIDS

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of action ID strings.
     */
    class ActionIds
    {
    public:
        static std::string actionManager()
        {
            return "frts::ActionManager";
        }
    };
}

#endif // FRTS_ACTIONIDS

