#ifndef FRTS_REGIONGENERATORIDS_H
#define FRTS_REGIONGENERATORIDS_H

#include <string>


namespace frts
{
    /**
     * @brief Simple collection of region generator ID strings.
     */
    class RegionGeneratorIds
    {
    public:
        static std::string bmpMapParser()
        {
            return "frts.vanillamodel.regiongenerator.mapparser.bmp";
        }

        static std::string textMapParser()
        {
            return "frts.vanillamodel.regiongenerator.mapparser.text";
        }

    };
}

#endif // FRTS_REGIONGENERATORIDS_H
