#ifndef FRTS_ENTITYGROUPBUILDER_H
#define FRTS_ENTITYGROUPBUILDER_H

#include <entity/ComponentBuilder.h>

#include <memory>


namespace frts
{
    class EntityGroupBuilder;

    /**
     * @brief Pointer to EntityGroupBuilder.
     */
    using EntityGroupBuilderPtr = std::shared_ptr<EntityGroupBuilder>;

    /**
     * @brief Builder for EntityGroup.
     */
    class EntityGroupBuilder : public ComponentBuilder
    {
    public:
        EntityGroupBuilder();
        ~EntityGroupBuilder();

        ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node) override;
    };

    /**
     * @brief Create new EntityGroupBuilder.
     * @return The component builder.
     */
    inline ComponentBuilderPtr makeEntityGroupBuilder()
    {
        return std::make_shared<EntityGroupBuilder>();
    }
}

#endif // FRTS_ENTITYGROUPBUILDER_H
