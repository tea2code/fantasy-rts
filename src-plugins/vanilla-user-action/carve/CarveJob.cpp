#include "CarveJob.h"


frts::CarveJob::CarveJob(const IdPtr& id, const IdPtr& type, const IdUnorderedSet& carveEntities,
                         bool doDrop, bool fromAbove,  const EntityPtr& toHarvest,
                         const IdUnorderedSet& jobRequirements, const EntityPtr& jobMarker)
    : BaseJob(id, type, jobRequirements, jobMarker), carveEntities{carveEntities}, doDrop{doDrop},
      fromAbove{fromAbove}, toHarvest{toHarvest}
{

}

frts::CarveJob::~CarveJob()
{

}

