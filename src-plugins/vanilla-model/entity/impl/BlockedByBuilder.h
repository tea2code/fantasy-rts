#ifndef FRTS_BLOCKEDBYBUILDER_H
#define FRTS_BLOCKEDBYBUILDER_H

#include <entity/ComponentBuilder.h>

namespace frts
{
    class BlockedByBuilder : public ComponentBuilder
    {
    public:
        BlockedByBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
    };

    inline ComponentBuilderPtr makeBlockedByBuilder()
    {
        return std::make_shared<BlockedByBuilder>();
    }
}

#endif // FRTS_BLOCKEDBYBUILDER_H
