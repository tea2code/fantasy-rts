#ifndef FRTS_SORTORDERBUILDER_H
#define FRTS_SORTORDERBUILDER_H

#include <entity/ComponentBuilder.h>


namespace frts
{
    class SortOrderBuilder : public ComponentBuilder
    {
    public:
        SortOrderBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
    };

    inline ComponentBuilderPtr makeSortOrderBuilder()
    {
        return std::make_shared<SortOrderBuilder>();
    }
}

#endif // FRTS_SORTORDERBUILDER_H
