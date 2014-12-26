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
        static std::string booleanEventValue()
        {
            return "frts.vanillaevent.value.boolean";
        }

        static std::string eventManager()
        {
            return "frts::EventManager";
        }

        static std::string floatEventValue()
        {
            return "frts.vanillaevent.value.float";
        }

        static std::string idEventValue()
        {
            return "frts.vanillaevent.value.id";
        }

        static std::string integerEventValue()
        {
            return "frts.vanillaevent.value.integer";
        }

        static std::string stringEventValue()
        {
            return "frts.vanillaevent.value.string";
        }
    };
}

#endif // FRTS_EVENTIDS

