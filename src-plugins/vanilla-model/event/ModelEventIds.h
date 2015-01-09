#ifndef FRTS_MODELEVENTIDS
#define FRTS_MODELEVENTIDS

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of model event ID strings.
     */
    class ModelEventIds
    {
    public:
        static std::string entityEventValue()
        {
            return "frts.vanillamodel.event.value.entity";
        }

        static std::string entityListEventValue()
        {
            return "frts.vanillamodel.event.value.entity.list";
        }

        static std::string pointEventValue()
        {
            return "frts.vanillamodel.event.value.point";
        }

        static std::string pointListEventValue()
        {
            return "frts.vanillamodel.event.value.point.list";
        }
    };
}

#endif // FRTS_MODELEVENTIDS

