#ifndef FRTS_TEXTMAPPARSER_H
#define FRTS_TEXTMAPPARSER_H

#include <regiongenerator/MapParser.h>


namespace frts
{
    class TextMapParser : public MapParser
    {
    public:
        TextMapParser();

        WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared);
        void parseConfig(ConfigNodePtr node, SharedManagerPtr shared);
        void validateData(SharedManagerPtr shared);
    };

    /**
     * @brief Create new TextMapParser.
     * @return The map parser.
     */
    inline MapParserPtr makeTextMapParser()
    {
        return std::make_shared<TextMapParser>();
    }
}

#endif // FRTS_TEXTMAPPARSER_H
