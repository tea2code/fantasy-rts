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
        void init(const SharedManagerPtr& shared) override;
        WriteableBlockPtr newBlock(const PointPtr& pos, const SharedManagerPtr& shared) override;
        void parseConfig(const ConfigNodePtr& node, const SharedManagerPtr& shared) override;
        void validateData(const SharedManagerPtr& shared) override;
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
