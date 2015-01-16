#include "InfoBuilder.h"

#include <entity/ComponentIds.h>
#include "InfoImpl.h"


frts::InfoBuilder::InfoBuilder()
{}

frts::ComponentPtr frts::InfoBuilder::build(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    return makeInfo(shared->makeId(ComponentIds::info()));
}

frts::ComponentPtr frts::InfoBuilder::build(const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<Info>(build(shared));
    std::vector<Info::InfoItem> information;
    auto infosNode = node->getNode("infos");
    for (auto infoNode : *infosNode)
    {
        auto name = shared->makeId(infoNode->getString("name"));
        auto value = shared->makeId(infoNode->getString("value"));
        information.push_back(std::make_pair(name, value));
    }
    component->setInformation(information);
    return component;
}
