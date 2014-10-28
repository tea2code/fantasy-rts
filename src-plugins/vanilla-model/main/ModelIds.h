#ifndef FRTS_MODELIDS_H
#define FRTS_MODELIDS_H

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of model ID strings.
     */
    class ModelIds
    {
    public:
        static std::string modelFactory()
        {
            return "frts/ModelFactory";
        }

        static std::string regionConfig()
        {
            return "frts.vanillamodel.regionconfig";
        }

        static std::string regionManager()
        {
            return "frts.vanillamodel.regionmanager";
        }
    };
}

#endif // FRTS_MODELIDS_H
