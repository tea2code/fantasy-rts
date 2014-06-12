#ifndef FRTS_DROPBUILDER_H
#define FRTS_DROPBUILDER_H

#include <entity/ComponentBuilder.h>


namespace frts
{
    class DropBuilder : public ComponentBuilder
    {
    public:
        DropBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    inline ComponentBuilderPtr makeDropBuilder()
    {
        return std::make_shared<DropBuilder>();
    }
}

#endif // FRTS_DROPBUILDER_H
