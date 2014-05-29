#ifndef FRTS_ISRESOURCEBUILDER_H
#define FRTS_ISRESOURCEBUILDER_H

#include <entity/ComponentBuilder.h>

#include <string>


namespace frts
{
    class IsResourceBuilder : public ComponentBuilder
    {
    public:
        IsResourceBuilder(const std::string& resource);

        ComponentPtr build(SharedManagerPtr shared) override;

    private:
        std::string resource;
    };

    inline ComponentBuilderPtr makeIsResourceBuilder(const std::string& resource)
    {
        return std::make_shared<IsResourceBuilder>(resource);
    }
}

#endif // FRTS_ISRESOURCEBUILDER_H
