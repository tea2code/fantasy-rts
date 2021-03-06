#ifndef FRTS_TELEPORTIMPL_H
#define FRTS_TELEPORTIMPL_H

#include <entity/Teleport.h>

#include <frts/shared>


namespace frts
{
    class TeleportImpl : public Teleport
    {
    public:
        TeleportImpl(const IdPtr& type);

        IdPtr getComponentType() const override;
        EntityPtr getTarget() const override;
        void setTarget(const EntityPtr& target) override;

    private:
        EntityPtr target;
        IdPtr type;
    };

    /**
     * @brief Create new Teleport.
     * @param type The component type.
     * @return The SortOrder.
     */
    inline TeleportPtr makeTeleport(const IdPtr& type)
    {
        assert(type != nullptr);

        return std::make_shared<TeleportImpl>(type);
    }
}

#endif // FRTS_TELEPORTIMPL_H
