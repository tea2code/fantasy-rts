#ifndef FRTS_SORTORDERIMPL_H
#define FRTS_SORTORDERIMPL_H

#include <entity/SortOrder.h>

#include <frts/shared>


namespace frts
{
    class SortOrderImpl : public SortOrder
    {
    public:
        SortOrderImpl(SharedManagerPtr shared);

        IdPtr getComponentType() override;
        int getSortOrder() const override;
        void setSortOrder(int sortOrder) override;

    private:
        int sortOrder;
        IdPtr type;
    };

    /**
     * @brief Create new SortOrder.
     * @param shared The shared manager.
     * @return The SortOrder.
     */
    inline SortOrderPtr makeSortOrder(SharedManagerPtr shared, int sortOrder = SortOrder::Position::DEFAULT)
    {
        SortOrderPtr component = std::make_shared<SortOrderImpl>(shared);
        component->setSortOrder(sortOrder);
        return component;
    }
}

#endif // FRTS_SORTORDERIMPL_H
