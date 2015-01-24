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

        ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node) override;
    };

    inline ComponentBuilderPtr makeHasResourceBuilder()
    {
        return std::make_shared<HasResourceBuilder>();
    }
}

#endif // FRTS_HASRESOURCEBUILDER_H
