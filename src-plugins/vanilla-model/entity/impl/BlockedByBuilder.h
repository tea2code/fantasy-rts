#ifndef FRTS_BLOCKEDBYBUILDER_H
#define FRTS_BLOCKEDBYBUILDER_H

#include <entity/ComponentBuilder.h>

namespace frts
{
    class BlockedByBuilder : public ComponentBuilder
    {
    public:
        BlockedByBuilder();

        ComponentPtr build(const SharedManagerPtr& shared) override;
        ComponentPtr build(const SharedManagerPtr& shared, const ConfigNodePtr& node) override;
    };

    inline ComponentBuilderPtr makeBlockedByBuilder()
    {
        return std::make_shared<BlockedByBuilder>();
    }
}

#endif // FRTS_BLOCKEDBYBUILDER_H
