#include "CurriculumImpl.h"


frts::CurriculumImpl::CurriculumImpl(IdPtr type)
    : type{type}
{

}

frts::CurriculumImpl::~CurriculumImpl()
{

}

void frts::CurriculumImpl::addAbility(IdPtr ability)
{
    assert(ability != nullptr);

    abilities.insert(ability);
}

frts::IdUnorderedSet frts::CurriculumImpl::getAbilities() const
{
    return abilities;
}

frts::IdPtr frts::CurriculumImpl::getComponentType() const
{
    return type;
}

bool frts::CurriculumImpl::hasAbility(IdPtr ability) const
{
    assert(ability != nullptr);

    return (abilities.find(ability) != abilities.end());
}

void frts::CurriculumImpl::removeAbility(IdPtr ability)
{
    assert(ability != nullptr);

    abilities.erase(ability);
}
