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

        static std::string booleanListEventValue()
        {
            return "frts.vanillaevent.value.boolean.list";
        }

        static std::string eventManager()
        {
            return "frts::EventManager";
        }

        static std::string floatEventValue()
        {
            return "frts.vanillaevent.value.float";
        }

        static std::string floatListEventValue()
        {
            return "frts.vanillaevent.value.float.list";
        }

        static std::string idEventValue()
        {
            return "frts.vanillaevent.value.id";
        }

        static std::string idListEventValue()
        {
            return "frts.vanillaevent.value.id.list";
        }

        static std::string integerEventValue()
        {
            return "frts.vanillaevent.value.integer";
        }

        static std::string integerListEventValue()
        {
            return "frts.vanillaevent.value.integer.list";
        }

        static std::string stringEventValue()
        {
            return "frts.vanillaevent.value.string";
        }

        static std::string stringListEventValue()
        {
            return "frts.vanillaevent.value.string.list";
        }
    };
}

#endif // FRTS_EVENTIDS

