#ifndef FRTS_DROPIMPL_H
#define FRTS_DROPIMPL_H

#include <entity/Drop.h>

#include <frts/shared>


namespace frts
{
    class DropImpl : public Drop
    {
    public:
        DropImpl(IdPtr type);

        void addDrop(IdPtr entityId) override;
        IdPtr getComponentType() const override;
        std::vector<IdPtr> getDrops() const override;
        bool hasDrop(IdPtr entityId) const override;
        void removeDrop(IdPtr entityId) override;

    private:
        struct IdComparison
        {
            IdComparison(IdPtr id)
            {
                this->id = id;
            }

            bool operator()(IdPtr other)
            {
                return id == other;
            }

            IdPtr id;
        };

    private:
        std::vector<IdPtr> drops;
        IdPtr type;
    };

    /**
     * @brief Create new Drop.
     * @param type The component type.
     * @return The Drop.
     */
    inline DropPtr makeDrop(IdPtr type)
    {
        return std::make_shared<DropImpl>(type);
    }
}

#endif // FRTS_DROPIMPL_H
