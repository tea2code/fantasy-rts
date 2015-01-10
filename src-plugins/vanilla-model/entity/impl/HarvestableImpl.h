#ifndef FRTS_HARVESTABLEIMPL_H
#define FRTS_HARVESTABLEIMPL_H

#include <entity/Harvestable.h>

#include <frts/shared>


namespace frts
{
    class HarvestableImpl : public Harvestable
    {
    public:
        /**
         * @param componentType The component type.
         */
        HarvestableImpl(IdPtr componentType);
        ~HarvestableImpl();

        void addType(IdPtr type) override;
        IdPtr getComponentType() const override;
        IdUnorderedSet getTypes() const override;
        bool hasType(IdPtr type) const override;
        void removeType(IdPtr type) override;

    private:
        IdUnorderedSet types;
        IdPtr componentType;
    };

    /**
     * @brief Create new Harvestable.
     * @param componentType The component type.
     * @return The Harvestable.
     */
    inline HarvestablePtr makeHarvestable(IdPtr componentType)
    {
        assert(componentType != nullptr);

        return std::make_shared<HarvestableImpl>(componentType);
    }
}

#endif // FRTS_HARVESTABLEIMPL_H
