#ifndef TESTREGIONGENERATOR_H
#define TESTREGIONGENERATOR_H

#include <entity/ComponentIds.h>
#include <region/RegionGenerator.h>
#include <region/impl/BlockImpl.h>
#include <region/impl/PointImpl.h>

#include <shared/impl/IdImpl.h>


namespace frts
{
    class TestRegionGenerator : public RegionGenerator
    {
    public:
        TestRegionGenerator()
            : blockingType{makeId(ComponentIds::blocking())},
              sortOrderType{makeId(ComponentIds::sortOrder())}
        {}

        std::map<PointPtr, WriteableBlockPtr> allBlocks(Point::value zLevel) override
        {
            const int sizeX = 10;
            const int sizeY = 10;

            std::map<PointPtr, WriteableBlockPtr> result;
            for (int x = 0; x < sizeX; ++x)
            {
                for (int y = 0; y < sizeY; ++y)
                {
                    result[makePoint(x, y, zLevel)] = makeBlock(blockingType, sortOrderType);
                }
            }
            return result;
        }

        WriteableBlockPtr newBlock(PointPtr) override
        {
            return makeBlock(blockingType, sortOrderType);
        }

    private:
        IdPtr blockingType;
        IdPtr sortOrderType;
    };
}

#endif // TESTREGIONGENERATOR_H
