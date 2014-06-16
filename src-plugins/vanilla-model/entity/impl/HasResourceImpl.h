#ifndef FRTS_HASRESOURCEIMPL_H
#define FRTS_HASRESOURCEIMPL_H

#include <entity/HasResource.h>


namespace frts
{
    class HasResourceImpl : public HasResource
    {
    public:
        HasResourceImpl(IdPtr type);

        void addResource(IdPtr resourceType);
        IdPtr getComponentType() const override;
        ResourceSet getResources() const;
        bool hasResource(IdPtr resourceType) const;
        void removeResource(IdPtr resourceType);

    private:
        ResourceSet resources;
        IdPtr type;
    };

    /**
     * @brief Create new HasResource.
     * @param type The component and resource type.
     * @return The HasResource.
     */
    inline HasResourcePtr makeHasResource(IdPtr type)
    {
        return std::make_shared<HasResourceImpl>(type);
    }
}

#endif // FRTS_HASRESOURCEIMPL_H