#include "HarvestableBuilder.h"

#include "HarvestableImpl.h"
#include <entity/ComponentIds.h>


frts::HarvestableBuilder::HarvestableBuilder()
{

}

frts::HarvestableBuilder::~HarvestableBuilder()
{

}

frts::ComponentPtr frts::HarvestableBuilder::build(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::harvestable());
    return makeHarvestable(id);
}

frts::ComponentPtr frts::HarvestableBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<Harvestable>(build(shared));
    for (auto& type : node->getStrings("types"))
    {
        auto id = shared->makeId(type);
        component->addType(id);
    }
    return component;
}
