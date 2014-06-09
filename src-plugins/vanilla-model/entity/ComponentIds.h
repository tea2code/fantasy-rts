#ifndef FRTS_COMPONENTIDS_H
#define FRTS_COMPONENTIDS_H

#include <string>

namespace frts
{
    /**
     * @brief Simple collection of component ID strings.
     */
    class ComponentIds
    {
    public:
        static std::string blockedBy()
        {
            return "frts.vanillamodel.entity.component.blockedby";
        }

        static std::string blocking()
        {
            return "frts.vanillamodel.entity.component.blocking";
        }

        static std::string drop()
        {
            return "frts.vanillamodel.entity.component.drop";
        }

        static std::string hasResource()
        {
            return "frts.vanillamodel.entity.component.hasresource";
        }

        static std::string isResource()
        {
            return "frts.vanillamodel.entity.component.isresource";
        }

        static std::string sortOrder()
        {
            return "frts.vanillamodel.entity.component.sortorder";
        }
    };
}

#endif // FRTS_COMPONENTIDS_H
