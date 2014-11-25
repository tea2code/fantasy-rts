#ifndef FRTS_TELEPORTBUILDER_H
#define FRTS_TELEPORTBUILDER_H

#include <entity/ComponentBuilder.h>


namespace frts
{
    class TeleportBuilder : public ComponentBuilder
    {
    public:
        TeleportBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    inline ComponentBuilderPtr makeTeleportBuilder()
    {
        return std::make_shared<TeleportBuilder>();
    }
}

#endif // FRTS_TELEPORTBUILDER_H
