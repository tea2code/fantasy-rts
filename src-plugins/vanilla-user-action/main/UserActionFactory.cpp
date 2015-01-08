#include "UserActionFactory.h"

#include "UserActionIds.h"


frts::UserActionFactory::UserActionFactory()
    : BaseUtility(UserActionIds::userActionFactory(), 1, UserActionIds::userActionFactory(), 1)
{

}

frts::UserActionFactory::~UserActionFactory()
{

}

bool frts::UserActionFactory::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // TODO

    isInit = true;
    return false;
}
