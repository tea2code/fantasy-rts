#ifndef FRTS_ISRESOURCEBUILDER_H
#define FRTS_ISRESOURCEBUILDER_H

#include <entity/ComponentBuilder.h>

#include <string>


namespace frts
{
    class IsResourceBuilder : public ComponentBuilder
    {
    public:
        IsResourceBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
    };

    /**
     * @brief Create new IsResourceBuilder.
     * @return The IsResourceBuilder.
     */
    inline ComponentBuilderPtr makeIsResourceBuilder()
    {
        return std::make_shared<IsResourceBuilder>();
    }
}

#endif // FRTS_ISRESOURCEBUILDER_H
