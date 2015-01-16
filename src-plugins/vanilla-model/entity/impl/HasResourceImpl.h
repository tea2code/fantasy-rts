#ifndef FRTS_HASRESOURCEIMPL_H
#define FRTS_HASRESOURCEIMPL_H

#include <entity/HasResource.h>


namespace frts
{
    class HasResourceImpl : public HasResource
    {
    public:
        HasResourceImpl(const IdPtr& type);

        void addResource(const IdPtr& resourceType);
        IdPtr getComponentType() const override;
        ResourceSet getResources() const;
        bool hasResource(const IdPtr& resourceType) const;
        void removeResource(const IdPtr& resourceType);

    private:
        ResourceSet resources;
        IdPtr type;
    };

    /**
     * @brief Create new HasResource.
     * @param type The component and resource type.
     * @return The HasResource.
     */
    inline HasResourcePtr makeHasResource(const IdPtr& type)
    {
        assert(type != nullptr);

        return std::make_shared<HasResourceImpl>(type);
    }
}

#endif // FRTS_HASRESOURCEIMPL_H
