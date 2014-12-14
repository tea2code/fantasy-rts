#ifndef FRTS_TEXTMAPPARSER_H
#define FRTS_TEXTMAPPARSER_H

#include <regiongenerator/MapParser.h>


namespace frts
{
    class TextMapParser : public MapParser
    {
    public:
        TextMapParser();

        std::string getSupportedConfig() const override;
        void init(SharedManagerPtr shared) override;
        WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared) override;
        void parseConfig(ConfigNodePtr node, SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
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
