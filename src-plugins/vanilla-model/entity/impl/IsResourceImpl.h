#ifndef FRTS_ISRESOURCEIMPL_H
#define FRTS_ISRESOURCEIMPL_H

#include <entity/IsResource.h>


namespace frts
{
    class IsResourceImpl : public IsResource
    {
    public:
        IsResourceImpl(const IdPtr& componentType);

        IdPtr getComponentType() const override;
        IdPtr getResourceType() const override;
        void setResourceType(const IdPtr& resourceType) override;

    private:
        IdPtr componentType;
        IdPtr resourceType;
    };

    /**
     * @brief Create new IsResource.
     * @param componentType The component type.
     * @return The IsResource.
     */
    inline IsResourcePtr makeIsResource(const IdPtr& componentType)
    {
        assert(componentType != nullptr);

        return std::make_shared<IsResourceImpl>(componentType);
    }
}

#endif // FRTS_ISRESOURCEIMPL_H
