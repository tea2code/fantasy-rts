#ifndef FRTS_SORTORDER_H
#define FRTS_SORTORDER_H

#include "Component.h"
#include "Entity.h"
#include <frts/shared>

#include <memory>
#include <string>


namespace frts
{
    class SortOrder;

    /**
     * @brief Pointer to SortOrder.
     */
    using SortOrderPtr = std::shared_ptr<SortOrder>;

    /**
     * @brief Component describing in which order a entity is sorted in for example
     *        a block.
     */
    class SortOrder : public Component
    {
    public:
        /**
         * @brief Some predifined sort order positions for different pseudo entity
         *        types. Don't use strongly typed enums to allow implicit conversion
         *        to integer.
         */
        enum Position
        {
            DEFAULT = -1,

            TILE_DEFAULT = 0,
            TILE_NORMAL = 40,
            TILE_IMPORTANT = 80,

            STATIC_DEFAULT = 100,
            STATIC_NORMAL = 140,
            STATIC_IMPORTANT = 180,

            DYNAMIC_DEFAULT = 200,
            DYNAMIC_NORMAL = 240,
            DYNAMIC_IMPORTANT = 280,

            OVERLAY_DEFAULT = 300,
            OVERLAY_NORMAL = 340,
            OVERLAY_IMPORTANT = 380,

            BOTTOM = -1000,
            TOP = 1000
        };

        /**
         * @brief Orders entities by sort order.
         */
        struct SortOrdered
        {
            SortOrdered(IdPtr componentType = nullptr)
                : componentType{componentType}
            {}

            bool operator() (EntityPtr lhs, EntityPtr rhs) const
            {
                int sortOrderLhs = Position::DEFAULT;
                SortOrderPtr componentLhs = getComponent<SortOrder>(componentType, lhs);
                if (componentLhs != nullptr)
                {
                    sortOrderLhs = componentLhs->getSortOrder();
                }

                int sortOrderRhs = Position::DEFAULT;
                SortOrderPtr componentRhs = getComponent<SortOrder>(componentType, rhs);
                if (componentRhs != nullptr)
                {
                    sortOrderRhs = componentRhs->getSortOrder();
                }

                return sortOrderLhs < sortOrderRhs;
            }

            IdPtr componentType;
        };

    public:
        virtual ~SortOrder() {}

        virtual int getSortOrder() const = 0;
        virtual void setSortOrder(int sortOrder) = 0;
    };
}

#endif // FRTS_SORTORDER_H
