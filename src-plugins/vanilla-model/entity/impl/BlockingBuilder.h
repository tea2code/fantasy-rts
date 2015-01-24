#ifndef FRTS_BLOCKINGBUILDER_H
#define FRTS_BLOCKINGBUILDER_H

#include <entity/ComponentBuilder.h>


namespace frts
{
    class BlockingBuilder : public ComponentBuilder
    {
    public:
        BlockingBuilder();

        ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node) override;
    };

    inline ComponentBuilderPtr makeBlockingBuilder()
    {
        return std::make_shared<BlockingBuilder>();
    }
}

#endif // FRTS_BLOCKINGBUILDER_H
