#ifndef FRTS_HASRESOURCEBUILDER_H
#define FRTS_HASRESOURCEBUILDER_H

#include <entity/ComponentBuilder.h>

#include <string>


namespace frts
{
    class HasResourceBuilder : public ComponentBuilder
    {
    public:
        HasResourceBuilder(const std::string& resource);

        ComponentPtr build(SharedManagerPtr shared) override;

    private:
        std::string resource;
    };

    inline ComponentBuilderPtr makeHasResourceBuilder(const std::string& resource)
    {
        return std::make_shared<HasResourceBuilder>(resource);
    }
}

#endif // FRTS_HASRESOURCEBUILDER_H
