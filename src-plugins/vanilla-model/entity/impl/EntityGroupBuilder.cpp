#include "EntityGroupBuilder.h"

#include "EntityGroupImpl.h"
#include "EntityGroupSatelliteImpl.h"
#include <entity/ComponentIds.h>
#include <main/ModelFactory.h>
#include <main/ModelIds.h>


frts::EntityGroupBuilder::EntityGroupBuilder()
{

}

frts::EntityGroupBuilder::~EntityGroupBuilder()
{

}

frts::ComponentPtr frts::EntityGroupBuilder::build(const EntityPtr&, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    return makeEntityGroup(shared->makeId(ComponentIds::entityGroup()));
}

frts::ComponentPtr frts::EntityGroupBuilder::build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(entity != nullptr);
    assert(shared != nullptr);
    assert(node != nullptr);

    EntityVector entities;
    EntityGroupImpl::EntityPosMap positions;

    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    auto satelliteId = shared->makeId(ComponentIds::entityGroupSatellite());
    for (auto satelliteNode : *node)
    {
        auto entityId = shared->makeId(satelliteNode->getString("entity"));
        auto satellite = mf->makeEntity(entityId, shared);
        auto component = makeEntityGroupSatellite(satelliteId, entity);
        satellite->addComponent(component);
        entities.push_back(satellite);

        auto pos = mf->makePoint(satelliteNode->getInteger("x"),
                                 satelliteNode->getInteger("y"),
                                 satelliteNode->getInteger("z"));
        positions.insert(std::make_pair(satellite, pos));
    }

    return makeEntityGroup(shared->makeId(ComponentIds::entityGroup()), entities, positions);
}
