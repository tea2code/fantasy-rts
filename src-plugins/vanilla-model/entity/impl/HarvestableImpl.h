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
        HarvestableImpl(const IdPtr& componentType);
        ~HarvestableImpl();

        void addType(const IdPtr& type) override;
        IdPtr getComponentType() const override;
        double getSpeed() const override;
        IdUnorderedSet getTypes() const override;
        bool hasType(const IdPtr& type) const override;
        void removeType(const IdPtr& type) override;
        void setSpeed(double speed) override;

    private:
        double speed = 0.0;
        IdUnorderedSet types;
        IdPtr componentType;
    };

    /**
     * @brief Create new Harvestable.
     * @param componentType The component type.
     * @return The Harvestable.
     */
    inline HarvestablePtr makeHarvestable(const IdPtr& componentType)
    {
        assert(componentType != nullptr);

        return std::make_shared<HarvestableImpl>(componentType);
    }
}

#endif // FRTS_HARVESTABLEIMPL_H
