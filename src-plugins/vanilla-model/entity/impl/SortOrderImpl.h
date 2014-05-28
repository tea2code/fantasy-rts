#ifndef FRTS_SORTORDERIMPL_H
#define FRTS_SORTORDERIMPL_H

#include <entity/SortOrder.h>

#include <frts/shared>


namespace frts
{
    class SortOrderImpl : public SortOrder
    {
    public:
        SortOrderImpl(IdPtr type);

        IdPtr getComponentType() override;
        int getSortOrder() const override;
        void setSortOrder(int sortOrder) override;

    private:
        int sortOrder;
        IdPtr type;
    };

    /**
     * @brief Create new SortOrder.
     * @param type The component type.
     * @return The SortOrder.
     */
    inline SortOrderPtr makeSortOrder(IdPtr type, int sortOrder = SortOrder::Position::DEFAULT)
    {
        SortOrderPtr component = std::make_shared<SortOrderImpl>(type);
        component->setSortOrder(sortOrder);
        return component;
    }
}

#endif // FRTS_SORTORDERIMPL_H
