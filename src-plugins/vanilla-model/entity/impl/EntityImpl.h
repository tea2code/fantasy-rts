#ifndef FRTS_ENTITYIMPL_H
#define FRTS_ENTITYIMPL_H

#include <entity/Entity.h>

#include <frts/shared>

#include <unordered_map>
#include <vector>


namespace frts
{
    class EntityImpl : public Entity
    {
    public:
        EntityImpl();

        void addComponent(ComponentPtr component) override;
        ComponentPtr getComponent(IdPtr type) const override;
        std::vector<ComponentPtr> getComponents() const override;
        bool hasComponent(IdPtr type) const override;
        void removeComponent(IdPtr type) override;

    private:
        using ComponentMap = std::unordered_map<IdPtr, ComponentPtr>;

    private:
        ComponentMap components;
    };

    /**
     * @brief Create new entity.
     * @return The entity.
     */
    inline EntityPtr makeEntity()
    {
        return std::make_shared<EntityImpl>();
    }

    /**
     * @brief Create new entity and initialize with components.
     * @param components The components.
     * @return The entity.
     */
    inline EntityPtr makeEntity(std::vector<ComponentPtr> components)
    {
        EntityPtr entity = makeEntity();
        for (auto& component : components)
        {
            entity->addComponent(component);
        }
        return entity;
    }
}

#endif // FRTS_ENTITYIMPL_H
