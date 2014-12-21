#ifndef FRTS_BLOCKIMPL_H
#define FRTS_BLOCKIMPL_H

#include <entity/Blocking.h>
#include <entity/Entity.h>
#include <region/WriteableBlock.h>

#include <memory>
#include <mutex>
#include <set>
#include <stdexcept>


namespace frts
{
    class BlockImpl;

    /**
     * @brief Pointer to BlockImpl.
     */
    using BlockImplPtr = std::shared_ptr<BlockImpl>;

    class BlockImpl : public WriteableBlock
    {
    public:
        /**
         * @param blockingType The id of the blocking component type.
         */
        BlockImpl(IdPtr blockingType, IdPtr sortOrderType);

        std::vector<EntityPtr> getByComponent(IdPtr componentType) const override;
        std::vector<EntityPtr> getEntities() const override;
        bool has(EntityPtr entity) const override;
        void insert(EntityPtr entity) override;
        bool isBlocking(BlockedByPtr blockedBy) const override;
        void remove(EntityPtr entity) override;

    private:
        /**
         * @brief Predicate to check if a entity has a certain component.
         */
        struct HasComponentPred
        {
            HasComponentPred(IdPtr componentType)
                : componentType{componentType}
            {
                assert(componentType != nullptr);
            }

            bool operator()(EntityPtr entity)
            {
                return entity->hasComponent(componentType);
            }

            IdPtr componentType;
        };

        /**
         * @brief Predicate to check if a entity blocks a blocked by definition.
         */
        struct IsBlockingPred
        {
            IsBlockingPred(IdPtr blockingType, BlockedByPtr blockedBy)
                : blockedBy{blockedBy}, blockingType{blockingType}
            {
                assert(blockedBy != nullptr);
                assert(blockingType != nullptr);
            }

            bool operator()(EntityPtr entity)
            {
                assert(entity != nullptr);

                bool result = false;
                BlockingPtr blocking = getComponent<Blocking>(blockingType, entity);
                if (blocking != nullptr)
                {
                    result = blocking->blocks(blockedBy);
                }
                return result;
            }

            BlockedByPtr blockedBy;
            IdPtr blockingType;
        };

        /**
         * @brief Ordered set of entities.
         */
        using EntitySet = std::multiset<EntityPtr, SortOrder::SortOrdered>;

    private:
        IdPtr blockingType;
        std::unique_ptr<EntitySet> entities;

        // Needs to be mutable because of its usage in const methods.
        // This is ok because the mutex doesn't represent a public visible
        // state of this class.
        mutable std::mutex lockAllMutex;
    };

    /**
     * @brief Create a new block object.
     * @param blockingType The id of the blocking component type.
     * @param sortOrderType The id of the sortorder component type.
     * @return The block pointer.
     */
    inline BlockImplPtr makeBlock(IdPtr blockingType, IdPtr sortOrderType)
    {
        assert(blockingType != nullptr);
        assert(sortOrderType != nullptr);

        return std::make_shared<BlockImpl>(blockingType, sortOrderType);
    }
}

#endif // FRTS_BLOCKIMPL_H
