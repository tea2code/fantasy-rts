#include "CurriculumBuilder.h"

#include "CurriculumImpl.h"
#include <entity/ComponentIds.h>


frts::CurriculumBuilder::CurriculumBuilder()
{

}

frts::CurriculumBuilder::~CurriculumBuilder()
{

}

frts::ComponentPtr frts::CurriculumBuilder::build(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::curriculum());
    return makeCurriculum(id);
}

frts::ComponentPtr frts::CurriculumBuilder::build(const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<Curriculum>(build(shared));
    for (auto& ability : node->getStrings("abilities"))
    {
        auto id = shared->makeId(ability);
        component->addAbility(id);
    }
    return component;
}
