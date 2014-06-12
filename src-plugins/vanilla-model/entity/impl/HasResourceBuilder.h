#ifndef FRTS_HASRESOURCEBUILDER_H
#define FRTS_HASRESOURCEBUILDER_H

#include <entity/ComponentBuilder.h>

#include <string>


namespace frts
{
    class HasResourceBuilder : public ComponentBuilder
    {
    public:
        HasResourceBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    inline ComponentBuilderPtr makeHasResourceBuilder()
    {
        return std::make_shared<HasResourceBuilder>();
    }
}

#endif // FRTS_HASRESOURCEBUILDER_H
