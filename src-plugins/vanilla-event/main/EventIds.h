#ifndef FRTS_EVENTIDS
#define FRTS_EVENTIDS

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of event ID strings.
     */
    class EventIds
    {
    public:
        static std::string eventManager()
        {
            return "frts::EventManager";
        }
    };
}

#endif // FRTS_EVENTIDS

