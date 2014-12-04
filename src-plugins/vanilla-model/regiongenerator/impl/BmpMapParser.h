#ifndef FRTS_BMPMAPPARSER_H
#define FRTS_BMPMAPPARSER_H

#include <regiongenerator/MapParser.h>


namespace frts
{
    class BmpMapParser : public MapParser
    {
    public:
        BmpMapParser();

        WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared);
        void parseConfig(ConfigNodePtr node, SharedManagerPtr shared);
        void validateData(SharedManagerPtr shared);
    };

    /**
     * @brief Create new BmpMapParser.
     * @return The map parser.
     */
    inline MapParserPtr makeBmpMapParser()
    {
        return std::make_shared<BmpMapParser>();
    }
}

#endif // FRTS_BMPMAPPARSER_H
