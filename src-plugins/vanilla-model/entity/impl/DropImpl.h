#ifndef FRTS_DROPIMPL_H
#define FRTS_DROPIMPL_H

#include <entity/Drop.h>

#include <frts/shared>


namespace frts
{
    class DropImpl : public Drop
    {
    public:
        /**
         * @param type The component type.
         */
        DropImpl(const IdPtr& type);

        void addDrop(const IdPtr& entityId) override;
        IdPtr getComponentType() const override;
        IdVector getDrops() const override;
        bool hasDrop(const IdPtr& entityId) const override;
        void removeDrop(const IdPtr& entityId) override;

    private:
        struct IdComparison
        {
            IdComparison(const IdPtr& id)
                : id{id}
            {}

            bool operator()(const IdPtr& other)
            {
                return id == other;
            }

            IdPtr id;
        };

    private:
        IdVector drops;
        IdPtr type;
    };

    /**
     * @brief Create new Drop.
     * @param type The component type.
     * @return The Drop.
     */
    inline DropPtr makeDrop(const IdPtr& type)
    {
        assert(type != nullptr);

        return std::make_shared<DropImpl>(type);
    }
}

#endif // FRTS_DROPIMPL_H
