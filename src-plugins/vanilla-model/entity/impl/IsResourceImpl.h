#ifndef FRTS_ISRESOURCEIMPL_H
#define FRTS_ISRESOURCEIMPL_H

#include <entity/IsResource.h>


namespace frts
{
    class IsResourceImpl : public IsResource
    {
    public:
        IsResourceImpl(IdPtr type);

        IdPtr getComponentType() override;

    private:
        IdPtr type;
    };

    /**
     * @brief Create new IsResource.
     * @param type The component and resource type.
     * @return The IsResource.
     */
    inline IsResourcePtr makeIsResource(IdPtr type)
    {
        return std::make_shared<IsResourceImpl>(type);
    }
}

#endif // FRTS_ISRESOURCEIMPL_H
