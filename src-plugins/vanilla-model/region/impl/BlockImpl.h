#ifndef FRTS_BLOCKIMPL_H
#define FRTS_BLOCKIMPL_H

#include <entity/Blocking.h>
#include <entity/Entity.h>
#include <region/WriteableBlock.h>

#include <frts/RecursiveLock.h>

#include <memory>
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
        BlockImpl(const IdPtr& blockingType, const IdPtr& sortOrderType);

        EntityVector getByComponent(const IdPtr& componentType) const override;
        EntityVector getEntities() const override;
        bool has(const EntityPtr& entity) const override;
        void insert(const EntityPtr& entity) override;
        bool isBlocking(const BlockedByPtr& blockedBy) const override;
        void remove(const EntityPtr& entity) override;

    private:
        /**
         * @brief Predicate to check if a entity has a certain component.
         */
        struct HasComponentPred
        {
            HasComponentPred(const IdPtr& componentType)
                : componentType{componentType}
            {
                assert(componentType != nullptr);
            }

            bool operator()(const EntityPtr& entity)
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
            IsBlockingPred(const IdPtr& blockingType, const BlockedByPtr& blockedBy)
                : blockedBy{blockedBy}, blockingType{blockingType}
            {
                assert(blockingType != nullptr);
            }

            bool operator()(const EntityPtr& entity)
            {
                assert(entity != nullptr);

                bool result = false;
                auto blocking = getComponent<Blocking>(blockingType, entity);
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
        mutable RecursiveLock locker;
    };

    /**
     * @brief Create a new block object.
     * @param blockingType The id of the blocking component type.
     * @param sortOrderType The id of the sortorder component type.
     * @return The block pointer.
     */
    inline BlockImplPtr makeBlock(const IdPtr& blockingType, const IdPtr& sortOrderType)
    {
        assert(blockingType != nullptr);
        assert(sortOrderType != nullptr);

        return std::make_shared<BlockImpl>(blockingType, sortOrderType);
    }
}

#endif // FRTS_BLOCKIMPL_H
