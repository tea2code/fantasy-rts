#ifndef FRTS_BLOCKINGBUILDER_H
#define FRTS_BLOCKINGBUILDER_H

#include <entity/ComponentBuilder.h>


namespace frts
{
    class BlockingBuilder : public ComponentBuilder
    {
    public:
        BlockingBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    inline ComponentBuilderPtr makeBlockingBuilder()
    {
        return std::make_shared<BlockingBuilder>();
    }
}

#endif // FRTS_BLOCKINGBUILDER_H
